#pragma once
#include <openGL/glew.h>
#include <openGL/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "GlobalFunctions.h"
#include "Shader.h"


/*
    Most basic event handlers:
    Closed
    Resized
*/
void initializeHandlers(GLFWwindow* win);


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height);


/* class made for handling size changes with shader perspective change if bound*/
class SizeHandler {
public:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static SizeHandler& getInstance();
    void setShader(std::shared_ptr<Shader> _shader);
    void setFov(float _fov);
private:
    std::shared_ptr<Shader> shader;
    bool shaderInitialized;
    float fov;
    SizeHandler() : shader(nullptr), shaderInitialized(false), fov(45.0f) {}
    SizeHandler(SizeHandler& other) = delete;
    void operator=(const SizeHandler&) = delete;
};


/* class for handling and storing all the keyboard stuff 
   is a singleton */
class KeyboardHandler {
public:
    static KeyboardHandler& getInstance();
    static void init(glm::dvec3& camPos, glm::dvec3& camDir, glm::dvec3& camUp);
    bool keypress(unsigned char key);
    void checkAll();
    void addHandler(unsigned char c, std::shared_ptr<std::function<void()>> handler);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    std::vector<char> keysToCheck;
    std::map<char, std::shared_ptr<std::function<void()>>> handlers;
    std::vector<bool> keys;

    KeyboardHandler();
    KeyboardHandler(KeyboardHandler& other) = delete;
    void operator=(const KeyboardHandler&) = delete;

};

/* mouse movement handler */
class MouseHandler {
public:
    static MouseHandler& getInstance();
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    /* initialize with the basic direct camera movement */
    static void init(glm::dvec3& camDir, glm::dvec3& camUp);
    void addHandler(std::shared_ptr<std::function<void(double, double)>> _handler);
    static void setSensitivity(double s);
    static double getSensitivity();
    static void setworking(bool _w);
private:
    std::shared_ptr<std::function<void(double, double)>> handler;
    glm::dvec2 prevMPos;
    bool firstMove;
    // yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    double yaw;	
    double pitch;
    double sensitivity;
    bool working;

    MouseHandler() : prevMPos(0, 0), handler(nullptr), firstMove(true), yaw(-90.0), pitch(0),
        sensitivity(MOUSE_SENSITIVITY), working(true){}
    MouseHandler(MouseHandler& other) = delete;
    void operator=(const MouseHandler&) = delete;
};