#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    float x, y;
    int speed;
};

void initSnake();
void drawSnake();
void destroySnake();
void moveSnake(int direction);

extern struct Snake snake;

#endif