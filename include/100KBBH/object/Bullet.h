#pragma once

#include "Object.h"

class Bullet : public Object {
public:
    Bullet(Vector2 bulletVelocity);

    void draw(MatrixStack& stack, GLuint program) const override;

    void update(float deltaTime) override;

    const Model& getModel() const override;
};