#pragma once

#include <vector>
#include <random>
#include <map>
#include <forward_list>
#include "1KBBH/util/Util.h"
#include "1KBBH/texture/Texture.h"
#include "1KBBH/shader/Shader.h"
#include "1KBBH/model/Model.h"
#include "1KBBH/object/Object.h"
#include "1KBBH/object/wave/WaveHandler.h"

class Game {
private:
    WaveHandler waveHandler;
    MatrixStack matrixStack;
    GLuint vao;

    Game();

    ~Game();

public:
    std::vector<std::shared_ptr<Object>> newObjects;
    std::vector<std::shared_ptr<Object>> gameObjects;
    std::default_random_engine random;
    std::map<int, bool> inputs;
    float gameTime;
    bool booted;
    bool stop;

    static Game& getInstance();

    void init();

    void reset();

    void draw();

    void update(float deltaTime);
};