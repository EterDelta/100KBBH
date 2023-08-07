#include "100KBBH/model/Models.h"

extern "C" const char bullet_obj[];
extern "C" const char bullet_source_obj[];
extern "C" const char player_obj[];
extern "C" const char quad_obj[];

std::forward_list<Model> Models::models;

const Model& Models::BULLET = addModel(Model::fromResource(bullet_obj));
const Model& Models::BULLET_SOURCE = addModel(Model::fromResource(bullet_source_obj));
const Model& Models::PLAYER = addModel(Model::fromResource(player_obj));
const Model& Models::QUAD = addModel(Model::fromResource(quad_obj));

Model& Models::addModel(Model&& model) {
    models.push_front(std::move(model));
    return models.front();
}
