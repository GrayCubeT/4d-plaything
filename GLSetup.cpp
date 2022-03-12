#include "GLSetup.h"


void GLController::setup() {

}

GLController::GLController() {
    
}

GLController::~GLController() {
}

void glsetup::shaderSetup() {
    // build and compile our shader program
    // ------------------------------------
    // vertex shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::exception(std::string(
            "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog) + "\n")
                .c_str());
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::exception(std::string(
            "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog) + "\n")
            .c_str());
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::exception(std::string(
            "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog) + "\n")
            .c_str());
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void glsetup::basicSetup() {
    // smooth shading 
    glShadeModel(GL_SMOOTH);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);
}

void glsetup::perspectiveSetup(GLuint x, GLuint y) {

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, x, y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(x) / y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

}
