#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <functional>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GlobalFunctions.h"
#include "Handlers.h"
#include "GLBasicShapes.h"
#include "GLSetup.h"
#include "Shader.h"
#include "testSource.h"

enum {
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 700,
};

void renderingLoop(GLFWwindow* win) {
    glm::dvec3 camPos(0, 0, 0), camDir(0, 0, -1), camUp(0, 1, 0);
    KeyboardHandler::init(camPos, camDir, camUp);
    MouseHandler::init(camDir, camUp);
    // opengl shaders
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    try {
        shader->loadFromFile(GL_FRAGMENT_SHADER, "BasicFragmentShader.glsl");
        shader->loadFromFile(GL_VERTEX_SHADER, "BasicVertexShader.glsl");
        shader->createProgram();
    }
    catch (std::exception e) {
        std::cout << e.what();
        return;
    }
    SizeHandler::getInstance().setShader(shader);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
    // then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseCubeVertices), baseCubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(baseCubeIndices), baseCubeIndices, GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind VBO VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // projection matrix set up
    shader->Bind();
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), ((float)w) / h, 1.0f, 200.f);
    shader->uniformMat4("projection", projection);

    while (!glfwWindowShouldClose(win)) {
        {
            GLenum err = glGetError();
            if (err != 0) {
                std::cout << err << "\n";
                throw std::exception();
            }
        }
        // keys
        KeyboardHandler::getInstance().checkAll();
        

        // rendering

        glClearColor(0.0f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind the shader

        // create transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, 0));
        //transform = glm::rotate(transform, (float)(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));

        
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(camPos, camPos + camDir, camUp);
        
        shader->Bind();
        shader->uniformMat4("model", model);
        shader->uniformMat4("view", view);
        
        // draw the thing
        glBindVertexArray(VAO); // normally, needs to be bound each time
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // normally, needs to be rebound somewhere else

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    // reallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader->UnBind();
}


int main() {
    
    //testingCentral();
    //return 0;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "poggers", NULL, NULL); 
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // initialize all the handlers
    initializeHandlers(window);
    
    // opengl globals and glew/glad loading
    glsetup::basicSetup();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // window loop
    // TODO enter thread
    renderingLoop(window);
    glfwTerminate();
	return 0;
}