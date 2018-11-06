#include "main.h"
#include "timer.h"
#include "ball.h"
#include "rock.h"
#include "water.h"
#include "boat.h"
#include "monster.h"
#include "barrel.h"
#include "mongifts.h"
#include "bigboos.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
// Initializing the Models

Water water1,water2,water3;
Ball ball[50];
int ballthrown[50];
Boat boat1;
Rock rock[50];
MONSTER monster[50];
BARREL barrel[50];
MONGIFT mongifts[50];
int giftrelease[50];
BMONSTER bigboss;
int bigdead = 0;


int healthpoints = 600;
int score = 0;
int ticboost = 0;
int monstercount = 0;
float radius=2,camera=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

//int normalview = 1;
int topview =  0;
int boatview = 0;
int towerview = 0;
int Fcamview = 1;
int Hcamview = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    if(Fcamview) // + +
    {
        glm::vec3 eye ( boat1.position.x+5*sin(boat1.rotation*(M_PI/180.0f)), boat1.position.y+2.50, boat1.position.z+5*cos(boat1.rotation*(M_PI/180.0f)));
        //glm::vec3 eye(0,0,3);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (boat1.position.x, boat1.position.y, boat1.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);
        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if(boatview)
    {
        glm::vec3 eye ( boat1.position.x, boat1.position.y+1.8, boat1.position.z);
        //glm::vec3 eye(0,0,3);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (boat1.position.x-5*sin(boat1.rotation*(M_PI/180.0f)), boat1.position.y, boat1.position.z-5*cos(boat1.rotation*(M_PI/180.0f)));
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);
        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if(topview)
    {
        glm::vec3 eye (boat1.position.x, 15, boat1.position.z);
        //glm::vec3 eye(0,0,3);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (boat1.position.x, boat1.position.y, boat1.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 0, -1);
        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if(Hcamview)
    {
        float bbb = camera*M_PI/180;
        glm::vec3 eye ( radius*cos(bbb),15 , radius*sin(bbb) );
        //glm::vec3 eye(0,0,3);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (boat1.position.x,boat1.position.y,boat1.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (cos(bbb), 1, sin(bbb));
        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if(towerview)
    {
        glm::vec3 eye ( 0.00, 0.00, 10.00 );
        //glm::vec3 eye(0,0,3);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (boat1.position.x, boat1.position.y, boat1.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);
        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0;i<20;i++)
    {
        if(ballthrown[i])
            ball[i].draw(VP);
    }
    boat1.draw(VP);
   // ball1.draw(VP);
    for(int i=0;i<50;i++)
    {
        barrel[i].draw(VP);
    }
    for(int i=0;i<50;i++)
    {
        rock[i].draw(VP);
    }
    for(int i=0;i<50;i++)
    {
        monster[i].draw(VP);
        if(giftrelease[i])
        {
            mongifts[i].draw(VP);
        }
    }
    if(bigdead==0 && monstercount>=4)
    {
        bigboss.draw(VP);
    }
    water1.draw(VP);
    water2.draw(VP);
    water3.draw(VP);


}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int a     = glfwGetKey(window, GLFW_KEY_A);
    int s     = glfwGetKey(window, GLFW_KEY_S);
    int w     = glfwGetKey(window, GLFW_KEY_W);
    int d     = glfwGetKey(window, GLFW_KEY_D);
    int spacej     = glfwGetKey(window, GLFW_KEY_SPACE);

    if(a)
    {
        camera += 5;
    }
    if(d)
    {
        camera -= 5;
    }
    if(w)
    {
        radius += 2;
    }
    if(s)
    {
        radius -= 2;
    }
    if(spacej)
    {

    }
    if (left)
    {
        boat1.rotation += 3;

    }
    if(right)
    {
        boat1.rotation -= 3;

    }
    if(up)
    {
        boat1.position.z -= 0.2*(cos(boat1.rotation*(M_PI/180.0f)));
        boat1.position.x -= 0.2*(sin(boat1.rotation*(M_PI/180.0f)));

    }
    if(down)
    {
        boat1.position.z += 0.2*(cos(boat1.rotation*(M_PI/180.0f)));
        boat1.position.x += 0.2*(sin(boat1.rotation*(M_PI/180.0f)));

    }

    int z = glfwGetKey(window,GLFW_KEY_Z);// Top-View
    int n = glfwGetKey(window,GLFW_KEY_N);// Normal-View
    int h = glfwGetKey(window,GLFW_KEY_H);// Hcam-View
    int c = glfwGetKey(window,GLFW_KEY_C);// Boat/Cannon-View
    int tower = glfwGetKey(window,GLFW_KEY_T);// Tower-View;
    if(z)
    {
        Fcamview = 0;
        towerview = 0;
        Hcamview = 0;
        boatview = 0;
        topview = 1;
    }
    if(n)
    {
        Fcamview = 1;
        towerview = 0;
        Hcamview = 0;
        boatview = 0;
        topview = 0;
    }
    if(h)
    {
        Fcamview = 0;
        towerview = 0;
        Hcamview = 1;
        boatview = 0;
        topview = 0;
    }
    if(c)
    {
        Fcamview = 0;
        towerview = 0;
        Hcamview = 0;
        boatview = 1;
        topview = 0;
    }
    if(tower)
    {
        Fcamview = 0;
        towerview = 1;
        Hcamview = 0;
        boatview = 0;
        topview = 0;
    }

}

void tick_elements() {

    // For bigboss rotate
    if(bigdead==0 && monstercount >= 4)
    {
        bigboss.tick();
    }
    // For the monster to rotate about itself;
    if(ticboost == 310)
    {
        boat1.boatsp = 0.2f;
        boat1.boostacitivate = 0;
        ticboost = 0;
    }
    else
    {
        ticboost += 1;
    }
    for(int i=0;i<50;i++)
    {
        monster[i].tick();
    }
    // For the fireball to rotate about itself;
    for(int i=0;i<20;i++)
    {
        if(ballthrown[i])
        {
            ball[i].tick();
        }
    }
    // BIGBOSS COLLISION with BOAT

    if(boat_Bmonster_collision())
    {
         healthpoints -= 100;
    }
    // Fire Ball
    for(int d=0;d<50;d++)
    {
        if(ballthrown[d])
        {
                if(fireball_Bmonster_collision(d))
                {
                    score += 100;
                    ballthrown[d] = 0;
                    bigdead = 1;
                    for(int z=0;z<50;z++)
                    {
                        if(giftrelease[z]==0)
                        {
                            giftrelease[z]=1;
                            mongifts[z].position.x = bigboss.position.x;
                            mongifts[z].position.z = bigboss.position.z;
                            mongifts[z].booster = 0;
                            break;
                        }
                    }
                }
        }
    }

    // For the collision between monster , Boat and Fireballs;
    for(int i=0;i<50;i++)
    {
        if(boat_monster_collision(i))
        {
            healthpoints -= 10;
        }
        for(int j=0;j<50;j++)
        {
            if(fireball_monster_collision(i,j))
            {
                score += 100;
                ballthrown[i] = 0;
                monstercount += 1;
                for(int z=0;z<50;z++)
                {
                    if(giftrelease[z]==0)
                    {
                        giftrelease[z]=1;
                        mongifts[z].position.x = monster[j].position.x;
                        mongifts[z].position.z = monster[j].position.z;
                        mongifts[z].booster = 1;
                        break;
                    }
                }
                int fghjt = rand()%2;
                if(fghjt)
                {
                    monster[j].position.x += 15;
                    monster[j].position.z -= 15;
                }
                else
                {
                    monster[j].position.x -= 15;
                    monster[j].position.z += 15;
                }

            }
        }
    }
    // For the collision between the rocks and boat;
    // and also the boat and barrels
    for(int i=0;i<50;i++)
    {
        if(rock_collision(boat1.bounding_box(),rock[i].bounding_box()))
        {
            healthpoints -= 5;
        }
        if(boat_barrel_collision(i))
        {
            if(i%2)
            {
                barrel[i].position.x += 50;
                barrel[i].position.z -= 50;
            }
            else
            {
                barrel[i].position.x -= 50;
                barrel[i].position.z += 50;
            }
            healthpoints += 50;
        }
        if(boat_booster_collision(i))
        {
            giftrelease[i]=0;
            if(mongifts[i].booster==0)
            {
              boat1.upgrade = 1;
            }
            boat1.boostacitivate = 1;

            // To increase the speed for atmost 1000 ticks;
            if(ticboost==0)
            {
                boat1.boatsp = 4.5f;
                ticboost +=1;

            }
            else
            {
                ticboost = 1;
            }
        }
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */


    // Create the models
    water1  =  Water(0.00,-8.00,0.00,COLOR_WATER);
    boat1   =  Boat(0.00,-5.50,0.00,COLOR_BROWN);
    boat1.boatsp = 0.2f;
    boat1.upgrade = 0;
    boat1.boostacitivate = 0;
    water2  =  Water(600.00,-8.00,0.00,COLOR_WATER);
    water3  =  Water(-600.00,-8.00,0.00,COLOR_WATER);
    bigboss =  BMONSTER(30.0,-5.0,0.0,COLOR_GREEN);
    for(int i=0;i<50;i++)
    {
        mongifts[i] = MONGIFT(4.0,-7.50,0.0,COLOR_BARREL);
        giftrelease[i] = 0;
    }

    // Rocks and Barrels are kept at the random positions;
    for(int i=0;i<50;i++)
    {
        float rx = rand()%100;
        float rz = rand()%100;
        int check = rand()%2;
//        int check1 = rand()%2;
        if(check/*&&check1*/)
        {
            rock[i]   =  Rock(rx+1,-6.00,(rz+1),0.5,COLOR_BLACK);
            barrel[i] = BARREL(rx+10,-7.50,(rz+10),COLOR_BARREL);
        }
        else
        {
            rock[i]   =  Rock(-1*(rx+1),-6.00,-1*(rz+1),0.5,COLOR_BLACK);
            barrel[i] = BARREL(-1*(rx+10),-7.50,-1*(rz+10),COLOR_BARREL);
        }
    }
    // FireBalls are initialized at a place
    // They are Drawn only when Key "F" is pressed They are 50 balls to use;
    for(int i=0;i<50;i++)
    {
        ball[i] = Ball(0.0,-5.0,-3.0,0.2,COLOR_FIREBALL);
    }
    // Monster are Kept at random Positions



    // Motion TO BE DONE



    for(int i=0;i<50;i++)
    {
        float rx = rand()%100;
        float rz = rand()%100;
        float fg = rand()%2;
        if(fg)
            monster[i] = MONSTER(rz+10,-5.5,rx+10,COLOR_GREEN);
        else
            monster[i] = MONSTER(rz-10,-5.5,rx-10,COLOR_GREEN);
    }



    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            string Result;
            stringstream convert;
            //cout << "nonedit score:" << score << endl;
            convert << healthpoints;
            Result = convert.str();
            const char *one = "Health: ";
            const char *two = Result.c_str();
            const char *three = "   Score: ";
            string Result1;
            stringstream convert1;
            convert1 << score;
            Result1 = convert1.str();
            const char *four = Result1.c_str();
            const char *five = " MonsterCount: ";
            string Result3;
            stringstream convert2;
            convert2 << monstercount;
            Result3 = convert2.str();
            const char *six = Result3.c_str();
            string total( string(one) + two + string(three) + four + string(five) + six );
            glfwSetWindowTitle(window,total.c_str());
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        if(healthpoints==0)
            break;

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool rock_collision(bounding_box_t a, bounding_box_t b)
{
    if((fabs(a.x-b.x) < (a.height+b.height) && fabs(a.width-b.width) < (a.height+b.height))
       || ( fabs(a.x-b.x) < (a.height*2+b.height) && fabs(a.width-b.width) < (a.height*2+b.height))
       || ( fabs(a.x-b.x) < (a.height+(b.height)*sqrt(2)) && fabs(a.width-b.width) < (a.height+(b.height)*sqrt(2)))
       || (fabs(a.x-b.x) < (a.height*2+(b.height)*sqrt(2)) &&fabs(a.width-b.width) < (a.height*2+(b.height)*sqrt(2))))
    {
        return true;
    }
    return false;

}

void reset_screen() {
    float top    = screen_center_y + 10 / screen_zoom;
    float bottom = screen_center_y - 10 / screen_zoom;
    float left   = screen_center_x - 10 / screen_zoom;
    float right  = screen_center_x + 10 / screen_zoom;
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(90.0f), 2.0f, 0.1f,1000.0f);
}

void firing_balls()
{
    int r=0;
    for(int i=0;i<50;i++)
    {
        if(ballthrown[i]==0)
        {
            ballthrown[i]=1;
            ball[i].back = 0;
            ball[i].position.x = boat1.position.x;
            ball[i].position.y = boat1.position.y+0.7;
            ball[i].position.z = boat1.position.z/*-2*(cos(boat1.rotation*(M_PI/180.0f)))*/;
            ball[i].dirroc = boat1.rotation;
            return;
            r=i;
        }

    }

}

void firing_Backballs()
{
    int r=0;
    for(int i=0;i<50;i++)
    {
        if(ballthrown[i]==0)
        {
            ballthrown[i]=1;
            ball[i].back = 1;
            ball[i].position.x = boat1.position.x;
            ball[i].position.y = boat1.position.y+0.7;
            ball[i].position.z = boat1.position.z/*-2*(cos(boat1.rotation*(M_PI/180.0f)))*/;
            ball[i].dirroc = boat1.rotation;
            return ;
            r=i;
        }

    }


}

bool boat_barrel_collision(int rt)
{
    if(fabs(boat1.position.x-barrel[rt].position.x) <= 1 && fabs(boat1.position.z-barrel[rt].position.z) <= 1)
        return true;
    else
        return false;
}

bool boat_monster_collision(int rt)
{
        if(fabs(boat1.position.x-monster[rt].position.x) <= 1.300 && fabs(boat1.position.z-monster[rt].position.z)<= 1.300)
            return true;
        else
            return false;
}

bool fireball_monster_collision(int rt,int mt)
{
    if(ballthrown[rt])
    {
        if(fabs(monster[mt].position.x-ball[rt].position.x)<=0.300 && fabs(monster[mt].position.z-ball[rt].position.z)<=0.300)
        {
            return true;
        }
        else
            return false;
    }

}
bool boat_booster_collision(int rt)
{
    if(giftrelease[rt])
    {
        if(fabs(boat1.position.x-mongifts[rt].position.x) <= 1 && fabs(boat1.position.z-mongifts[rt].position.z) <= 1)
            return true;
        else
            return false;
    }
}


bool boat_Bmonster_collision()
{
        if(fabs(boat1.position.x-bigboss.position.x) <= 1.300 && fabs(boat1.position.z-bigboss.position.z)<= 1.300)
            return true;
        else
            return false;
}

bool fireball_Bmonster_collision(int rt)
{
    if(ballthrown[rt])
    {
        if(fabs(bigboss.position.x-ball[rt].position.x)<=0.300 && fabs(bigboss.position.z-ball[rt].position.z)<=0.300)
        {
            return true;
        }
        else
            return false;
    }

}

void screen_zoom_in(){
    screen_zoom -= 1;
    reset_screen();
}
void screen_zoom_out(){
    screen_zoom += 1;
    reset_screen();
}
