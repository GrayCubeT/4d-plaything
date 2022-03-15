#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <fstream>

#define NUM_SHADER_TYPES 4

/* Shader wrapper class
   allows basic controls over most stuff
   automatic program deletion
*/
class Shader {
public:
    bool created;
    Shader();
    virtual ~Shader();
    /*load shader from string*/
    void loadFromText(GLenum type, const std::string& src);
    /*load shader from file*/
    void loadFromFile(GLenum type, const char* fileName);

    /*link and create program, allowing it to be used*/
    void createProgram();
    
    GLuint getProgramID() const;
    
    void uniformMat4(const std::string& str, glm::mat4& value);

    /*gluseprogram*/
    virtual void Bind() const;
    /*gluseprogram*/
    virtual void UnBind() const;
private:
    enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, PIXEL_SHADER };
    GLuint _program;
    int _numShaders;
    GLuint _shaders[4]; /// VERTEX, FRAGMENT, GEOMETRY AND PIXEL_SHADERS
};
