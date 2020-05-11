#include "main.h"

#ifndef CONVEXELLIPSE_H
#define CONVEXELLIPSE_H


class Convexellipse {
public:
    Convexellipse() {}
    Convexellipse(float x, float y, float r, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int fl);
    double speed;
private:
    VAO *object;
};

#endif // CONVEXELLIPSE_H
