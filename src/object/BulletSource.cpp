#include "100KBBH/object/BulletSource.h"
#include "100KBBH/Game.h"
#include "100KBBH/model/Models.h"

const std::vector<BulletSource::BulletFunction> BulletSource::unweightedFunctions {
    // Target burst
    [](const BulletSource& source, float alpha) {
        Vector2 direction = Vector2(source.target.lock()->position.x - source.position.x, source.target.lock()->position.y - source.position.y).normalized();
        return std::make_unique<Bullet>(direction * source.bulletSpeed);
    },
    // Predictive target burst
    [](const BulletSource& source, float alpha) {
        Vector2 sourcePos = Vector2(source.position.x, source.position.y);
        Vector2 targetPos = Vector2(source.target.lock()->position.x, source.target.lock()->position.y);
        float length = (sourcePos - targetPos).length();
        float speed = source.bulletSpeed;
        float time = length / speed;
        Vector2 futureTargetPos = targetPos + source.target.lock()->velocity * time;
        Vector2 direction = (futureTargetPos - sourcePos).normalized();
        return std::make_unique<Bullet>(direction * speed);
    }
};

const std::vector<BulletSource::BulletFunction> BulletSource::weightedFunctions {
    // Circular burst
    [](const BulletSource& source, float alpha) {
        float angle = alpha * 2 * MathUtil::PI;
        Vector2 direction = Vector2(MathUtil::fastCos(angle), MathUtil::fastSin(angle)).normalized();
        return std::make_unique<Bullet>(direction * source.bulletSpeed);
    },
    // Helix burst
    [](const BulletSource& source, float alpha) {
        float angle = alpha * 2 * MathUtil::PI;
        Vector2 direction = Vector2(MathUtil::fastCos(angle), MathUtil::fastSin(angle)).normalized();
        float speed = source.bulletSpeed * (1 + 0.5f * MathUtil::fastSin(4 * MathUtil::PI * alpha));
        return std::make_unique<Bullet>(direction * speed);
    },
    // Star burst
    [](const BulletSource& source, float alpha) {
        float angle = alpha * 2 * MathUtil::PI;
        Vector2 direction = Vector2(MathUtil::fastCos(angle), MathUtil::fastSin(angle)).normalized();
        float speed = source.bulletSpeed * (1 + 0.5f * MathUtil::fastSin(10 * MathUtil::PI * alpha));
        return std::make_unique<Bullet>(direction * speed);
    }
};

BulletSource::BulletSource(const BulletSource::BulletFunction& function, const std::shared_ptr<Object>& target, float speed, float delay, int count, int bursts) : Object(),
    spawnFactor(0.0F),
    despawnFactor(0.0F),
    bulletFunction(function),
    target(target),
    bulletSpeed(speed),
    bulletDelay(delay),
    bulletValue(1.0F / count),
    bulletTime(0.0F),
    burstAlpha(0.0F),
    bursts(bursts),
    active(false),
    despawn(false) {
    position.z = -0.25;
    scale = Vector3(0.2F, 0.2F, 0.2F);
}

void BulletSource::draw(MatrixStack& stack, GLuint program) const {
    stack.push();

    float size = MathUtil::fastCos(aliveTime * 10.0F) / 8.0F;
    stack.top().scale(1.0F + size, 1.0F + size, 1.0F);

    float animFactor;
    float easedAnimFactor;
    float animY;
    if (!active) {
        animFactor = std::clamp(spawnFactor, 0.0F, 1.0F);
        easedAnimFactor = (--animFactor) * animFactor * animFactor + 1;
        animY = MathUtil::lerp(1.5F, position.y, easedAnimFactor);
        stack.top().translate(0.0F, animY - position.y, 0.0F);
    } else if (despawn) {
        animFactor = std::clamp(despawnFactor, 0.0F, 1.0F);
        easedAnimFactor = animFactor * animFactor * animFactor;
        animY = MathUtil::lerp(position.y, -1.5F, easedAnimFactor);
        stack.top().translate(0.0F, animY - position.y, 0.0F);
    }

    Object::draw(stack, program);
    stack.pop();
}

void BulletSource::update(float deltaTime) {
    Object::update(deltaTime);

    if (active) {
        if (!target.expired()) {
            bulletTime += deltaTime;

            while (bulletTime >= bulletDelay && !despawn) {
                Game& game = Game::getInstance();

                if (bursts > 0) {
                    if (burstAlpha < 1.0F) {
                        burstAlpha += bulletValue;
                        std::unique_ptr<Bullet> nextBullet = bulletFunction(*this, burstAlpha);
                        nextBullet->position.x = position.x;
                        nextBullet->position.y = position.y;
                        game.newObjects.push_back(std::move(nextBullet));
                    } else {
                        bursts--;
                        burstAlpha = 0.0F;
                    }
                } else {
                    despawn = true;
                }
                bulletTime = 0.0F;
            }
        }
        if (despawn) {
            despawnFactor += deltaTime;
            if (despawnFactor >= 1.0F) {
                alive = false;
            }
        }
    } else {
        spawnFactor += deltaTime;
        if (spawnFactor >= 1.0F) {
            active = true;
        }
    }
}

const Model& BulletSource::getModel() const {
    return Models::BULLET_SOURCE;
}
