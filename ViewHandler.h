#pragma once
#include <SFML/Graphics.hpp>

enum {
    /// adjusts camera movement speed
    MOVE_MULTIPLIER = 10
};

// do I even need this? no, cus there is dynamic calculation anyway
// basically a view, but with all the positional storage
// has functions that handle ASWD ZX and lmb mouse dragging 
class ViewHandler {
public:
    double zoom;
    sf::Vector2f clientsize;
    // y / x clientsize
    double screenratio;
    // main view
    sf::View view;

    ViewHandler();

};
