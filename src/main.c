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

vec3 lightPos = {0.0f, 1.5f, -2.0f};

int main() {

    createWindow();
    initFloor();
    initSnake();
    initApple();
 
    struct Shader mainShader = createShader("res/shaders/main.vs", "res/shaders/main.fs"); //Main shader which actually performs lighting
    struct Shader lightShader = createShader("res/shaders/light.vs", "res/shaders/light.fs"); //This is separate for the cube, does not perform lighting!!

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,    

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };

    //LIGHTING
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window.self)) {
        updateWindow();

        useShader(mainShader);
        setShaderVec3(mainShader, "lightPos", lightPos[0], lightPos[1], lightPos[2]);
        setShaderVec3(mainShader, "lightColor", 1.0f, 1.0f, 1.0f);


        useCamera(mainShader);

        renderFloor(mainShader);
        renderSnake(mainShader);
        renderApple(mainShader);

        useShader(lightShader);
        setShaderMat4(lightShader, "projection", camera.projection);
        setShaderMat4(lightShader, "view", camera.view);

        glm_mat4_identity(camera.model); //Reset matrix
        glm_translate(camera.model, lightPos);
        glm_scale(camera.model, (vec3) {0.5f, 0.5f, 0.5f});

        setShaderMat4(lightShader, "model", camera.model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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