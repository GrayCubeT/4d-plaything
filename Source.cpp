#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <thread>
#include <vector>
#include <map>
#include <functional>
#include "SFML/OpenGL.hpp"
#include "GlobalFunctions.h"
#include "EventController.h"
#include "Handlers.h"
#include "GLBasicShapes.h"
#include "GLShaders.h"
#include "GLSetup.h"

using namespace sf;

void renderingLoop(sf::RenderWindow& win, bool& running, EventController &eventController) {
    GLdouble x = 0, y = 0, z = 0;
    basicSetupEventController(eventController, x, y, z);
    // opengl shaders
    win.setActive(true);
    glsetup::shaderSetup();
    glsetup::basicSetup();
    glsetup::perspectiveSetup(win.getSize().x, win.getSize().y);

    // Enable position coordinates vertex components
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Disable normal and color vertex components
    glDisableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(8, GL_FLOAT, 7 * sizeof(GLfloat), vertexPositions);
    //glColorPointer(8, GL_FLOAT, 7 * sizeof(GLfloat), vertexPositions + 4);

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
        glTranslatef(x, y, z - 10.0);
        glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);

        // Draw the cube
        glDrawElements(GL_LINES, 12, GL_UNSIGNED_INT, indices);


        win.setActive(false);
        
        win.display();
    }
}



int main() {
    // window
	RenderWindow win(VideoMode(700, 700), "openGL testing zone");
	win.setFramerateLimit(60);
    bool running = true;

    // handlers
    EventController eventController(&win);
    initialSetupEventController(eventController, win, running);
    
    // window loop
    // TODO enter thread
    renderingLoop(win, running, eventController);

	return 0;
}