#include "main.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle {
public:
    Triangle() {}
    Triangle(float x, float y, float speedx, float speedy, float x1, float y1, float x2, float y2, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int mrk);
    double speedx,speedy;
    int str;
    int projectile;
private:
    VAO *object;
};

#endif // TRIANGLE_H
