#include "triangle.h"
#include "main.h"

Triangle::Triangle(float x, float y, float speedx, float speedy, float x1 , float yy1, float x2, float yy2, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    printf("%f %f %f %f\n",x1,yy1,x2,yy2);
    this->str = 0;
    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        x1, yy1, 0.0f,
        x2, yy2, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
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

void Triangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Triangle::tick(int mrk) {
    // handling y co-ordinate
    if(mrk == 0)
    {
        printf("marked 0\n");
        this->speedx = 1;
        printf("fsdf%f \n", this->position.x);
        this->position.x -= 1;
        printf("sfa%f \n", this->position.x);
    }
    if(mrk == 1)
    {
        if(this->str == 0)
        {
            this->speedy = 0;
            this->str = 1;
        }
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
    else if(mrk == 2)
    {
        if(abs(this->position.y + 1.55) < 1e-1 && this->speedy <= 0)
        {   // lowermost point for player
            this->position.y = -1.55;
            this->speedy = 0;
        }
        else
        {
            this->speedy -= 0.02;
            this->position.y += speedy/10;
            if((this->position.y - 2.45) > 1e-6)
            {   // uppermost point for player
                this->speedy = 0;
                this->position.y = 2.45;
            }
        } 
    }
    else if(mrk == 3)
    {
        if(abs(this->position.y + 2.0) < 1e-1 && this->speedy <= 0)
        {   // lowermost point for player
            this->position.y = -2.0;
            this->speedy = 0;
        }
        else
        {
            this->speedy -= 0.02;
            this->position.y += speedy/10;
            if((this->position.y - 2.0) > 1e-6)
            {   // uppermost point for player
                this->speedy = 0;
                this->position.y = 2.0;
            }
        }
    }
    else if(mrk == 4)
    {
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
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

