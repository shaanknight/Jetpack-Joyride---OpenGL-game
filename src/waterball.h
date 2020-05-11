#include "main.h"

#ifndef WATERFALL_H
#define WATERFALL_H


class Waterball {
public:
    Waterball() {}
    Waterball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx,speedy;
private:
    VAO *object;
};

#endif // WATERFALL_H
