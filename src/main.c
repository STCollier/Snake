#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "include/shader.h"
#include "include/window.h"

int main() {

    createWindow();

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //OH MY GOSH ITS GL_ELEMENT_ARRAY_BUFFER INSTEAD OF GL_ARRAY_BUFFER FINALLY
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        glm_rotate(model, glm_rad(-55.0f), (vec3) {1.0f, 0.0f, 0.0f});
        glm_translate(view, (vec3) {0.0f, 0.0f, -3.0f});
        glm_perspective(glm_rad(45.0f), window.width / window.height, 0.1f, 100.0f, projection);

        setShaderMat4(mainShader, "projection", projection);
        setShaderMat4(mainShader, "view", view);
        setShaderMat4(mainShader, "model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    terminateWindow();
   
    return 0;
}