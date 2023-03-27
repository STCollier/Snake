#include "window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

struct Window window;

static void _sizeCallback() {
    glViewport(0, 0, window.width, window.height);
}


static void _keyboardCallback() {
    if (glfwGetKey(window.self, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.self, 1);
}

void createWindow() {
    window.title = "Snake";
    window.width = 1200;
    window.height = 800;

    window.dt = 0.0f;
    window.lastFrame = 0.0f;



    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Apple users :)
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window.self = glfwCreateWindow(window.width, window.height, "LearnOpenGL", NULL, NULL);
    if (window.self == NULL) {
        printf("Failed to create GLFW window");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window.self);

    //Load all OpenGL function pointers with Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        exit(1);
    }

    glfwSetFramebufferSizeCallback(window.self, _sizeCallback);
    glfwSetKeyCallback(window.self, _keyboardCallback);
}

void terminateWindow() {
    glfwDestroyWindow(window.self);
    glfwTerminate();
}

void updateWindow() {
    _keyboardCallback();

    float currentFrame = glfwGetTime();
    window.dt = currentFrame - window.lastFrame;
    window.lastFrame = currentFrame;

    // render
    glClearColor(0.4f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
}