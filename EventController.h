#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

enum {
    SHIFT_MULTIPLIER_VALUE = 2
};

enum class eventTypes {
    DRAG,
    KEY,
    WHEEL
};

using namespace sf;


/// Handles all window events
class EventController {

    sf::RenderWindow* win;
    sf::Vector2f mpos, prevmpos;
    bool lmb, rmb;
    /// needed so handler will not assume button click as click and drag
    bool notDragging;
    /// this is basically a multiplier for any movement if shift is pressed
    double shiftMult;
    
    /// handlers for keys, argument is key pressed
    std::vector<std::function<bool(sf::Keyboard::Key)>> keyHandlers;
    /// handlers for click and drag, argument is mpos change
    std::vector<std::function<bool(sf::Vector2f)>> dragHandlers;
    /// handlers for wheel events, argument is change
    std::vector<std::function<bool(double)>> wheelHandlers;

public:    
    /// constructor only uses the current window
    EventController(sf::RenderWindow* _win) : win(_win), mpos(), prevmpos(),
        lmb(false), rmb(false), notDragging(true) {};

    /// this method is called every frame to register all window events
    /// calls all the possible handlers
    void handle();
    
    /// add a handler
    template <typename T>
    bool addHandler(eventTypes type, std::function<T> handler);
};