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
void renderSnake(struct Shader shader);
void destroySnake();

extern struct Snake snake;

#endif