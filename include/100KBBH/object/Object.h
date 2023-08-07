#pragma once

#include "glad/gl.h"
#include "100KBBH/util/Util.h"
#include "100KBBH/model/Model.h"
#include "100KBBH/shader/Shader.h"

class Object {
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Vector3 color;
    Vector2 velocity;
    bool checksCollision;
    bool colliding;
    bool alive;
    float aliveTime;

    Object();

    virtual ~Object() = default;

    virtual const Model& getModel() const = 0;

    virtual void draw(MatrixStack& stack, GLuint program) const;

    virtual void update(float deltaTime);

    virtual bool collide(Object& other);
};
