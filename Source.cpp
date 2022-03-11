#include <stdio.h>
#include <iostream>
#include "SFML/OpenGL.hpp"
#include "GlobalFunctions.h"
#include "EventController.h"
#include <vector>
#include <map>
#include <functional>
#include <thread>

using namespace sf;

void renderingLoop(sf::RenderWindow& win, bool& running, EventController &eventController) {
    GLfloat x = 0, y = 0, z = 0;


    
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

    // opengl
    const GLfloat vertexPositions[] = {
        0.75f, 0.75f, 0.0f, 1.0f,
        0.75f, -0.75f, 0.0f, 1.0f,
        -0.75f, -0.75f, 0.0f, 1.0f,
    };
    win.setActive(true);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, win.getSize().x, win.getSize().y);

    // Setup a perspective projection
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(win.getSize().x) / win.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
    
    // Enable position coordinates vertex components
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(4, GL_FLOAT, 4 * sizeof(GLfloat), vertexPositions);

    // Disable normal and color vertex components
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Make the window no longer the active window for OpenGL calls
    win.setActive(false);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;
    while (running) {
        eventController.handle();

        win.setActive(true);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x, y, z - 100.0);
        glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);

        // Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 3);


        win.setActive(false);
        
        
        win.display();
    }
}



int main() {
    // window
	RenderWindow win(VideoMode(700, 700), "openGL testing zone");
	win.setFramerateLimit(60);
    bool running = true;
    std::cout << GLOBAL_SPEED_MODIFIER;
    // handlers
    EventController eventController(&win);
    // TODO: eventController.build
    // handler has to be stored somewhere
    // should be moved later
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
    
    // window loop
    // TODO enter thread
    renderingLoop(win, running, eventController);


	return 0;
}