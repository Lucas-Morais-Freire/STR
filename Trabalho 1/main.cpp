#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine.hpp>

int main() {
    engine eng(1280, 720);
    glfwSwapInterval(1);
    std::cout << glGetString(GL_VERSION) << '\n';

    auto render = [&]() {

    };

    auto keyHold = [&](const std::list<int>& pressedKeys) {

    };

    auto keyPress = [&](int key) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            eng.setWindowShouldClose(true);
            break;
        }
    };

    auto mousePos = [&](double xpos, double ypos) {

    };

    eng.setRenderFunc(render);
    eng.setKeyHoldFunc(keyHold);
    eng.setKeyPressFunc(keyPress);
    eng.setMousePosFunc(mousePos);

    eng.mainLoop();
    return 0;
}