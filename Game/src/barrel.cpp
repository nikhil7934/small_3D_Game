#include "barrel.h"
#include "main.h"

BARREL::BARREL(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90.0f;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        //Face 1
        0.5,0.0,0.00,
        -0.5,0.0,0.00,
        0.5,0.0,-2.0,

        -0.5,0.0,0.00,
        -0.5,0.0,-2.0,
        0.5,0.0,-2.0,

        // Face 2

        -0.5,0.5,0.0,
        -0.5,0.0,0.0,
        -0.5,0.0,-2.0,

        -0.5,0.5,0.0,
        -0.5,0.5,-2.0,
        -0.5,0.0,-2.0,

       // Face 3

        -0.5,0.5,0.0,
        -0.5,0.5,-2.0,
        0.5,0.5,-2.0,

        0.5,0.5,0.0,
        0.5,0.5,-2.0,
        -0.5,0.5,0.0,

        // Face 4

        0.5,0.5,0.0,
        0.5,0.5,-2.0,
        0.5,0.0,-2.0,

        0.5,0.5,0.0,
        0.5,0.0,0.0,
        0.5,0.0,-2.0,

        // Gem on barrel
        0.25,0.25,-2.00,
        -0.25,0.25,-2.00,
        0.25,0.25,-2.25,

        -0.25,0.25,-2.25,
        -0.25,0.25,-2.00,
        0.25,0.25,-2.25

    };
    GLfloat vertex_buffer_data1[] = {
        // Gem on barrel
        0.25,0.25,-2.00,
        -0.25,0.25,-2.00,
        0.25,0.25,-2.25,

        -0.25,0.25,-2.25,
        -0.25,0.25,-2.00,
        0.25,0.25,-2.25

    };

    this->object[0] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_BARREL, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3,vertex_buffer_data1,COLOR_GEM,GL_FILL);
  }

void BARREL::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void BARREL::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void BARREL::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
