#include "100KBBH/texture/Texture.h"

Texture::Texture(std::vector<unsigned char>&& pixelData, int width, int height) :
    pixelData(std::move(pixelData)),
    width(width),
    height(height),
    isInit(false) {
}

Texture::~Texture() {
    if (isInit) {
        glDeleteTextures(1, &textureID);
    }
}

void Texture::init() {
    if (!isInit) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixelData.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        isInit = true;
    }
}

GLuint Texture::getTextureID() const {
    return isInit ? textureID : 0;
}

Texture Texture::fromResource(const unsigned char* bmpData) {
    int width = *(int*) (bmpData + 18);
    int height = *(int*) (bmpData + 22);
    int size = width * height;

    int pixelDataOffset = *(int*) (bmpData + 10);
    const unsigned char* pixelData = bmpData + pixelDataOffset;

    std::vector<unsigned char> bytePixelData(size);
    for (int i = 0; i < size; i++) {
        int byteIndex = i / 8;
        int bitIndex = 7 - (i % 8);
        unsigned char bit = (pixelData[byteIndex] >> bitIndex) & 1;
        bytePixelData[i] = bit * 255;
    }
    return Texture(std::move(bytePixelData), width, height);
}