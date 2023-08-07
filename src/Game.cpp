#include "100KBBH/Game.h"
#include "100KBBH/object/Player.h"
#include "100KBBH/texture/Textures.h"
#include "100KBBH/shader/Shaders.h"
#include "100KBBH/model/Models.h"

Game::Game() :
    random(std::random_device{}()),
    gameTime(1.0F),
    booted(true),
    stop(true) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Game::~Game() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::init() {
    MathUtil::init();

    for (int i = 0; i < 256; i++) {
        inputs[i] = false;
    }

    for (Texture& texture : Textures::textures) {
        texture.init();
    }
    for (Shader& shader : Shaders::shaders) {
        shader.init();
    }
    for (Model& model : Models::models) {
        model.init();
    }

    reset();
}

void Game::reset() {
    newObjects.clear();
    gameObjects.clear();
    gameObjects.push_back(std::make_shared<Player>());
    gameTime = 1.0F;
    waveHandler.wave = 0;
    waveHandler.waveDelay = 0.5F;
    waveHandler.computeScore();
}

void Game::draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint backgroundProgram = Shaders::BACKGROUND.getProgram();
    glUseProgram(backgroundProgram);
    glUniformMatrix4fv(glGetUniformLocation(backgroundProgram, "transform"), 1, GL_FALSE, matrixStack.top().elements);
    glUniform1f(glGetUniformLocation(backgroundProgram, "time"), gameTime);
    Models::QUAD.draw();

    GLuint objectProgram = Shaders::OBJECT.getProgram();
    glUseProgram(objectProgram);
    for (std::shared_ptr<Object>& object : gameObjects) {
        matrixStack.push();
        matrixStack.top().translate(object->position.x, object->position.y, object->position.z);
        matrixStack.top().rotate(object->rotation.x, object->rotation.y, object->rotation.z);
        matrixStack.top().scale(object->scale.x, object->scale.y, object->scale.z);
        object->draw(matrixStack, objectProgram);
        matrixStack.pop();
    }

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, Textures::FONT_ATLAS.getTextureID());
    matrixStack.push();
    matrixStack.top().translate(0.0F, 0.0F, -1.0F);
    GLuint foregroundProgram = Shaders::FOREGROUND.getProgram();
    glUseProgram(foregroundProgram);
    glUniformMatrix4fv(glGetUniformLocation(foregroundProgram, "transform"), 1, GL_FALSE, matrixStack.top().elements);
    glUniform1i(glGetUniformLocation(foregroundProgram, "stopped"), stop);
    glUniform1i(glGetUniformLocation(foregroundProgram, "booted"), booted);
    std::vector<int> score = waveHandler.score;
    std::for_each(score.begin(), score.end(), [](int& element) { element += 52; });
    glUniform1iv(glGetUniformLocation(foregroundProgram, "score"), score.size(), &score[0]);
    glUniform1i(glGetUniformLocation(foregroundProgram, "atlas"), 0);
    Models::QUAD.draw();
    matrixStack.pop();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::update(float deltaTime) {
    if (!stop) {
        gameTime += deltaTime;
        std::move(std::begin(newObjects), std::end(newObjects), std::back_inserter(gameObjects));
        newObjects.clear();
        for (std::shared_ptr<Object>& object : gameObjects) {
            object->update(deltaTime);
        }
        gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [](std::shared_ptr<Object>& object) {
            return !object->alive;
        }), gameObjects.end());
        waveHandler.update(deltaTime);
    } else {
        if (inputs[0x20]) {
            reset();
            booted = false;
            stop = false;
        }
    }
}
