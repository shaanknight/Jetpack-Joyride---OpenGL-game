#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedx = -4.5;
    speedy = -1;
    projectile = 0;
    
    static const GLfloat vertex_buffer_data[] = {
        -0.25f,-0.25f,-0.25f, // triangle 1 : begin
        -0.25f,-0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f, // triangle 1 : end
         0.0f, 0.0f, 0.0f,
        0.0f, 0.2f, 0.0f,
        0.4f, 0.4f, 0.0f,// triangle 2 : end
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,// 3
        0.0f, 0.0f, 0.0f,
        0.0f, -0.2f, 0.0f,
        0.4f, -0.4f, 0.0f,// 4
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,// 5
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,// 6
        0.0f, 0.0f, 0.0f,
        0.0f, 0.2f, 0.0f,
        0.4f, 0.4f, 0.0f,// 7
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,// 8
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,// 9
        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f,// 10
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,// 11
        0.0f, 0.0f, 0.0f,
        0.0f, -0.2f, 0.0f,
        0.4f, -0.4f, 0.0f,// 12
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.25f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->position.y += speedy/100;
    this->rotation -= speedy;
    this->position.x += speedx/100;
    this->speedx += 0.02;
}

