#ifndef FLOOR_H
#define FLOOR_H

struct Floor {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
};

void initFloor();
void renderFloor(struct Shader shader);
void destroyFloor();

#endif