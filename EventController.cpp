#include "EventController.h"

EventController::EventController(sf::RenderWindow* _win) : win(_win), mpos(), prevmpos(),
    lmb(false), rmb(false), dragging(false), dragHandler(nullptr), keysToCheck(), 
    pressHandlers(), handlers() {}

EventController::~EventController() {
    
}

void EventController::handle() {
    // event handling
    sf::Event event;
    while (win->pollEvent(event)) {
        auto it = handlers.find(event.type);
        if (it != handlers.end()) {
            // bruh
            (*(*it).second)(event);
        }
    }
    // since dragging results in no event, it needs to be called constantly
    if (dragging && (lmb || rmb)) {
        (*dragHandler)((lmb) ? sf::Mouse::Left : sf::Mouse::Right, mpos - prevmpos);
    }
    // same goes for pressing and holding keys
    for (auto i : keysToCheck) {
        if (keypress(i)) {
            (*pressHandlers[i])();
        }
    }
}

bool EventController::addHandler(
        sf::Event::EventType type, 
        std::shared_ptr<std::function<bool(sf::Event)>> handler) {
    auto it = handlers.find(type);
    if (it != handlers.end()) {
        return false;
    }
    handlers[type] = handler;
    return true;
}

bool EventController::addPressHandler(
        sf::Keyboard::Key key, 
        std::shared_ptr<std::function<void()>> handler) {
    pressHandlers[key] = handler;
    keysToCheck.push_back(key);
    return false;
}

bool EventController::setDragHandler(
        std::shared_ptr<std::function<bool(sf::Mouse::Button, sf::Vector2f)>> handler) {
    if (dragHandler != nullptr) {
        return false;
    }
    dragHandler = handler;
    return true;
}
