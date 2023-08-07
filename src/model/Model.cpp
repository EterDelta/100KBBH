#include <utility>
#include <sstream>

#include "100KBBH/model/Model.h"

Model::Model(std::vector<GLfloat>&& verticesIn, std::vector<GLuint>&& indicesIn) :
    vertices(std::move(verticesIn)),
    indices(std::move(indicesIn)),
    isInit(false) {
}

Model::~Model() {
    if (isInit) {
        glDeleteBuffers(2, buffers);
    }
}

void Model::init() {
    if (!isInit) {
        glGenBuffers(2, buffers);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        isInit = true;
    }
}

void Model::draw() const {
    if (isInit) {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

Model Model::fromResource(const char* objData) {
    std::stringstream stream(objData);
    std::string line;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    while (std::getline(stream, line)) {
        std::stringstream lineStream(line);
        std::string type;
        lineStream >> type;

        if (type == "v") {
            GLfloat x, y, z;
            lineStream >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        } else if (type == "f") {
            GLuint v1, v2, v3;
            lineStream >> v1 >> v2 >> v3;
            indices.push_back(v1 - 1);
            indices.push_back(v2 - 1);
            indices.push_back(v3 - 1);
        }
    }
    return Model(std::move(vertices), std::move(indices));
}