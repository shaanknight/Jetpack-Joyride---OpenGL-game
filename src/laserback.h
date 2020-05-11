#include "main.h"

#ifndef LASERBACK_H
#define LASERBACK_H


class Laserback {
public:
    Laserback() {}
    Laserback(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // LASERBACK_H
