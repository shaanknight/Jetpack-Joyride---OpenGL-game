#include "main.h"

#ifndef BORDERLINE_H
#define BORDERLINE_H


class Borderline {
public:
    Borderline() {}
    Borderline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BORDERLINE_H
