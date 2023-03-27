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

    while (!glfwWindowShouldClose(window.self)) {
        updateWindow();


        glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    terminateWindow();
   
    return 0;
}