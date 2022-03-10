#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <map>
#include "GlobalFunctions.h"

enum {
    SHIFT_MULTIPLIER_VALUE = 2
};

enum class eventTypes {
    KEY,
    WHEEL,
    RESIZE,
    DRAG,
    PRESS

};


/// Handles all window events
class EventController {

    sf::RenderWindow* win;
    sf::Vector2f mpos, prevmpos;
    bool lmb, rmb;
    /// needed so handler will not assume button click as click and drag
    bool dragging;
    
    /// handlers for single key press events, argument is key pressed
    std::map<sf::Keyboard::Key, std::function<bool()>> keyHandlers;
    /// handlers for holding key pressed, argument is key pressed
    std::map<sf::Keyboard::Key, std::function<bool()>> pressHandlers;
    /// extra class to hold all the keys that need to be checked 
    std::vector<sf::Keyboard::Key> keysToCheck;

    /// handlers for click and drag, argument is mpos change
    std::vector<std::function<bool(sf::Mouse::Button, sf::Vector2f)>> dragHandlers;
    /// handlers for wheel events, argument is change
    std::vector<std::function<bool(double)>> wheelHandlers;
    /// handler for resize events
    std::vector<std::function<bool(sf::Vector2i)>> resizeHandlers;

public:    
    /// constructor only uses the current window
    EventController(sf::RenderWindow* _win);

    /// this method is called every frame to register all window events
    /// calls all the possible handlers
    void handle();
    
    /// add a handler
    template <typename T>
    bool addHandler(eventTypes type, std::function<T> handler);
};

template<typename T>
inline bool EventController::addHandler(eventTypes type, std::function<T> handler) {
    switch (type) {
    case eventTypes::KEY:
        keyHandlers.push_back(handler);
        return true;
    case eventTypes::WHEEL:
        wheelHandlers.push_back(handler);
        return true;
    case eventTypes::RESIZE:
        resizeHandlers.push_back(handler);
        return true;
    case eventTypes::DRAG:
        dragHandlers.push_back(handler);
        return true;
    case eventTypes::PRESS:
        pressHandlers.push_back(handler);
        return true;
    default:
        break;
    }
    return false;
}
