#include "GLSetup.h"

void glsetup::basicSetup() {
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //    throw (std::exception("GLAD (os) failed to initialize"));
    //}
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::exception("poggers");
    }

    // smooth shading 
    glShadeModel(GL_SMOOTH);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    //glDisable(GL_LIGHTING);

}

void glsetup::perspectiveSetup(GLuint x, GLuint y) {

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, x, y);

}
