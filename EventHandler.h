#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ViewHandler.h"

enum {
    SHIFT_MULTIPLIER_VALUE = 2
};

using namespace sf;


/// Handles all window events
class EventHandler {
    sf::RenderWindow* win;
    sf::Vector2f mpos, prevmpos;
    bool lmb, rmb;
    /// this is needed for correct usage of buttons, so that after clicking
    /// a button the handler will not assume further mouse movement as click and drag
    bool notDragging;
    /// this is basically a multiplier for any movement if shift is pressed
    double shiftMult;
    
    ViewHandler viewHandler;

public:
    /// constructor only uses the current window
    EventHandler(sf::RenderWindow* _win) : viewHandler(), win(_win), mpos(), prevmpos(),
            lmb(false), rmb(false), notDragging(true);

    /// this method is called every frame to register all window events
    void handle();
};