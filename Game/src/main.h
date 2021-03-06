#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <climits>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
bool rock_collision(bounding_box_t a, bounding_box_t b);
bool boat_barrel_collision(int rt);
bool boat_monster_collision(int rt);
bool fireball_monster_collision(int rt,int mt);
bool boat_booster_collision(int rt);
bool boat_Bmonster_collision();
bool fireball_Bmonster_collision(int rt);


extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

void firing_balls();
void firing_Backballs();
void screen_zoom_in();
void screen_zoom_out();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_WATER;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_ROCK1;
extern const color_t COLOR_ROCK2;
extern const color_t COLOR_ROCK3;
extern const color_t COLOR_ROCK4;
extern const color_t COLOR_CANNON;
extern const color_t COLOR_PURERED;
extern const color_t COLOR_BARREL;
extern const color_t COLOR_GEM;
extern const color_t COLOR_FIREBALL;
extern const color_t COLOR_BOOST;
extern const color_t COLOR_BIGBOSS1;
extern const color_t COLOR_BIGBOSS2;


#endif
