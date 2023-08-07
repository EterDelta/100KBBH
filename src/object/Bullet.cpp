#include "100KBBH/object/Bullet.h"
#include "100KBBH/model/Models.h"

Bullet::Bullet(Vector2 bulletVelocity) : Object() {
    position.z = -0.5;
    scale = Vector3(0.05F, 0.05F, 0.05F);
    color = Vector3(0.95F, 0.08F, 0.35F);
    velocity = bulletVelocity;
}

void Bullet::draw(MatrixStack& stack, GLuint program) const {
    stack.push();

    float rot = aliveTime * 5.0F;
    stack.top().rotate(rot, rot, rot);

    Object::draw(stack, program);
    stack.pop();
}

void Bullet::update(float deltaTime) {
    Object::update(deltaTime);

    if ((position.x + scale.x < -1.0F || position.x - scale.x > 1.0F) ||
        (position.y + scale.y < -1.0F || position.y - scale.y > 1.0F)) {
        alive = false;
    }

    float colorFactor = std::min(1.0F, aliveTime * 1.5F);
    color.x = MathUtil::lerp(1.0F, 0.95F, colorFactor);
    color.y = MathUtil::lerp(1.0F, 0.08F, colorFactor);
    color.z = MathUtil::lerp(1.0F, 0.35F, colorFactor);
}

const Model& Bullet::getModel() const {
    return Models::BULLET;
}
