#include "main.h"

#ifndef WHEEL_H
#define WHEEL_H


class Wheel {
public:
    Wheel() {}
    Wheel(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx,speedy;
    int projectile;
private:
    VAO *object;
};

#endif // WHEEL_H
