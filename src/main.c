#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

#include "world/shader.h"
#include "world/window.h"
#include "world/camera.h"

#include "objects/floor.h"
#include "objects/snake.h"

int main() {

    createWindow();
    initFloor();
    initSnake();

    struct Shader mainShader = createShader("res/shaders/main.vs", "res/shaders/main.fs");

    while (!glfwWindowShouldClose(window.self)) {
        updateWindow();

        useShader(mainShader);
        useCamera(mainShader);

        renderFloor(mainShader);
        renderSnake(mainShader);

        glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    destroyFloor();
    terminateWindow();
   
    return 0;
}