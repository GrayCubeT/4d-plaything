/// Most basic functions and classes that are used everywhere
#pragma once
#include <openGL/glew.h>
#include <openGL/glfw3.h>
#include <math.h>
#include <sstream>
#include <iomanip>


const double GLOBAL_SPEED_MODIFIER = 0.1;
const double MOUSE_SENSITIVITY = 0.1;

/// checks for keypress
bool keypress(GLFWwindow* win, unsigned char c);


/// translate number (int, double or any other) to string
/// breaks if T does cannot be streamed
template <typename T>
std::string numtostr(T number, int precision = 0);

/// smh does not work if this is in GlobalFunctions.cpp
template<typename T>
inline std::string numtostr(T number, int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss << std::fixed << number;
    std::string ans = ss.str();
    return ans;
}
