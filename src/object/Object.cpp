#include "1KBBH/object/Object.h"
#include "1KBBH/Game.h"

Object::Object() :
    position(0.0F, 0.0F, 0.0F),
    rotation(0.0F, 0.0F, 0.0F),
    scale(0.5F, 0.5F, 0.5F),
    color(1.0F, 1.0F, 1.0F),
    velocity(0.0F, 0.0F),
    checksCollision(false),
    colliding(false),
    alive(true),
    aliveTime(0.0F) {
}

void Object::draw(MatrixStack& stack, GLuint program) const {
    glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, stack.top().elements);
    glUniform3f(glGetUniformLocation(program, "color"), color.x, color.y, color.z);
    getModel().draw();
}

void Object::update(float deltaTime) {
    aliveTime += deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    if (checksCollision) {
        Game& game = Game::getInstance();
        for (std::shared_ptr<Object>& object : game.gameObjects) {
            if (object.get() != this) collide(*object);
        }
    }
}

bool Object::collide(Object& other) {
    return position.x < other.position.x + other.scale.x && position.x + scale.x > other.position.x &&
           position.y < other.position.y + other.scale.y && position.y + scale.y > other.position.y;
}
