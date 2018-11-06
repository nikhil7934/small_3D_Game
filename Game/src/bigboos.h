#include "main.h"

#ifndef BMONSTER_H
#define BMONSTER_H


class BMONSTER {
public:
    BMONSTER() {}
    BMONSTER(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object[2];
};

#endif // BMONSTER_H
