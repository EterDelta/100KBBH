#include "100KBBH/object/Player.h"
#include "100KBBH/Game.h"
#include "100KBBH/model/Models.h"

Player::Player() : Object(),
    speed(0.8F) {
    position.y = -0.5;
    position.z = -0.5;
    scale = Vector3(0.08F, 0.08F, 0.08F);
    color = Vector3(1.0F, 0.32F, 0.64F);
    checksCollision = true;
}

void Player::draw(MatrixStack& stack, GLuint program) const {
    stack.push();

    stack.top().rotate(0.0F, aliveTime * 3.0F, 0.0F);

    Object::draw(stack, program);
    stack.pop();
}

void Player::update(float deltaTime) {
    Game& game = Game::getInstance();

    velocity = Vector2(
        (float) (game.inputs[VK_D] - game.inputs[VK_A]),
        (float) (game.inputs[VK_W] - game.inputs[VK_S])
    );

    velocity = velocity.normalized() * speed;

    Object::update(deltaTime);

    if (position.x - scale.x < -1.0F) {
        position.x = -1.0F + scale.x;
    } else if (position.x + scale.x > 1.0F) {
        position.x = 1.0F - scale.x;
    }
    if (position.y - scale.y < -1.0F) {
        position.y = -1.0F + scale.y;
    } else if (position.y + scale.y > 1.0F) {
        position.y = 1.0F - scale.y;
    }
}

bool Player::collide(Object& other) {
    Bullet* bullet = dynamic_cast<Bullet*>(&other);
    if (bullet && Object::collide(other)) {
        Game& game = Game::getInstance();
        game.stop = true;
        return true;
    }
    return false;
}

const Model& Player::getModel() const {
    return Models::PLAYER;
}
