#include "main.h"

#ifndef CONCAVEELLIPSE_H
#define CONCAVEELLIPSE_H


class Concaveellipse {
public:
    Concaveellipse() {}
    Concaveellipse(float x, float y, float r, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int fl);
    double speed;
private:
    VAO *object;
};

#endif // CONCAVEELLIPSE_H
