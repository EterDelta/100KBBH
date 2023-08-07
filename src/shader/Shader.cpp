#include "100KBBH/shader/Shader.h"

Shader::Shader(const char* vertexSource, const char* fragmentSource) :
    vertexSource(vertexSource),
    fragmentSource(fragmentSource),
    isInit(false) {
}

Shader::~Shader() {
    if (isInit) {
        glDetachShader(program, vertShader);
        glDetachShader(program, fragShader);
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteProgram(program);
    }
}

void Shader::init() {
    if (!isInit) {
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        program = glCreateProgram();

        glShaderSource(vertShader, 1, &vertexSource, nullptr);
        glCompileShader(vertShader);

        glShaderSource(fragShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragShader);

        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        isInit = true;
    }
}

GLuint Shader::getProgram() const {
    return isInit ? program : 0;
}
