#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <map>
#include "GlobalFunctions.h"

enum {
    SHIFT_MULTIPLIER_VALUE = 2
};



/* Handles all window events
 *
 * NOTE: might delete all handlers with destructor (?)
*/
class EventController {

    sf::RenderWindow* win;
    sf::Vector2f mpos, prevmpos;
    bool lmb, rmb;
    /* needed so handler will not assume button click as click and drag */
    bool dragging;
    
    
    /* handlers for holding key pressed, argument is key pressed */
    std::map<unsigned int, std::shared_ptr<std::function<void()>>> pressHandlers;
    /* extra class to hold all the keys that need to be checked */
    std::vector<unsigned int> keysToCheck;

    /* mouse drag handler */
    std::shared_ptr<std::function<bool(sf::Mouse::Button, sf::Vector2f)>> dragHandler;
    
    /* a full map of all general-purpose handlers 
       only supports 1 handler per event.
    */
    std::map<sf::Event::EventType, std::shared_ptr<std::function<bool(sf::Event)>>> handlers;

public:    
    /* default constructor, everything is set to pretty much 0 */
    EventController(sf::RenderWindow* _win);
    ~EventController();
    /* this method is called every frame to register all window events
     * calls all the possible handlers internally
    */
    void handle();
    
    /* add a handler by defining its event type and any function as a handler */
    bool addHandler(sf::Event::EventType type, std::shared_ptr<std::function<bool(sf::Event)>> handler);

    /* add a handler for key press and hold events */
    bool addPressHandler(sf::Keyboard::Key, std::shared_ptr<std::function<void()>> handler);

    bool setDragHandler(std::shared_ptr<std::function<bool(sf::Mouse::Button, sf::Vector2f)>>);
};
