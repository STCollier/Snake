#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "../world/window.h"
#include "../world/shader.h"
#include "../world/camera.h"

#include "apple.h"
#include "snake.h"

struct Snake snake;

void initSnake() {
    snake.dir = Up; //Initilize direction

    snake.speed = 15;
    snake.size = 1;

    snake.body[0].x = -1.0f;
    snake.body[0].y = -1.0f;

    snake.head = snake.body[0];

    snake.ticks = 0;

    float vertices[] = {
         //positions          //uv        //normals
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 
         1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
         1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 

        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

         1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,

        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f
    };


    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);   

    //normal vectors
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

static void _drawSnake() {

    snake.ticks++;

    if (glfwGetKey(window.self, GLFW_KEY_UP) == GLFW_PRESS && snake.dir != Down)
        snake.dir = Up;
    else if (glfwGetKey(window.self, GLFW_KEY_DOWN) == GLFW_PRESS && snake.dir != Up)
        snake.dir = Down;
    else if (glfwGetKey(window.self, GLFW_KEY_LEFT) == GLFW_PRESS && snake.dir != Right)
        snake.dir = Left;
    else if (glfwGetKey(window.self, GLFW_KEY_RIGHT) == GLFW_PRESS && snake.dir != Left)
        snake.dir = Right;


    if (snake.ticks == snake.speed) {
        // Move the snake's head in the direction specified by the dir variable
        switch(snake.dir) {
            case Up:
                snake.head.y -= 2.0f;
                break;
            case Down:
                snake.head.y += 2.0f;
                break;
            case Left:
                snake.head.x -= 2.0f;
                break;
            case Right:
                snake.head.x += 2.0f;
                break;
        }

        // Move the snake's body
        for (int i = snake.size - 1; i > 0; i--) {
            snake.body[i] = snake.body[i-1];
        }

        snake.body[0] = snake.head;
        
        // Reset ticks
        snake.ticks = 0;
    }

    // Check if the snake eats an apple
    if (snake.head.x == apple.x && snake.head.y == apple.y) {
        int rx, ry;
        int valid = 0;

        while (!valid) {
            rx = (rand() % (10 + 1 + 8) - 8);
            ry = (rand() % (10 + 1 + 8) - 8);
            float ax = (rx + rx % 2) - 1.0f;
            float ay = (ry + ry % 2) - 1.0f;

            // Check if the new apple is not inside the snake's body
            valid = 1;
            for (int i = 0; i < snake.size; i++) {
                if (snake.body[i].x == ax && snake.body[i].y == ay) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                apple.x = ax;
                apple.y = ay;
            }
        }

        snake.size++;

        printf("SCORE: %d\n", snake.size-1);

        if(snake.size > 1) {
            int last = snake.size - 1;
            snake.body[last] = snake.body[last-1];
        }
    }

    // Check if the snake hits its own body
    for (int i = 1; i < snake.size; i++) {
        if (snake.head.x == snake.body[i].x && snake.head.y == snake.body[i].y && snake.size > 2) {
            printf("You Died!\n\n");
            exit(1);
        }
    }

    //Check if snake hits wall
    if (snake.head.x >= 10.0f || snake.head.x <= -10.0f || snake.head.y >= 10.0f || snake.head.y <= -10.0f) {
        printf("You Died!\n\n");
        exit(1);
    }
}

void renderSnake(struct Shader shader) {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, snake.texture);

    useShader(shader);

    glBindVertexArray(snake.VAO);

    for (int i = 0; i < snake.size; i++) {
        glm_mat4_identity(camera.model); //Reset matrix
        glm_rotate(camera.model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});
        glm_scale(camera.model, (vec3) {0.1, 0.1, 0.05}); //Construct second matrix
        glm_translate(camera.model, (vec3) {snake.body[i].x, snake.body[i].y, -21.0f});
        setShaderMat4(shader, "model", camera.model);

        //Makes the head darker with fragment shader pixel manipulation
        if (i == 0 && snake.size >= 2) {
            setShaderVec4(shader, "headColor", 0.0f, 0.0f, 1.0f);
        } else {
            setShaderVec4(shader, "headColor", 1.0f, 1.0f, 1.0f);
        }

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    _drawSnake();
}

void destroySnake() {
    glDeleteVertexArrays(1, &snake.VAO);
    glDeleteBuffers(1, &snake.VBO);
    glDeleteBuffers(1, &snake.EBO);
}
