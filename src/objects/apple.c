#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "../world/camera.h"
#include "../world/shader.h"
#include "apple.h"

struct Apple apple;

void initApple() {
    srand(time(NULL));

    //Range from +10 to -8
    int rx = (rand() % (10 + 1 + 8) - 8);
    int ry = (rand() % (10 + 1 + 8) - 8);

    //Generate only even numbers to lock to grid
    float x = (rx + rx % 2) - 1.0f;
    float y = (ry + ry % 2) - 1.0f;

    apple.x = x;
    apple.y = y;

    float vertices[] = {
        //positions     //texture coords
        -1, -1,  1,   0.0f, 0.0f, 
         1, -1,  1,   1.0f, 0.0f, 
        -1,  1,  1,   0.0f, 1.0f,
         1,  1,  1,   1.0f, 1.0f,

        -1, -1, -1,   0.0f, 0.0f,
         1, -1, -1,   1.0f, 0.0f,
        -1,  1, -1,   0.0f, 1.0f,
         1,  1, -1,   1.0f, 1.0f 
    };

    unsigned int indices[] = {
        //Top
        2, 6, 7,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        0, 1, 5,

        //Left
        0, 2, 6,
        0, 4, 6,

        //Right
        1, 3, 7,
        1, 5, 7,

        //Front
        0, 2, 3,
        0, 1, 3,

        //Back
        4, 6, 7,
        4, 5, 7
    };

    glGenTextures(1, &apple.texture);
    glBindTexture(GL_TEXTURE_2D, apple.texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps

    int width, height, nrChannels;
    
    unsigned char *data = stbi_load("res/textures/apple.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Could not load apple texture\n");
    }

    stbi_image_free(data);

    glGenVertexArrays(1, &apple.VAO);
    glGenBuffers(1, &apple.VBO);
    glGenBuffers(1, &apple.EBO);

    glBindVertexArray(apple.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, apple.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, apple.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

static void _drawApple() {
    glBindTexture(GL_TEXTURE_2D, apple.texture);

    glBindVertexArray(apple.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void renderApple(struct Shader shader) {
    glm_mat4_identity(camera.model); //Reset matrix
    glm_rotate(camera.model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});
    glm_scale(camera.model, (vec3) {0.1, 0.1, 0.05}); //Construct second matrix
    glm_translate(camera.model, (vec3) {apple.x, apple.y, -21.0f}); //Offset to grid

    setShaderMat4(shader, "model", camera.model);
    _drawApple();
}

void destroyApple() {
    glDeleteVertexArrays(1, &apple.VAO);
    glDeleteBuffers(1, &apple.VBO);
    glDeleteBuffers(1, &apple.EBO);
}