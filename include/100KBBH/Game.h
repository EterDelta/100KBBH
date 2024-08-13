#pragma once

#include <vector>
#include <random>
#include <unordered_map>
#include <forward_list>
#include "100KBBH/util/Util.h"
#include "100KBBH/texture/Texture.h"
#include "100KBBH/shader/Shader.h"
#include "100KBBH/model/Model.h"
#include "100KBBH/object/Object.h"
#include "100KBBH/object/wave/WaveHandler.h"

class Game {
private:
    static constexpr int VK_SPC = 0x20;

    WaveHandler waveHandler;

    MatrixStack matrixStack;
    GLuint vao;

    Game();

    ~Game();

public:
    std::vector<std::shared_ptr<Object>> newObjects;
    std::vector<std::shared_ptr<Object>> gameObjects;

    std::default_random_engine random;

    std::unordered_map<int, bool> inputs;

    float gameTime;

    bool booted;
    bool stop;

    static Game& getInstance();

    void init();

    void reset();

    void draw();

    void update(float deltaTime);
};