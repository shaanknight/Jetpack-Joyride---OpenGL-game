#include "main.h"

#ifndef LASERCAP_H
#define LASERCAP_H


class Lasercap {
public:
    Lasercap() {}
    Lasercap(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // LASERCAP_H
