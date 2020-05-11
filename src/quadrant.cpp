#include "quadrant.h"
#include "main.h"

Quadrant::Quadrant(float x_pos, float y_pos, float speedx, float speedy, float x, float y, color_t color) {
    this->position = glm::vec3(x_pos, y_pos, 0);
    this->rotation = 0;

    int n;
    n = 20;
    this->str = 0;
    GLfloat g_vertex_buffer_data[9*n];

    float ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    for(int i=0;i<(n/4);++i)
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
    }

    this->object = create3DObject(GL_TRIANGLES, (n/4)*3, g_vertex_buffer_data, color, GL_FILL);
}

void Quadrant::draw(glm::mat4 VP) {
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

void Quadrant::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Quadrant::tick(int mrk)
{
    if(mrk == 1)
    {
        if(this->str == 0)
        {
            this->speedy = 0;
            this->str = 1;
        }
        if(abs(this->position.y + 2.25) < 1e-1 && this->speedy <= 0)
        {   // lowermost point for player
            this->position.y = -2.25;
            this->speedy = 0;
        }
        else
        {
            this->speedy -= 0.02;
            this->position.y += speedy/10;
            if((this->position.y - 1.75) > 1e-6)
            {   // uppermost point for player
                this->speedy = 0;
                this->position.y = 1.75;
            }
        }
    }
    //this->rotation += rot*speed;
    //this->position.x -= speed/100;
    // this->position.y -= speed;
}

