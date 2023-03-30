#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

#include "window.h"
#include "shader.h"
#include "camera.h"

//Define globally
struct Camera camera;

void useCamera(struct Shader shader) {
    useShader(shader);

    glm_mat4_identity(camera.projection);
    glm_perspective(glm_rad(window.fov), (float) window.width / (float) window.height, 0.1f, 100.0f, camera.projection); //Make sure to convert to floats for float division
    //glm_ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f, projection);
    setShaderMat4(shader, "projection", camera.projection);

    glm_mat4_identity(camera.view);
    glm_translate(camera.view, (vec3) {0.0f, -0.4f, -5.0f});
    glm_rotate(camera.view, glm_rad(55.0f), (vec3) {1.0f, 0.0f, 0.0f});
    setShaderMat4(shader, "view", camera.view);
}