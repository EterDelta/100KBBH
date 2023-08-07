#pragma once

#include <forward_list>
#include "Texture.h"

class Textures {
private:
    static std::forward_list<Texture> textures;

    static Texture& addTexture(Texture&& texture);

public:
    static const Texture& FONT_ATLAS;

    friend class Game;
};