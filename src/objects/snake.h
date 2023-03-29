#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    float x, y;
    int speed;
    int ticks;
};

typedef enum {
    Up,
    Down,
    Left,
    Right
} snakeDir;

void initSnake();
void drawSnake();
void destroySnake();
void moveSnake();

extern struct Snake snake;

#endif