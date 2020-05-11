#include "main.h"

#ifndef STAR_H
#define STAR_H


class Star {
public:
    Star() {}
    Star(float x, float y, float r, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int rot);
    double speed;
private:
    VAO *object;
};

#endif // STAR_H
