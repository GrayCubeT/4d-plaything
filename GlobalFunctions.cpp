#include "GlobalFunctions.h"



bool keypress(GLFWwindow* win, unsigned char c) {
    return (glfwGetKey(win, c) == GLFW_PRESS);
}

