#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    speed = 0;
    float xb,yb,zb;
    xb=1.00,yb=0.1,zb=2.0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        // Front Triangle
        xb*-1.0f,yb*0.0f,zb*-1.0f,
        xb*1.0f, yb*0.0f,zb*-1.0f,
        xb*0.0f, yb*0.0f,zb*(-1-0.866),

        //Face 1
        xb*-1.0f,yb*0.0f,zb*-1.0f, // triangle 1 : begin
        xb*1.0f,yb*0.0f, zb*-1.0f,
        xb*-1.0f, yb*0.0f, zb*1.0f, // triangle 1 : end


         xb*-1.0f, yb*0.0f,zb*1.0f, // triangle 2 : begin
        xb*1.0f,yb*0.0f,zb*1.0f,
        xb*1.0f, yb*0.0f,zb*-1.0f, // triangle 2 : end

        //Face 2
       xb*-1.0f,yb*0.0f, zb*1.0f,
        xb*-1.0f,yb*-1.0f,zb*1.0f,
        xb*-1.0f,yb*-1.0f,zb*-1.0f,

        xb*-1.0f, yb*0.0f, zb* 1.0f,
        xb*-1.0f, yb*0.0f, zb*-1.0f,
        xb*-1.0f,yb*-1.0f, zb*-1.0f,

        // Face 3
        xb*-1.0f,yb*0.0f,zb*1.0f,
        xb*1.0f, yb*0.0f, zb*1.0f,
        xb*-1.0f, yb*-1.0f,zb*1.0f,

        xb*-1.0f,yb*-1.0f, zb*1.0f,
        xb*1.0f,yb*-1.0f, zb*1.0f,
        xb*1.0f,yb*0.0f,zb*1.0f,

        //Face 4
        xb*1.0f, yb*0.0f, zb*1.0f,
        xb*1.0f, yb*0.0f, zb*-1.0f,
        xb*1.0f,yb*-1.0f, zb*-1.0f,

        xb*1.0f, yb*0.0f, zb*1.0f,
        xb*1.0f,yb*-1.0f,zb*1.0f,
        xb*1.0f, yb*-1.0f,zb*-1.0f,

        //Face 5
        xb*-1.0f,yb*0.0f,zb*-1.0f,
        xb*-1.0f, yb*-1.0f, zb*-1.0f,
        xb*1.0f,yb*0.0f, zb*-1.0f,

        xb*1.0f, yb*0.0f, zb*-1.0f,
        xb*1.0f, yb*-1.0f,zb*-1.0f,
        xb*-1.0f, yb*-1.0f,zb*-1.0f,

        // Face 6
        xb*-1.0f, yb*-1.0f, zb*1.0f,
        xb*-1.0f, yb*-1.0f,zb*-1.0f,
        xb*1.0f, yb*-1.0f, zb*-1.0f,

        xb*-1.0f, yb*-1.0f, zb*1.0f,
        xb*1.0f, yb*-1.0f, zb*1.0f,
        xb*1.0f,yb*-1.0f, zb*-1.0f


    };

    // Side of the boats as rectangles

    GLfloat vertex_buffer_data1[] = {
        // Sides the
        xb*1.0,0.5,zb*1.0,
        xb*1.0,0.5,zb*-1.0,
        xb*1.0,0.0,zb*1.0,

        xb*1.0,0.5,zb*-1.0,
        xb*1.0,0.0,zb*1.0,
        xb*1.0,0.0,zb*-1.0,

        xb*-1.0,0.0,zb*1.0,
        xb*-1.0,0.5,zb*-1.0,
        xb*-1.0,0.5,zb*1.0,

        xb*-1.0,0.0,zb*-1.0,
        xb*-1.0,0.0,zb*1.0,
        xb*-1.0,0.5,zb*-1.0,


        // Front side
        xb*-1.0f,-0.1f,zb*-1.0f,
        xb*0.0f, -0.1f,zb*(-1-0.866),
        xb*-1.0f,0.5f,zb*-1.0f,

        xb*0.0f, -0.1f,zb*(-1-0.866),
        xb*0.0f, 0.5f,zb*(-1-0.866),
        xb*-1.0f,0.5f,zb*-1.0f,


        xb*1.0f, -0.10f,zb*-1.0f,
        xb*0.0f, -0.10f,zb*(-1-0.866),
        xb*1.0f, 0.5f,zb*-1.0f,

        xb*0.0f, -0.10f,zb*(-1-0.866),
        xb*0.0f, 0.5f,zb*(-1-0.866),
        xb*1.0f, 0.5f,zb*-1.0f,

        //pole at center

        0.05,4.0,+0.22,
        0.00,0.0,+0.22,
        0.05,0.0,+0.22,

        0.00,4.0,+0.22,
        0.00,0.0,+0.22,
        0.05,4.0,+0.22,

        -0.05,4.0,0.22,
        0.00,0.0,0.22,
        -0.05,0.0,0.22,

        0.00,4.0,0.22,
        0.00,0.0,0.22,
        -0.05,4.0,0.22,

    };

    GLfloat vertex_buffer_data2[] = {

        0.0,4.0,+0.22,
        0.0,1.00,+0.22,
        0.0,1.00,3.5,

    };

    GLfloat vertex_buffer_data3[] =
    {
        // Support
      -0.75,0.0,-2.00,
        0.75,0.0,-2.00,
       0.75,0.5,-2.00,

        -0.75,0.0,-2.00,
         -0.75,0.5,-2.00,
         0.75,0.5,-2.00,

        // Face 1
        0.25,0.5,-2.00,
        -0.25,0.5,-2.00,
        0.25,0.5,-4.0,

        -0.25,0.5,-2.00,
        -0.25,0.5,-4.0,
        0.25,0.5,-4.0,

        // Face 2

        -0.25,1.0,-2.0,
        -0.25,0.5,-2.0,
        -0.25,0.5,-4.0,

        -0.25,1.0,-2.0,
        -0.25,1.0,-4.0,
        -0.25,0.5,-4.0,

       // Face 3

        -0.25,1.0,-2.0,
        -0.25,1.0,-4.0,
        0.25,1.0,-4.0,

        0.25,1.0,-2.0,
        0.25,1.0,-4.0,
        -0.25,1.0,-2.0,

        // Face 4

        0.25,1.0,-2.0,
        0.25,1.0,-4.0,
        0.25,0.5,-4.0,

        0.25,1.0,-2.0,
        0.25,0.5,-2.0,
        0.25,0.5,-4.0,
    };


    GLfloat vertex_buffer_data4[] =
    {
        // Support
      -0.75,0.0,1.00,
        0.75,0.0,1.00,
       0.75,0.5,1.00,

        -0.75,0.0,1.00,
         -0.75,0.5,1.00,
         0.75,0.5,1.00,

        // Face 1
        0.25,0.5,1.00,
        -0.25,0.5,1.00,
        0.25,0.5,3.00,

        -0.25,0.5,1.00,
        -0.25,0.5,3.0,
        0.25,0.5,3.0,

        // Face 2

        -0.25,1.0,1.0,
        -0.25,0.5,1.0,
        -0.25,0.5,3.0,

        -0.25,1.0,1.0,
        -0.25,1.0,3.0,
        -0.25,0.5,3.0,

       // Face 3

        -0.25,1.0,1.0,
        -0.25,1.0,3.0,
        0.25,1.0,3.0,

        0.25,1.0,1.0,
        0.25,1.0,3.0,
        -0.25,1.0,1.0,

        // Face 4

        0.25,1.0,1.0,
        0.25,1.0,3.0,
        0.25,0.5,3.0,

        0.25,1.0,1.0,
        0.25,0.5,1.0,
        0.25,0.5,3.0,
    };



    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1,COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2,COLOR_WHITE, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data3,COLOR_CANNON, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1,COLOR_BOOST, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data4,COLOR_CANNON, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    if(boostacitivate)
        draw3DObject(this->object[4]);
    if(upgrade)
        draw3DObject(this->object[5]);
}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float size1 = 0.5 ,size2 = 0.5;
    bounding_box_t bbox = { x, y, z, size1 };
    return bbox;
}

