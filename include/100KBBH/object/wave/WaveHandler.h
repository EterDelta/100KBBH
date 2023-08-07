#pragma once

#include "100KBBH/object/BulletSource.h"

class WaveHandler {
public:
    std::weak_ptr<BulletSource> source;
    std::vector<int> score;
    float waveDelay;
    int wave;

    WaveHandler();

    void update(float deltaTime);

    void computeScore();

    void spawnNewWave();

    bool canSpawnNewWave() const;
};
