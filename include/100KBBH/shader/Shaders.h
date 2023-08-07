#pragma once

#include <forward_list>
#include "Shader.h"

class Shaders {
private:
    static Shader& addShader(Shader&& shader);

    static std::forward_list<Shader> shaders;

public:
    static const Shader& BACKGROUND;
    static const Shader& FOREGROUND;
    static const Shader& OBJECT;

    friend class Game;
};