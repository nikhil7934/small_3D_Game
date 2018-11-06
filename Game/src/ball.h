#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z,float side,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float dirroc;
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int back;
private:
    VAO *object;
};

#endif // BALL_H
