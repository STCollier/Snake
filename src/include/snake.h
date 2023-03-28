#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
};

void initSnake();
void drawSnake();
void destroySnake();


#endif