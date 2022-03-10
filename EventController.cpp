#include "EventController.h"

EventController::EventController(sf::RenderWindow* _win) : win(_win), mpos(), prevmpos(),
    lmb(false), rmb(false), dragging(false), keyHandlers(), dragHandlers(), wheelHandlers(), 
    resizeHandlers() {}

void EventController::handle() {
    // event handling
    sf::Event event;
    while (win->pollEvent(event)) {
        // close window event
        if (event.type == sf::Event::Closed) {
            win->close();
        }
        // wheel events
        else if (event.type == sf::Event::MouseWheelScrolled) {
            for (auto i : wheelHandlers) {
                // return value not used
                i(event.mouseWheelScroll.delta);
            }
        }
        // resize events
        else if (event.type == sf::Event::Resized) {
            for (auto i : resizeHandlers) {
                // return value not used
                i(sf::Vector2i(event.size.width, event.size.height));
            }
            // legacy 2d code for view handling
            /*
            //std::cout << "was: " << vhandler->view.getSize().x << " " << vhandler->view.getSize().y << "\n";
            sf::Vector2f prevclientsize = vhandler->clientsize;
            vhandler->clientsize = sf::Vector2f(event.size.width, event.size.height);
            vhandler->screenratio = event.size.height / event.size.width;
            sf::Vector2f s = vhandler->view.getSize();
            vhandler->view.setSize(s.x * event.size.width / prevclientsize.x, s.y * event.size.height / prevclientsize.y);

            fixedView->setSize(event.size.width, event.size.height);
            fixedView->setCenter(event.size.width / 2.0, event.size.height / 2.0);
            */
        }
        // key events
        else if (event.type == sf::Event::KeyPressed) {
            keyHandlers[event.key.code]();
        }
    }
    // since dragging results in no event, it needs to be called constantly
    if (dragging) {
        if (lmb) {
            for (auto i : dragHandlers) {
                // return value not used
                i(sf::Mouse::Left, mpos - prevmpos);
            }
        }
        if (rmb) {
            for (auto i : dragHandlers) {
                // return value not used
                i(sf::Mouse::Right, mpos - prevmpos);
            }
        }
    }
    // same goes for pressing and holding keys
    for (auto i : keysToCheck) {
        if (keypress(i)) {
            pressHandlers[i]();
        }
    }
}
