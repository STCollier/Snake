#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "world/shader.h"
#include "world/window.h"
#include "world/camera.h"

#include "objects/floor.h"
#include "objects/snake.h"
#include "objects/apple.h"

int main() {

    createWindow();
    initFloor();
    initSnake();
    initApple();

    struct Shader mainShader = createShader("res/shaders/main.vs", "res/shaders/main.fs");

    while (!glfwWindowShouldClose(window.self)) {
        updateWindow();

        useShader(mainShader);
        useCamera(mainShader);

        renderFloor(mainShader);
        renderSnake(mainShader);
        renderApple(mainShader);

        glfwSwapBuffers(window.self);
        glfwPollEvents();

        //printf("X: %f\n Y: %f\n\n", snake.x, snake.y);
    }

    destroyFloor();
    destroySnake();
    destroyApple();

    terminateWindow();
   
    return 0;
}