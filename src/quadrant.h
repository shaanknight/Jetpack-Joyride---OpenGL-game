#include "main.h"

#ifndef QUADRANT_H
#define QUADRANT_H


class Quadrant {
public:
    Quadrant() {}
    Quadrant(float x_pos, float y_pos, float speedx, float speedy, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int mrk);
    double speedx,speedy;
    int str;
private:
    VAO *object;
};

#endif // QUADRANT_H
