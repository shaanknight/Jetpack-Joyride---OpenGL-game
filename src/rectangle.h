#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y, float speedx, float speedy, float x1, float y1, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int mrk);
    double speedx,speedy;
    int projectile;
private:
    VAO *object;
};

#endif // RECTANGLE_H
