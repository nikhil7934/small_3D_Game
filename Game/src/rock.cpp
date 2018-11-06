#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y,float z,float side, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        side*-1.0f,side*-1.0f,side*-1.0f, // triangle 1 : begin
        side*-1.0f,side*-1.0f,side* 1.0f,
        side*-1.0f,side*1.0f,side* 1.0f, // triangle 1 : end
        side*1.0f,side* 1.0f,side*-1.0f, // triangle 2 : begin
        side*-1.0f,side*-1.0f,side*-1.0f,
        side*-1.0f,side*1.0f,side*-1.0f, // triangle 2 : end
        side*1.0f,side*-1.0f,side*1.0f,
        side*-1.0f,side*-1.0f,side*-1.0f,
        side*1.0f,side*-1.0f,side*-1.0f,
        side*1.0f, side*1.0f,side*-1.0f,
        side*1.0f,side*-1.0f,side*-1.0f,
        side*-1.0f,side*-1.0f,side*-1.0f,
        side*-1.0f,side*-1.0f,side*-1.0f,
        side*-1.0f,side*1.0f,side*1.0f,
        side*-1.0f,side*1.0f,side*-1.0f,
        side*1.0f,side*-1.0f,side*1.0f,
        side*-1.0f,side*-1.0f,side*1.0f,
        side*-1.0f,side*-1.0f,side*-1.0f,
        side*-1.0f,side*1.0f, side*1.0f,
        side*-1.0f,side*-1.0f, side*1.0f,
        side*1.0f,side*-1.0f,side*1.0f,
        side*1.0f, side*1.0f, side*1.0f,
        side*1.0f,side*-1.0f,side*-1.0f,
        side*1.0f, side*1.0f,side*-1.0f,
        side*1.0f,side*-1.0f,side*-1.0f,
        side*1.0f, side*1.0f, side*1.0f,
        side*1.0f,side*-1.0f, side*1.0f,
        side*1.0f, side*1.0f, side*1.0f,
        side*1.0f, side*1.0f,side*-1.0f,
        side*-1.0f, side*1.0f,side*-1.0f,
        side*1.0f, side*1.0f, side*1.0f,
        side*-1.0f, side*1.0f,side*-1.0f,
        side*-1.0f, side*1.0f, side*1.0f,
        side*1.0f, side*1.0f, side*1.0f,
        side*-1.0f, side*1.0f, side*1.0f,
        side*1.0f,side*-1.0f, side*1.0f

    };
    int wet = rand()%5;
    switch(wet)
    {
        case 0:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
            break;
        case 1:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_ROCK1, GL_FILL);
            break;
        case 2:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_ROCK2, GL_FILL);
            break;
        case 3:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_ROCK3, GL_FILL);
            break;
        case 4:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_ROCK4, GL_FILL);
            break;
        default:
            this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
            break;

    }/*

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);*/
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Rock::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Rock::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float size = 0.25;
    bounding_box_t bbox = { x, y, z, size};
    return bbox;
}

