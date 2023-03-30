#ifndef APPLE_H
#define APPLE_H

struct Apple {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;

    float x, y;
};

void initApple();
void renderApple(struct Shader shader);
void destroyApple();

#endif