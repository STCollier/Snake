#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include <stdio.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "../world/window.h"
#include "../world/shader.h"
#include "../world/camera.h"
#include "snake.h"

struct Snake snake;
snakeDir dir;

void initSnake() {
    dir = Up; //Initilize direction

    snake.speed = 5;
    snake.x = 0.0f;
    snake.y = 0.0f;
    snake.ticks = 0;

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

    glGenTextures(1, &snake.texture);
    glBindTexture(GL_TEXTURE_2D, snake.texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    
    unsigned char *data = stbi_load("res/textures/snake.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Could not load snake texture\n");
    }

    stbi_image_free(data);

    glGenVertexArrays(1, &snake.VAO);
    glGenBuffers(1, &snake.VBO);
    glGenBuffers(1, &snake.EBO);

    glBindVertexArray(snake.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, snake.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, snake.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

static void _drawSnake() {

    snake.ticks++;

    glBindTexture(GL_TEXTURE_2D, snake.texture);

    glBindVertexArray(snake.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    if (glfwGetKey(window.self, GLFW_KEY_UP) == GLFW_PRESS)
        dir = Up;
    if (glfwGetKey(window.self, GLFW_KEY_DOWN) == GLFW_PRESS)
        dir = Down;
    if (glfwGetKey(window.self, GLFW_KEY_LEFT) == GLFW_PRESS)
        dir = Left;
    if (glfwGetKey(window.self, GLFW_KEY_RIGHT) == GLFW_PRESS)
        dir = Right;

    if (snake.ticks == 20) {
        switch(dir) {
            case Up:
                snake.y -= 2.0f;
                break;
            case Down:
                snake.y += 2.0f;
                break;
            case Left:
                snake.x -= 2.0f;
                break;
            case Right:
                snake.x += 2.0f;
                break;
        }

        snake.ticks = 0;
    }
}

void renderSnake(struct Shader shader) {
    glm_mat4_identity(camera.model); //Reset matrix
    glm_rotate(camera.model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});
    glm_scale(camera.model, (vec3) {0.1, 0.1, 0.05}); //Construct second matrix
    glm_translate(camera.model, (vec3) {snake.x-1.0f, snake.y-1.0f, -21.0f}); //Offset to grid

    setShaderMat4(shader, "model", camera.model);
    _drawSnake();
}

void destroySnake() {
    glDeleteVertexArrays(1, &snake.VAO);
    glDeleteBuffers(1, &snake.VBO);
    glDeleteBuffers(1, &snake.EBO);
}
