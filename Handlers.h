#pragma once
#include "EventController.h"



/*
    Most basic event handlers:
    Closed
    Resized
*/
void initialSetupEventController(EventController& eventController, 
        sf::RenderWindow& win, bool& running);

/*
    basic handlers:
    ASDW movement
*/
void basicSetupEventController(EventController& eventController,
    GLdouble& x, GLdouble& y, GLdouble& z);