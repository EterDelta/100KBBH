#pragma once

#include "glad/gl.h"
#include <string>

class Shader {
private:
    const char* vertexSource;
    const char* fragmentSource;
    GLuint vertShader;
    GLuint fragShader;
    GLuint program;
    bool isInit;

public:
    Shader(const char* vertexSource, const char* fragmentSource);

    ~Shader();

    void init();

    GLuint getProgram() const;
};