#include "GlobalFunctions.h"


bool keypress(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool keypress(unsigned int key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}