#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "world/shader.h"
#include "world/window.h"
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

        mat4 projection;
        mat4 view;
        mat4 model;

        glm_mat4_identity(projection);
        glm_mat4_identity(view);
        glm_mat4_identity(model);

        glm_translate(view, (vec3) {0.0f, 0.0f, -5.0f});
        glm_rotate(view, glm_rad(-55.0f), (vec3) {1.0f, 0.0f, 0.0f});
        glm_perspective(glm_rad(window.fov), (float) window.width / (float) window.height, 0.1f, 100.0f, projection); //Make sure to convert to floats for float division
        //glm_ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f, projection);

        setShaderMat4(mainShader, "projection", projection);
        setShaderMat4(mainShader, "view", view);
        setShaderMat4(mainShader, "model", model);

        drawFloor();

        glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    destroyFloor();
    terminateWindow();
   
    return 0;
}