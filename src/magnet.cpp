#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x_pos, float y_pos, float r, color_t color) {
    this->position = glm::vec3(x_pos, y_pos, 0);
    this->rotation = 0;
    speed = 1;

    int n;
    n = 20;
    GLfloat g_vertex_buffer_data[9*n];

    float x = 0, y = r, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int p=0;
    for(int i=0;i<(n/2);++i)
    {
        x1 = x*cos(ang)-y*sin(ang);
        y1 = x*sin(ang)+y*cos(ang);
        g_vertex_buffer_data[9*i] = 0.0f;
        g_vertex_buffer_data[9*i+1] = 0.0f;
        g_vertex_buffer_data[9*i+2] = 0.0f;
        g_vertex_buffer_data[9*i+3] = x;
        g_vertex_buffer_data[9*i+4] = y;
        g_vertex_buffer_data[9*i+5] = 0.0f;
        g_vertex_buffer_data[9*i+6] = x1;
        g_vertex_buffer_data[9*i+7] = y1;
        g_vertex_buffer_data[9*i+8] = 0.0f;
        x = x1;
        y = y1;
        p+=9;
    }
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = 0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;

    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = -1*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = -1*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = -1*0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = -1*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = -1*0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;
    g_vertex_buffer_data[p++] = 1.5*r;
    g_vertex_buffer_data[p++] = -1*0.6*r;
    g_vertex_buffer_data[p++] = 0.0f;


    this->object = create3DObject(GL_TRIANGLES, p/3, g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    //this->rotation += rot*speed;
    this->position.x -= speed/100;
    // this->position.y -= speed;
}

