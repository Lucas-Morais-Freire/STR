#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine.hpp>
#include <shader.hpp>
#include <circle.hpp>

int main() {
    engine eng(1280, 720);
    glfwSetWindowPos(eng(),300,100);
    glfwSwapInterval(1);
    std::cout << glGetString(GL_VERSION) << '\n';

    shaderProg mainShader{
        {"shaders/circle.vert", GL_VERTEX_SHADER},
        {"shaders/circle.frag", GL_FRAGMENT_SHADER}
    };
    mainShader.use();

    circle circle({0.f, 0.f}, 50.0f, {0.f, 0.f, 1.f});

    glm::mat4 projmat = glm::ortho(-640.f, 640.f, -360.f, 360.f, 0.f, 1.0f);
    GLint projmat_loc = glGetUniformLocation(mainShader(), "projmat");
    
    glUniformMatrix4fv(projmat_loc, 1, GL_FALSE, glm::value_ptr(projmat));

    auto render = [&]() {
        glClear(GL_COLOR_BUFFER_BIT);

        circle.draw(mainShader);
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