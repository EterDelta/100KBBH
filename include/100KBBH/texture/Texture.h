#pragma once

#include "glad/gl.h"
#include <vector>

class Texture {
private:
    const std::vector<unsigned char> pixelData;
    const int width;
    const int height;
    GLuint textureID;
    bool isInit;

public:
    Texture(std::vector<unsigned char>&& pixelData, int width, int height);

    ~Texture();

    void init();

    GLuint getTextureID() const;

    static Texture fromResource(const unsigned char* bmpData);
};
