#include <stdio.h>
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

int main() {\

	RenderWindow win(VideoMode(700, 700), "");
	win.setFramerateLimit(60);
	while (win.isOpen()) {
		Event event;
		while (win.pollEvent(event)) {
			if (event.type == Event::Closed) {
				win.close();
			}
            
		}
		win.clear();
		win.display();
	}
	return 0;
}