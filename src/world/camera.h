#ifndef CAMERA_H
#define CAMERA_H

#include "cglm/cglm.h"
#include "cglm/call.h"

#include "shader.h"

struct Camera {
    mat4 projection;
    mat4 view;
    mat4 model;
};

void useCamera(struct Shader shader);

extern struct Camera camera;

#endif