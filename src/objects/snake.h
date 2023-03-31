#ifndef SNAKE_H
#define SNAKE_H

struct Position {
	int x;
	int y;
};

struct Snake {
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    struct Position body[100];
    struct Position head;
    int size;
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