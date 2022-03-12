#pragma once
#include <GL/glew.h>
#include "SFML/OpenGL.hpp"

const GLfloat baseCubeVertices[] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
};
const GLuint baseCubeIndices[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 4,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    7, 2,
    6, 1,
    0, 3,
    0, 5
};
