#pragma once

#include <forward_list>
#include "Model.h"

class Models {
private:
    static std::forward_list<Model> models;

    static Model& addModel(Model&& model);

public:
    static const Model& BULLET;
    static const Model& BULLET_SOURCE;
    static const Model& PLAYER;
    static const Model& QUAD;

    friend class Game;
};