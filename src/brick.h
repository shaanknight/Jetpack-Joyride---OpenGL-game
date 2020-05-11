#include "main.h"

#ifndef BRICK_H
#define BRICK_H


class Brick {
public:
    Brick() {}
    Brick(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BRICK_H
