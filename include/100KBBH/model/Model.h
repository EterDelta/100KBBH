#pragma once

#include "glad/gl.h"
#include <vector>

class Model {
private:
    const std::vector<GLfloat> vertices;
    const std::vector<GLuint> indices;
    GLuint buffers[2];
    bool isInit;

public:
    Model(std::vector<GLfloat>&& verticesIn, std::vector<GLuint>&& indicesIn);

    ~Model();

    void init();

    void draw() const;

    static Model fromResource(const char* objData);
};