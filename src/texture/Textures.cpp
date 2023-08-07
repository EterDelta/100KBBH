#include "1KBBH/texture/Textures.h"

extern "C" const unsigned char font_atlas_bmp[];

std::forward_list<Texture> Textures::textures;

const Texture& Textures::FONT_ATLAS = addTexture(Texture::fromResource(font_atlas_bmp));

Texture& Textures::addTexture(Texture&& texture) {
    textures.push_front(std::move(texture));
    return textures.front();
}
