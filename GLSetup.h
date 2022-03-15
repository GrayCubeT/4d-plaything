#pragma once
#include <exception>
#include <string>
#include <openGL/glew.h>
#include <openGL/glfw3.h>

namespace glsetup {
    /* setting global opengl settings
    and allowing opengl to actually work */
    void basicSetup();
    /* perspective setup (doesnt work for now)*/
    void perspectiveSetup(GLuint x, GLuint y);
}