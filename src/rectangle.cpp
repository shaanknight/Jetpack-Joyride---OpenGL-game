#include "rectangle.h"
#include "main.h"

Rectangle::Rectangle(float x, float y, float speedx, float speedy, float x1 , float yy1, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    
    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        x1, 0.0f, 0.0f,
        x1, yy1, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, yy1, 0.0f,
        x1, yy1, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.25f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rectangle::tick(int mrk) {
    // handling y co-ordinate
    if(mrk == 1)
    {
        if(abs(this->position.y + 1.75) < 1e-1 && this->speedy <= 0)
        {   // lowermost point for player
            this->position.y = -1.75;
            this->speedy = 0;
        }
        else
        {
            this->speedy -= 0.02;
            this->position.y += speedy/10;
            if((this->position.y - 2.25) > 1e-6)
            {   // uppermost point for player
                this->speedy = 0;
                this->position.y = 2.25;
            }
        } 
    }
    
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

