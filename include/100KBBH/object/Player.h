#pragma once

#include "Object.h"

class Player : public Object {
protected:
    static constexpr int VK_W = 0x57;
    static constexpr int VK_A = 0x41;
    static constexpr int VK_S = 0x53;
    static constexpr int VK_D = 0x44;

    const float speed;

public:
    Player();

    void draw(MatrixStack& stack, GLuint program) const override;

    void update(float deltaTime) override;

    const Model& getModel() const override;

    bool collide(Object& other) override;
};

