#include "Shader.h"


Shader::Shader() : _program(0), _numShaders(0), created(false) {
    _shaders[VERTEX_SHADER] = 0;
    _shaders[FRAGMENT_SHADER] = 0;
    _shaders[GEOMETRY_SHADER] = 0;
    _shaders[PIXEL_SHADER] = 0;
}

Shader::~Shader() {
    glDeleteProgram(_program);
}

void Shader::loadFromText(GLenum type, const std::string& text) {
    GLuint shader = glCreateShader(type);
    const char* cstr = text.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);

    ///compile + check shader load status
    GLint status;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
        GLchar* infoLog = new GLchar[infoLogSize];
        glGetShaderInfoLog(shader, infoLogSize, nullptr, infoLog);
        throw std::exception(infoLog);
    }
    _shaders[_numShaders++] = shader;
}

void Shader::loadFromFile(GLenum which, const char* fileName) {
    std::ifstream fparser;
    fparser.open(fileName, std::ios_base::in);
    if (fparser) {
        ///read + load
        std::string buffer(std::istreambuf_iterator<char>(fparser), (std::istreambuf_iterator<char>()));
        loadFromText(which, buffer);
    }
    else {
        throw std::exception("Shader loading from file failed");
    }
}

void Shader::createProgram() {
    if (_program != 0) {
        glDeleteProgram(_program);
    }
    _program = glCreateProgram();
    for (int i = 0; i < _numShaders; ++i) {
        glAttachShader(_program, _shaders[i]);
    }
    
    ///link + check
    GLint status;
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogSize;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogSize);
        GLchar* infoLog = new GLchar[infoLogSize];
        glGetProgramInfoLog(_program, infoLogSize, nullptr, infoLog);
        throw std::exception(infoLog);
    }

    for (int i = 0; i < _numShaders; ++i) {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }

    created = true;
}

void Shader::Bind() const {
    glUseProgram(_program);
}

void Shader::UnBind() const {
    glUseProgram(0);
}

GLuint Shader::getProgramID() const { return _program; }

void Shader::uniformMat4(const std::string& str, glm::mat4& value) {
    unsigned int uniformLoc = glGetUniformLocation(_program, str.c_str());
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
