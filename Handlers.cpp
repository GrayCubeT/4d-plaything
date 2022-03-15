#include "Handlers.h"


void initializeHandlers(GLFWwindow* win) {
    glfwSetFramebufferSizeCallback(win, SizeHandler::framebufferSizeCallback);
    glfwSetKeyCallback(win, KeyboardHandler::keyCallback);
    glfwSetCursorPosCallback(win, MouseHandler::mouseCallback);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

KeyboardHandler::KeyboardHandler() : keys(256) {
    keysToCheck.clear();
    handlers.clear();
}

KeyboardHandler& KeyboardHandler::getInstance() {
    static KeyboardHandler instance;
    return instance;
}

void KeyboardHandler::init(glm::dvec3& camPos, glm::dvec3& camDir, glm::dvec3& camUp) {
    getInstance().addHandler('e',
        std::make_shared<std::function<void()>>(([&]() {camPos += camUp * GLOBAL_SPEED_MODIFIER; })));
    getInstance().addHandler('q',
        std::make_shared<std::function<void()>>(([&]() {camPos -= camUp * GLOBAL_SPEED_MODIFIER; })));
    getInstance().addHandler('d',
        std::make_shared<std::function<void()>>([&]() 
            {
                camPos += glm::cross(camDir, camUp) * GLOBAL_SPEED_MODIFIER; 
            }));
    getInstance().addHandler('a',
        std::make_shared<std::function<void()>>(([&]() 
            {
                camPos -= glm::cross(camDir, camUp) * GLOBAL_SPEED_MODIFIER; 
            })));
    getInstance().addHandler('w',
        std::make_shared<std::function<void()>>(([&]() {camPos += camDir * GLOBAL_SPEED_MODIFIER; })));
    getInstance().addHandler('s',
        std::make_shared<std::function<void()>>(([&]() {camPos -= camDir * GLOBAL_SPEED_MODIFIER; })));
    
}

bool KeyboardHandler::keypress(unsigned char key) {
    return keys[key];
}

void KeyboardHandler::checkAll() {
    for (auto i : keysToCheck) {
        if (keypress(i)) {
            (*handlers[i])();
        }
    }
}

void KeyboardHandler::addHandler(unsigned char c, std::shared_ptr<std::function<void()>> handler) {
    handlers[c] = handler;
    keysToCheck.push_back(c);
}

void KeyboardHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        MouseHandler::setworking(false);
    }
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        MouseHandler::setworking(true);
    }
    if (key >= 256 || key < 0) {
        return;
    }
    auto p = tolower(key);
    switch (action) {
    case GLFW_PRESS:
        getInstance().keys[p] = true;
        break;
    case GLFW_RELEASE:
        getInstance().keys[p] = false;
        break;
    default:
        break;
    }
}

void SizeHandler::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    if (getInstance().shaderInitialized) {
        getInstance().shader->Bind();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(getInstance().fov), ((float)width) / height, 1.0f, 200.f);

        getInstance().shader->uniformMat4("projection", projection);
    }
}

SizeHandler& SizeHandler::getInstance() {
    static SizeHandler instance;
    return instance;
}

void SizeHandler::setShader(std::shared_ptr<Shader> _shader) {
    shader = _shader;
    shaderInitialized = true;
}

void SizeHandler::setFov(float _fov) {
    fov = _fov;
}

MouseHandler& MouseHandler::getInstance() {
    static MouseHandler instance;
    return instance;
}

void MouseHandler::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    (*getInstance().handler)(xposIn, yposIn);
}

void MouseHandler::init(glm::dvec3& camDir, glm::dvec3& camUp) {
    getInstance().addHandler(std::make_shared<std::function<void(double, double)>>(
        [&](double xpos, double ypos)
            {
                if (!getInstance().working) {
                    return;
                }
                if (getInstance().firstMove) {
                    getInstance().prevMPos = glm::dvec2(xpos, ypos);
                    getInstance().firstMove = false;
                }

                double xoffset = xpos - getInstance().prevMPos.x;
                double yoffset = getInstance().prevMPos.y - ypos; // reversed since y-coordinates go from bottom to top
                
                getInstance().prevMPos = glm::dvec2(xpos, ypos);

                xoffset *= getInstance().getSensitivity();
                yoffset *= getInstance().getSensitivity();

                getInstance().yaw += xoffset;
                getInstance().pitch += yoffset;

                // restrict flipping the screen over the top and bottom
                if (getInstance().pitch > 89.0f)
                    getInstance().pitch = 89.0f;
                if (getInstance().pitch < -89.0f)
                    getInstance().pitch = -89.0f;

                camDir.x = cos(glm::radians(getInstance().yaw)) * cos(glm::radians(getInstance().pitch));
                camDir.y = sin(glm::radians(getInstance().pitch));
                camDir.z = sin(glm::radians(getInstance().yaw)) * cos(glm::radians(getInstance().pitch));
                camDir = glm::normalize(camDir);

                camUp.x = - cos(glm::radians(getInstance().yaw)) * sin(glm::radians(getInstance().pitch));
                camUp.y = cos(glm::radians(getInstance().pitch));
                camUp.z = - sin(glm::radians(getInstance().yaw)) * sin(glm::radians(getInstance().pitch));
                camUp = glm::normalize(camUp);
                // sheesh
            }));
}

void MouseHandler::addHandler(std::shared_ptr<std::function<void(double, double)>> _handler) {
    handler = _handler;
}

void MouseHandler::setSensitivity(double s) {
    getInstance().sensitivity = s;
}

double MouseHandler::getSensitivity() {
    return getInstance().sensitivity;
}

void MouseHandler::setworking(bool _w) {
    getInstance().working = _w;
    getInstance().firstMove = true;
}
