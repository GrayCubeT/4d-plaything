#include "Handlers.h"

void initialSetupEventController(EventController& eventController, 
    sf::RenderWindow& win, bool& running) {
    eventController.addHandler(
        sf::Event::Closed,
        std::make_shared<std::function<bool(sf::Event)>>(([&running](sf::Event event) {
            running = false;
            return true; })));
    eventController.addHandler(
        sf::Event::Resized,
        std::make_shared<std::function<bool(sf::Event)>>(([&win](sf::Event event) {
            win.setActive(true);
            glViewport(0, 0, event.size.width, event.size.height);
            win.setActive(false);
            return true; })));
}

void basicSetupEventController(EventController& eventController,
        GLdouble& x, GLdouble& y, GLdouble& z) {
    
    eventController.addPressHandler(
        sf::Keyboard::D,
        std::make_shared<std::function<void()>>(([&x]() {x += GLOBAL_SPEED_MODIFIER; })));
    eventController.addPressHandler(
        sf::Keyboard::A,
        std::make_shared<std::function<void()>>(([&x]() {x -= GLOBAL_SPEED_MODIFIER; })));
    eventController.addPressHandler(
        sf::Keyboard::W,
        std::make_shared<std::function<void()>>(([&z]() {z -= GLOBAL_SPEED_MODIFIER; })));
    eventController.addPressHandler(
        sf::Keyboard::S,
        std::make_shared<std::function<void()>>(([&z]() {z += GLOBAL_SPEED_MODIFIER; })));

}
