#include "100KBBH/shader/Shaders.h"

extern "C" const char background_frag[];
extern "C" const char foreground_frag[];
extern "C" const char main_vert[];
extern "C" const char object_frag[];

std::forward_list<Shader> Shaders::shaders;

const Shader& Shaders::BACKGROUND = addShader(Shader(main_vert, background_frag));
const Shader& Shaders::FOREGROUND = addShader(Shader(main_vert, foreground_frag));
const Shader& Shaders::OBJECT = addShader(Shader(main_vert, object_frag));

Shader& Shaders::addShader(Shader&& shader) {
    shaders.push_front(std::move(shader));
    return shaders.front();
}
