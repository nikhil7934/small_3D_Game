#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class MONSTER {
public:
    MONSTER() {}
    MONSTER(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object[2];
};

#endif // MONSTER_H
