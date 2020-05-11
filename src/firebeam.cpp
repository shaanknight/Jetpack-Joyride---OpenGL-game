#include "firebeam.h"
#include "main.h"

Firebeam::Firebeam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.1f,-0.1f,-0.1f, // triangle 1 : begin
        -0.1f,-0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f, // triangle 1 : end
        0.5f, 0.014f,-0.1f, // triangle 2 : begin
        -0.5f,-0.014f,-0.1f,
        -0.5f, 0.014f,-0.1f, // triangle 2 : end
        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,// 3
        0.5f, 0.014f,-0.1f,
        0.5f,-0.014f,-0.1f,
        -0.5f,-0.014f,-0.1f,// 4
        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,// 5
        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,// 6
        -0.5f, 0.014f, 0.1f,
        -0.5f,-0.014f, 0.1f,
        0.5f,-0.014f, 0.1f,// 7
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,// 8
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,// 9
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f,-0.1f,// 10
        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,// 11
        0.5f, 0.014f, 0.1f,
        -0.5f, 0.014f, 0.1f,
        0.5f,-0.014f, 0.1f// 12
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.1f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    //this->rotation += speed;
    this->position.x -= (abs(speed))/100;
    if((this->position.y - 2.9) > 1e-6 && speed > 0)
    {   // uppermost point for beam
        this->speed *= -1;
        return;
    }
    else if((this->position.y + 2.9) < 1e-6 && speed < 0)
    {   // uppermost point for player
        this->speed *= -1;
        return;
    }
    this->position.y += speed/10;
    
    // this->position.y -= speed;
}

