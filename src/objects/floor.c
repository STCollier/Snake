#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include <stdio.h>

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "../world/camera.h"
#include "../world/shader.h"
#include "floor.h"

struct Floor _floor;

void initFloor() {
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

    glGenTextures(1, &_floor.texture);
    glBindTexture(GL_TEXTURE_2D, _floor.texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // load image, create texture and generate mipmaps

    int width, height, nrChannels;
    
    unsigned char *data = stbi_load("res/textures/floor.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);   

    //normal vectors
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);   
    

}

static void _drawFloor() {
    glBindTexture(GL_TEXTURE_2D, _floor.texture);

    glBindVertexArray(_floor.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void renderFloor(struct Shader shader) {
    glm_mat4_identity(camera.model);
    glm_rotate(camera.model, glm_rad(90.0f), (vec3) {1.0f, 0.0f, 0.0f});

    setShaderMat4(shader, "model", camera.model);
    _drawFloor();
}

void destroyFloor() {
    glDeleteVertexArrays(1, &_floor.VAO);
    glDeleteBuffers(1, &_floor.VBO);
    glDeleteBuffers(1, &_floor.EBO);
}