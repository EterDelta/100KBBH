#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "100KBBH/Game.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Game& game = Game::getInstance();
    if (action == GLFW_PRESS) {
        game.inputs[key] = true;
    } else if (action == GLFW_RELEASE) {
        game.inputs[key] = false;
    }
}

int main() {
    if (!glfwInit()) {
        // FIXME: Display error message (glfwInit failed!)
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(512, 512, "100KBBH", nullptr, nullptr);
    if (!window) {
        // FIXME: Display error message (window wasn't created!) 
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwSetKeyCallback(window, keyCallback);
    glViewport(0, 0, 512, 512);

    Game& game = Game::getInstance();
    game.init();

    auto prevFrameTime = std::chrono::system_clock::now();
    auto frameTime = std::chrono::system_clock::now();
    while (!glfwWindowShouldClose(window)) {
        frameTime = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedFrameTime = frameTime - prevFrameTime;
        float deltaTime = elapsedFrameTime.count();

        game.update(deltaTime);
        game.draw();

        prevFrameTime = frameTime;

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
