#include "bigboos.h"
#include "main.h"

BMONSTER::BMONSTER(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 20;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        -0.500f,-0.500f,-0.500f, // triangle 1 : begin
        -0.500f,-0.500f, 0.500f,
        -0.500f, 0.500f, 0.500f, // triangle 1 : end
        0.500f, 0.500f,-0.500f, // triangle 2 : begin
        -0.500f,-0.500f,-0.500f,
        -0.500f, 0.500f,-0.500f, // triangle 2 : end
        0.500f,-0.500f, 0.500f,
        -0.500f,-0.500f,-0.500f,
        0.500f,-0.500f,-0.500f,
        0.500f, 0.500f,-0.500f,
        0.500f,-0.500f,-0.500f,
        -0.500f,-0.500f,-0.500f,
        -0.500f,-0.500f,-0.500f,
        -0.500f, 0.500f, 0.500f,
        -0.500f, 0.500f,-0.500f,
        0.500f,-0.500f, 0.500f,
        -0.500f,-0.500f, 0.500f,
        -0.500f,-0.500f,-0.500f,
        -0.500f, 0.500f, 0.500f,
        -0.500f,-0.500f, 0.500f,
        0.500f,-0.500f, 0.500f,
        0.500f, 0.500f, 0.500f,
        0.500f,-0.500f,-0.500f,
        0.500f, 0.500f,-0.500f,
        0.500f,-0.500f,-0.500f,
        0.500f, 0.500f, 0.500f,
        0.500f,-0.500f, 0.500f,
        0.500f, 0.500f, 0.500f,
        0.500f, 0.500f,-0.500f,
        -0.500f, 0.500f,-0.500f,
        0.500f, 0.500f, 0.500f,
        -0.500f, 0.500f,-0.500f,
        -0.500f, 0.500f, 0.500f,
        0.500f, 0.500f, 0.500f,
        -0.500f, 0.500f, 0.500f,
        0.500f,-0.500f, 0.500f
    };
    GLfloat vertex_buffer_data1[] = {
       //face1
        -0.25,0.5,0.25,
         0.25,0.5,0.25,
        0.25,1.0,0.25,

        0.25,1.0,0.25,
        -0.25,1.0,0.25,
        -0.25,0.5,0.25,

    //face 2
        0.25,0.5,0.25,
        0.25,0.5,-0.25,
        0.25,1.0,0.25,

        0.25,1.0,0.25,
        0.25,1.0,-0.25,
        0.25,0.5,-0.25,

    //face 3
        -0.25,1.0,0.25,
        -0.25,0.5,0.25,
        -0.25,0.5,-0.25,

        -0.25,1.0,0.25,
        -0.25,1.0,-0.25,
        -0.25,0.5,-0.25,

  // face 4
        -0.25,0.5,-0.25,
        0.25,0.5,-0.25,
        0.25,1.0,-0.25,

        0.25,1.0,-0.25,
        -0.25,1.0,-0.25,
        -0.25,0.5,-0.25,



        // HANDS FOR MONSTER
        -0.5,0.5,-0.5,
        -0.5,0.5,0.5,
        -0.75,0.5,-0.5,

        -0.5,0.5,-0.5,
        -0.5,0.5,0.5,
        -0.75,0.5,0.5,

        0.5,0.5,-0.5,
        0.5,0.5,0.5,
        0.75,0.5,-0.5,

        0.5,0.5,-0.5,
        0.5,0.5,0.5,
        0.75,0.5,0.5,

    };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BIGBOSS1, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 12*3,vertex_buffer_data1,COLOR_BIGBOSS2,GL_FILL);
}

void BMONSTER::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);//  nikhilendra
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void BMONSTER::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void BMONSTER::tick() {
    this->rotation += speed;
//    if(rand()%2)
//    {
//        this->position.x += 0.1*(cos(this->rotation*(M_PI/180.0f)));
//        this->position.z += 0.1*(sin(this->rotation*(M_PI/180.0f)));
//    }
//    else
//    {
//        this->position.x -= 0.1*(cos(this->rotation*(M_PI/180.0f)));
//        this->position.z -= 0.1*(sin(this->rotation*(M_PI/180.0f)));
//    }
}
