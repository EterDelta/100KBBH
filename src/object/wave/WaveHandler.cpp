#include <algorithm>
#include "100KBBH/object/wave/WaveHandler.h"
#include "100KBBH/Game.h"

WaveHandler::WaveHandler() :
    waveDelay(0.5F),
    wave(0) {
}

void WaveHandler::update(float deltaTime) {
    if (canSpawnNewWave()) {
        waveDelay -= deltaTime;

        if (waveDelay <= 0.0F) {
            spawnNewWave();
            wave++;
            waveDelay = 0.5F;
            computeScore();
        }
    }
}

void WaveHandler::computeScore() {
    scoreLiteral = MathUtil::digitize(wave);
    scoreLiteral.resize(3, 0);
    std::reverse(scoreLiteral.begin(), scoreLiteral.end());
    std::for_each(scoreLiteral.begin(), scoreLiteral.end(), [](int& element) { element += 52; });
}

void WaveHandler::spawnNewWave() {
    Game& game = Game::getInstance();

    float speed = 1.0F;
    float delay = 0.0F;
    int count = 1;
    int bursts = 1;

    int instant = std::uniform_int_distribution<>(0, 1)(game.random);
    if (instant) {
        speed = std::uniform_real_distribution<float>(1.0F, 2.0F)(game.random);
        count = std::uniform_int_distribution<>(2, 32)(game.random);
        bursts = std::uniform_int_distribution<>(1, 5)(game.random);
    } else {
        speed = std::uniform_real_distribution<float>(1.0F, 3.0F)(game.random);
        delay = std::uniform_real_distribution<float>(0.1F, 0.25F)(game.random);
        count = std::uniform_int_distribution<>(1, 24)(game.random);
    }

    auto& funcPool = instant ? BulletSource::weightedFunctions : BulletSource::unweightedFunctions;
    auto& function = funcPool[std::uniform_int_distribution<>(0, funcPool.size() - 1)(game.random)];

    std::shared_ptr<BulletSource> newSource = std::make_shared<BulletSource>(function, game.gameObjects.front(), speed, delay, count, bursts);

    std::uniform_real_distribution<float> posDist(-0.8F, 0.8F);
    newSource->position.x = posDist(game.random);
    newSource->position.y = posDist(game.random);

    currentSource = newSource;
    game.newObjects.push_back(std::move(newSource));
}

bool WaveHandler::canSpawnNewWave() const {
    return currentSource.expired() || currentSource.lock()->despawn;
}
