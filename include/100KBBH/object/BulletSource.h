#pragma once

#include <functional>
#include <optional>
#include <memory>
#include "Object.h"
#include "Bullet.h"

class BulletSource : public Object {
private:
    float spawnFactor;
    float despawnFactor;

protected:
    using BulletFunction = std::function<std::unique_ptr<Bullet>(const BulletSource&, float)>;

    const BulletFunction& bulletFunction;
    const float bulletSpeed;
    const float bulletDelay;
    const float bulletValue;
    std::weak_ptr<Object> target;
    float bulletTime;
    float burstAlpha;

public:
    static const std::vector<BulletFunction> unweightedFunctions;
    static const std::vector<BulletFunction> weightedFunctions;
    int bursts;
    bool active;
    bool despawn;

    BulletSource(const BulletFunction& function, const std::shared_ptr<Object>& target, float speed, float delay, int count, int bursts);

    void draw(MatrixStack& factor, GLuint program) const override;

    void update(float deltaTime) override;

    const Model& getModel() const override;
};
