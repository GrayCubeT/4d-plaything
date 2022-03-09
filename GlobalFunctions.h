/// Most basic functions and classes that are used everywhere
#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <sstream>
#include <iomanip>


/// checks for keypress
/// basically a shortened version of sfml functionality
bool keypress(sf::Keyboard::Key key);

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
