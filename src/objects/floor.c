#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include <stdio.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "floor.h"

struct Floor _floor;

void initFloor() {
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

    glGenTextures(1, &_floor.texture);
    glBindTexture(GL_TEXTURE_2D, _floor.texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    // load image, create texture and generate mipmaps

    int width, height, nrChannels;
    
    unsigned char *data = stbi_load("res/textures/floor.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Could not load floor texture\n");
    }

    stbi_image_free(data);

    glGenVertexArrays(1, &_floor.VAO);
    glGenBuffers(1, &_floor.VBO);
    glGenBuffers(1, &_floor.EBO);

    glBindVertexArray(_floor.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _floor.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //OH MY GOSH ITS GL_ELEMENT_ARRAY_BUFFER INSTEAD OF GL_ARRAY_BUFFER FINALLY
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _floor.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void drawFloor() {
    glBindTexture(GL_TEXTURE_2D, _floor.texture);

    glBindVertexArray(_floor.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void destroyFloor() {
    glDeleteVertexArrays(1, &_floor.VAO);
    glDeleteBuffers(1, &_floor.VBO);
    glDeleteBuffers(1, &_floor.EBO);
}