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
        glm_mat4_identity(projection);
        glm_perspective(glm_rad(window.fov), (float) window.width / (float) window.height, 0.1f, 100.0f, projection); //Make sure to convert to floats for float division
        //glm_ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f, projection);
        setShaderMat4(mainShader, "projection", projection);

        mat4 view;
        glm_mat4_identity(view);
        glm_translate(view, (vec3) {0.0f, -0.4f, -5.0f});
        glm_rotate(view, glm_rad(55.0f), (vec3) {1.0f, 0.0f, 0.0f});
        setShaderMat4(mainShader, "view", view);
        
        mat4 model;
        glm_mat4_identity(model);
        glm_rotate(model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});

        setShaderMat4(mainShader, "model", model);
        drawFloor(); //Uses the currently set matrix (rotation)

        glm_mat4_identity(model); //Reset matrix
        glm_rotate(model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});
        glm_scale(model, (vec3) {0.1, 0.1, 0.05}); //Construct second matrix
        glm_translate(model, (vec3) {snake.x-1.0f, snake.y-1.0f, -21.0f}); //Offset to grid

        setShaderMat4(mainShader, "model", model);
        drawSnake(); //Uses the newly set matrix (scaling)

        glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    destroyFloor();
    terminateWindow();
   
    return 0;
}