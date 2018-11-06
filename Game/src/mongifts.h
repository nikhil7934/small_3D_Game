#include "main.h"

#ifndef MONGIFT_H
#define MONGIFT_H


class MONGIFT {
public:
    MONGIFT() {}
    MONGIFT(float x, float y,float z, color_t color);
    int booster;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object[2];
};

#endif // MONGIFT_H
