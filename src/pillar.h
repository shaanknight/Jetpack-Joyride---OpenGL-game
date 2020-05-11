#include "main.h"

#ifndef PILLAR_H
#define PILLAR_H


class Pillar {
public:
    Pillar() {}
    Pillar(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // PILLAR_H
