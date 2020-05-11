#include "main.h"
#include "timer.h"
#include "ball.h"
#include "brick.h"
#include "coin.h"
#include "borderline.h"
#include "pillar.h"
#include "firebeam.h"
#include "waterball.h"
#include "laser.h"
#include "lasercap.h"
#include "laserback.h"
#include "convexellipse.h"
#include "concaveellipse.h"
#include "triangle.h"
#include "quadrant.h"
#include "rectangle.h"
#include "magnet.h"
#include "boomerang.h"
#include "star.h"
#include "wheel.h"


using namespace std;

#define pb push_back
#define rc(a,b,c,d,v) Rectangle(a+v,b,0,0,c,d,COLOR_BLACK)

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Brick brick[600];
Coin coin[100];
Star star[100];
Pillar pillar[100];
Borderline up_borderline;
Borderline down_borderline;
Firebeam firebeam;
Waterball waterball;
Laser laser;
Lasercap lasercap;
Laserback laserback;
Coin fireline[12][16];
Coin outerline[12][16];
Coin sun;
Concaveellipse cl1,cl2;
Convexellipse ol1,ol2;
Triangle upcap,downcap,fup,fdown,eye1,eye2,leg1,leg2;
Quadrant quad;
Rectangle rect;
Magnet magnet[15];
Boomerang boomerang;
vector<Rectangle> adj[51];
vector<Quadrant> lob;
Triangle lobt;
vector<Triangle> diamond[10];
vector<Quadrant> ring;
int ringmarker;
double xdiff[20],ydiff[20];
double theta;
Wheel wheel[20];
Coin cover[20];

int points,lives;
int insidering;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( 0, 0, 1 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
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
    //ball1.draw(VP);
    sun.draw(VP);
    for(int i=0;i<=20;++i)
        wheel[i].draw(VP);
    /*for(int i=0;i<=20;++i)
        cover[i].draw(VP);*/
    for(int i=0;i<=20;++i)
        coin[i].draw(VP);
    for(int i=0;i<=20;++i)
        star[i].draw(VP);
    /*for(int i=0;i<=9;++i)
    {
        for(auto v:diamond[i])
            v.draw(VP);
    }*/
    for(int i=0;i<=599;++i)
        brick[i].draw(VP);
    for(int i=0;i<=99;++i)
        pillar[i].draw(VP);
    up_borderline.draw(VP);
    down_borderline.draw(VP);
    firebeam.draw(VP);
    waterball.draw(VP);
    laser.draw(VP);
    lasercap.draw(VP);
    laserback.draw(VP);
    for(int j=1;j<10;++j)
    {
        for(int i=0;i<=14;++i)
            outerline[j][i].draw(VP);
    }
    for(int j=1;j<10;++j)
    {
        for(int i=0;i<=14;++i)
            fireline[j][i].draw(VP);
    }
    ol1.draw(VP);
    ol2.draw(VP);
    cl1.draw(VP);
    cl2.draw(VP);
    for(int i=0;i<=10;++i)
        magnet[i].draw(VP);
    boomerang.draw(VP);
    if(ringmarker)
    {
        for(auto v:ring)
            v.draw(VP);
    }
    ball1.draw(VP);
    upcap.draw(VP);
    downcap.draw(VP);
    rect.draw(VP);
    fup.draw(VP);
    fdown.draw(VP);
    eye1.draw(VP);
    eye2.draw(VP);
    leg1.draw(VP);
    leg2.draw(VP);
    quad.draw(VP);
    for(int i=10;i<=15;++i)
    {
        for(auto v:adj[i])
            v.draw(VP);
    }
    for(auto v:adj[20+(int)(points/10)])
        v.draw(VP);
    for(auto v:adj[(int)(points%10)])
        v.draw(VP);
    for(auto v:lob)
        v.draw(VP);
    lobt.draw(VP);
    for(auto v:adj[30+(int)(lives%10)])
        v.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int w = glfwGetKey(window, GLFW_KEY_W);
    if(up) 
    {
        ball1.speedy = 1;
        upcap.speedy = 1;
        downcap.speedy = 1;
        quad.speedy = 1;
        rect.speedy = 1;
        fup.speedy = 1;
        fdown.speedy = 1;
        eye1.speedy = 1;
        eye2.speedy = 1;
        leg1.speedy = 1;
        leg2.speedy = 1;
    }
    if(down && ball1.position.y > -1)
    {
        ball1.position.y -= 0.2;
        upcap.position.y -= 0.2;
        downcap.position.y -= 0.2;
        quad.position.y -= 0.2;
        eye1.position.y -= 0.2;
        eye2.position.y -= 0.2;
        rect.position.y -= 0.2;
        fup.position.y -= 0.2;
        fdown.position.y -= 0.2;
        leg1.position.y -= 0.2;
        leg2.position.y -= 0.2;
    }
    if(left && ball1.position.x >= -2.7)
    { 
        ball1.position.x -= 0.1;
        upcap.position.x -= 0.1;
        downcap.position.x -= 0.1;
        quad.position.x -= 0.1;
        rect.position.x -= 0.1;
        fup.position.x -= 0.1;
        fdown.position.x -= 0.1;
        eye1.position.x -= 0.1;
        eye2.position.x -= 0.1;
        leg1.position.x -= 0.1;
        leg2.position.x -= 0.1;
    }
    if(right && ball1.position.x <= 2.7)
    {
        ball1.position.x += 0.1;
        upcap.position.x += 0.1;
        downcap.position.x += 0.1;
        quad.position.x += 0.1;
        rect.position.x += 0.1;
        fup.position.x += 0.1;
        fdown.position.x += 0.1;
        eye1.position.x += 0.1;
        eye2.position.x += 0.1;
        leg1.position.x += 0.1;
        leg2.position.x += 0.1;
    }
    if(s && waterball.position.y < -10)
    {
        waterball.position.x = ball1.position.x;
        waterball.position.y = ball1.position.y;
        waterball.speedx = waterball.speedy = 1;
    }
    if(w && points >= 4)
    {
        lives += 1;
        points -= 4;
    }
}

void tick_elements() {
    for(int i=0;i<=20;++i)
        coin[i].tick(1);
    for(int i=0;i<=20;++i)
        star[i].tick(1);
    for(int i=0;i<=599;++i)
        brick[i].tick();
    for(int i=0;i<=99;++i)
        pillar[i].tick();
    sun.tick(0);
    for(int i=0;i<=20;++i)
        wheel[i].tick();
    /*for(int i=0;i<=20;++i)
        cover[i].tick(1);*/
    up_borderline.tick();
    down_borderline.tick();
    firebeam.tick();
    waterball.tick();
    laser.tick();
    lasercap.tick();
    laserback.tick();
    for(int j=1;j<10;++j)
    {
        for(int i=0;i<=14;++i)
            outerline[j][i].tick(0);
        for(int i=0;i<=14;++i)
            fireline[j][i].tick(0);
    }
    ol1.tick(1);
    ol2.tick(1);
    cl1.tick(1);
    cl2.tick(1);
    if(insidering == 0)
    {
        ball1.tick();
        upcap.tick(1);
        downcap.tick(1);
        quad.tick(1);
        rect.tick(1);
        fup.tick(2);
        fdown.tick(1);
        eye1.tick(3);
        eye2.tick(3);
        leg1.tick(4);
        leg2.tick(4);
    }
    for(int i=0;i<=10;++i)
        magnet[i].tick();
    boomerang.tick();
    /*for(int i=0;i<=9;++i)
    {
        for(auto v:diamond[i])
            v.tick(0);
    }*/
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(-2, -2, COLOR_LITEYELLOW);
    upcap       = Triangle(-2.25,-1.75,1,0,0.5f,0.0f,1.0f,0.5f,COLOR_BLACK);
    downcap     = Triangle(-1.75,-1.75,1,0.0f,0.5f,0.5f,0.0f,-0.25f,COLOR_BLACK);
    quad        = Quadrant(-2.4,-2.25,1,0.0f,0.0f,-0.5f,COLOR_BLACK);
    rect        = Rectangle(-2.6,-1.75,1,0,0.2f,-0.75f,COLOR_BROWN);
    fdown       = Triangle(-2.5,-1.75,1,0,0.1,0.1,-0.1,0.1,COLOR_ORANGE);
    fup         = Triangle(-2.5,-1.55,1,0,0.1,-0.1,-0.1,-0.1,COLOR_ORANGE);
    eye1        = Triangle(-2.125,-2,1,0,0.075,0.125,-0.075,0.125,COLOR_BLACK);
    eye2        = Triangle(-2.125+0.25,-2,1,0,0.075,0.125,-0.075,0.125,COLOR_BLACK);
    leg1        = Triangle(-2.4,-2.25,1,0,0,-0.6,0.1,-0.6,COLOR_BROWN);
    leg2        = Triangle(-2.4+0.2,-2.25,1,0,0,-0.6,0.1,-0.6,COLOR_BROWN);

    for(int i=0;i<=99;++i)
    {
        brick[i]     = Brick(-3.5+i*2,-3.14,COLOR_BLACK);
        brick[i+100]     = Brick(-2.5+i*2,-3.42,COLOR_BLACK);
        brick[i+200] = Brick(-3.5+i*2,-3.70,COLOR_BLACK);
        brick[i+300]     = Brick(-3.5+i*2,3.14,COLOR_BLACK);
        brick[i+400]     = Brick(-2.5+i*2,3.42,COLOR_BLACK);
        brick[i+500] = Brick(-3.5+i*2,3.70,COLOR_BLACK);
        pillar[i]    = Pillar(-3.5+i*2,0,COLOR_OLIVEGREEN);
    }

    sun = Coin(0.0,2.0,0.5f,COLOR_ORANGE);
    
    for(int i=0;i<=20;++i)
    {
        int ry = rand()%5;
        coin[i]      = Coin(4.0+i*4,ry-2.0,0.1f,COLOR_YELLOW);
        star[i]      = Star(3.0+i*6,rand()%5-2.0,0.2f,COLOR_BLUE);
        wheel[i]     = Wheel(4.0+i*8,2.5,COLOR_DARKRED);
        //cover[i]     = Coin(4.0+i*8,2.5,0.2f,COLOR_DARKRED);
    }

    firebeam = Firebeam(-3.5+9.0,0,COLOR_YELLOW);
    ol1 = Convexellipse(5.5,0,0.5,COLOR_ORANGE);
    cl1 = Concaveellipse(4.5,0,0.5,COLOR_ORANGE);
    ol2 = Convexellipse(6.5,0,0.5,COLOR_ORANGE);
    cl2 = Concaveellipse(5.5,0,0.5,COLOR_ORANGE);

    up_borderline    = Borderline(90,3,COLOR_BLACK);
    down_borderline    = Borderline(90,-3,COLOR_BLACK);
    waterball          = Waterball(-100,-100,COLOR_BLUE);
    laser              = Laser(0,-100,COLOR_ORANGE);
    lasercap           = Lasercap(-3.6,-100,COLOR_GREY);
    laserback          = Laserback(3.6,-100,COLOR_GREY);

    for(int j=1;j<10;++j)
    {
        float ang = 2*3.14159;
        int n = rand()%5 + 1;
        ang /= n;
        
        float r = 0.12f;
        float x = j*10.0f, y = (float)(j%3 - 1);
        for(int i=0;i<=14;++i)
        {
            if(i%14 == 0)
                outerline[j][i] = Coin(x,y,2*r,COLOR_YELLOW);
            else
                outerline[j][i] = Coin(x,y,r,COLOR_YELLOW);
            x = x + 0.1*cos(ang);
            y = y + 0.1*sin(ang);
        }
        x = j*10.0f; y = (float)(j%3 - 1); r = 0.08f;
        for(int i=0;i<=14;++i)
        {
            if(i%14 == 0)
                fireline[j][i] = Coin(x,y,2*r,COLOR_BLACK);
            else
                fireline[j][i] = Coin(x,y,r,COLOR_BLACK);
            x = x + 0.1*cos(ang);
            y = y + 0.1*sin(ang);
        }
    }

    for(int i=0;i<=10;++i)
        magnet[i] = Magnet((i+1)*20+5,2,0.3,COLOR_DARKRED);

    boomerang = Boomerang(2,2,COLOR_BLACK);

    // display seven segment
    float w = 0.3, b = 0.2, t = 0.05;
    adj[10].pb(rc(-3.5,2.8,w+0.05,-1*t,0)); // 1
    adj[10].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,0)); // 3
    adj[10].pb(rc(-3.5,2.8-2*b,w,-1*t,0)); // 4
    adj[10].pb(rc(-3.5,2.8,t,-1*b-0.05,0)); // 6
    adj[10].pb(rc(-3.5,2.8-b,w,-1*t,0)); // 7

    double v = 0.4;

    adj[11].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[11].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[11].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[11].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6

    v = 0.8;

    adj[12].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[12].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[12].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[12].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[12].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[12].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6    

    v = 1.2;

    adj[13].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[13].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[13].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6

    v = 1.6;

    adj[14].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[14].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[14].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[14].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[14].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[14].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    v = 2.0;

    adj[15].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    v = 2.8;

    adj[0].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[0].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[0].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[0].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[0].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[0].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6

    adj[1].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[1].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3

    adj[2].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[2].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[2].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[2].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[2].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[3].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[3].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[3].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[3].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[3].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[4].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[4].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[4].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[4].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[5].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[5].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[5].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[5].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[5].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[6].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[6].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[6].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[6].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[6].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[6].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[7].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[7].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[7].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3

    adj[8].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[8].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[8].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[8].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[8].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[8].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[8].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[9].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[9].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[9].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[9].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[9].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    v = 2.4;

    adj[20].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[20].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[20].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[20].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[20].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[20].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6

    adj[21].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[21].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3

    adj[22].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[22].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[22].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[22].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[22].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    lob.pb(Quadrant(1,2.6,0.0f,0.0f,0.1f,0.0f,COLOR_RED));
    lob.pb(Quadrant(1,2.6,0.0f,0.0f,0.0f,0.1f,COLOR_RED));
    lob.pb(Quadrant(1.2,2.6,0.0f,0.0f,0.1f,0.0f,COLOR_RED));
    lob.pb(Quadrant(1.2,2.6,0.0f,0.0f,0.0f,0.1f,COLOR_RED));
    lobt = Triangle(0.9,2.6,0.0f,0.0f,0.4f,0.0f,0.2f,-0.2f,COLOR_RED);

    v = 5;

    adj[30].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[30].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[30].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[30].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[30].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[30].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6

    adj[31].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[31].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3

    adj[32].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[32].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[32].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[32].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[32].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[33].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[33].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[33].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[33].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[33].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[34].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[34].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[34].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[34].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[35].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[35].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[35].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[35].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[35].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[36].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[36].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[36].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[36].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[36].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[36].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[37].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[37].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[37].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3

    adj[38].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[38].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[38].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[38].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[38].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[38].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[38].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    adj[39].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[39].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[39].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[39].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[39].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7

    /*adj[8].pb(rc(-3.5,2.8,w+0.05,-1*t,v)); // 1
    adj[8].pb(rc(-3.5+w,2.8,t,-1*b-0.05,v)); // 2
    adj[8].pb(rc(-3.5+w,2.8-b,t,-1*b-0.05,v)); // 3
    adj[8].pb(rc(-3.5,2.8-2*b,w+0.05,-1*t,v)); // 4
    adj[8].pb(rc(-3.5,2.8-b,t,-1*b-0.05,v)); // 5
    adj[8].pb(rc(-3.5,2.8,t,-1*b-0.05,v)); // 6
    adj[8].pb(rc(-3.5,2.8-b,w+0.05,-1*t,v)); // 7*/

    ring.pb(Quadrant(0,0,0,0,3,0,COLOR_GREY));
    ring.pb(Quadrant(0,0,0,0,1.5,0,COLOR_BACKGROUND));
    ring.pb(Quadrant(0,0,0,0,0,3,COLOR_GREY));
    ring.pb(Quadrant(0,0,0,0,0,1.5,COLOR_BACKGROUND));

    for(int i=0;i<=9;++i)
    {
        int tr = rand()%5 - 2;
        diamond[i].pb(Triangle(i*7,tr,1,0,0.25,0.4,0.5,0,COLOR_BROWN));
        diamond[i].pb(Triangle(i*7,tr,1,0,0.25,0.4,0.4,0,COLOR_ORANGE));
        diamond[i].pb(Triangle(i*7,tr,1,0,0.25,0.4,0.2,0,COLOR_YELLOW));
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
    lives = 3;
    double laser_spawn_time = time(NULL);
    int laser_mrk = 0, laser_dir = 0;
    double boom_spawn_time = time(NULL);
    int fbtc = 1, bmtc = 1, fltc[20], lstc = 1;
    double ring_spawn_time = time(NULL);
    double start_time = time(NULL);

    for(int i=1;i<=14;++i)
        fltc[i] = 1;

    window = initGLFW(width, height);
    initGL (window, width, height);

    /* Draw in loop */
    double music_spawn_time = time(NULL);
    system("aplay spiderman_theme.wav&");

    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands

            if(time(NULL)-music_spawn_time > 13)
            {
                system("aplay spiderman_theme.wav&");
                music_spawn_time = time(NULL);
            }

            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // boomerang creation
            if(time(NULL)-boom_spawn_time > 15)
            {
                bmtc = 1;
                boomerang.position.x = boomerang.position.y = 2;
                boomerang.speedx = -4.5;
                boom_spawn_time = time(NULL);
            }

            // laser creation
            int p = rand()%5;
            if(laser_mrk == 0 && time(NULL)-laser_spawn_time > 15 && p == 3)
            {
                //laser.position.y = ball1.position.y;
                lstc = 1;
                lasercap.position.y = ball1.position.y;
                laserback.position.y = ball1.position.y;
                laser_mrk = 1;
                laser_spawn_time = time(NULL);
                printf("NEW LASER\n");
            }
            if(laser_mrk == 1 && time(NULL)-laser_spawn_time > 10)
            {
                laser.position.y = -100;
                lasercap.position.y = -100;
                laserback.position.y = -100;
                laser_mrk = 0;
                laser_dir = 0;
            }
            else if(laser_mrk == 1 && time(NULL)-laser_spawn_time > 8)
            {
                laser.position.y = -100;
            }
            else if(laser_mrk == 1 && time(NULL)-laser_spawn_time > 5)
            {
                laser.position.y = -100;
                if(laser_dir == 0)
                {
                    laser_dir = 1;
                    if(lasercap.position.y < ball1.position.y)
                        lasercap.speed = 1;
                    else
                        lasercap.speed = -1;
                } 
                else
                {
                    lasercap.position.y += lasercap.speed/100;
                    laserback.position.y = laser.position.y = lasercap.position.y; 
                }
            }
            else if(laser_mrk == 1 && time(NULL)-laser_spawn_time > 3 )
            {
                laser.position.y = lasercap.position.y;
            }

            bounding_box_t plyr_c = {ball1.position.x,ball1.position.y,
                                2.0f,2.0f};

            // firebeam collision with walls

            bounding_box_t fire_c = {firebeam.position.x,firebeam.position.y,
                                1.0f,0.03f};
            bounding_box_t wball_c = {waterball.position.x,waterball.position.y,
                                0.1f,0.1f};

            if(detect_collision(wball_c,fire_c,1.0f))
                firebeam.position.x = ol1.position.x = 
                    ol2.position.x = cl1.position.x = cl2.position.x = -100;

            if(time(NULL)-start_time > 30)
            {
                ringmarker = 1;
                start_time = time(NULL);
            }
            else if(insidering == 0 && stime(NULL)-start_time > 4)
            {
                ringmarker = 0;
            }

            if(insidering)
            {
                if(theta > 3.14)
                {
                    insidering = 0;
                    ringmarker = 0;
                }
                else
                {
                    theta += 0.01;
                    double xf = ball1.position.x + 2.25*cos(theta);
                    double yf = ball1.position.y - 2.25*sin(theta);
                    ball1.position.x -= xf;
                    upcap.position.x -= xf;
                    downcap.position.x -= xf;
                    quad.position.x -= xf;
                    eye1.position.x -= xf;
                    eye2.position.x -= xf;
                    rect.position.x -= xf;
                    fup.position.x -= xf;
                    fdown.position.x -= xf;
                    leg1.position.x -= xf;
                    leg2.position.x -= xf;
                    ball1.position.y -= yf;
                    upcap.position.y -= yf;
                    downcap.position.y -= yf;
                    quad.position.y -= yf;
                    eye1.position.y -= yf;
                    eye2.position.y -= yf;
                    rect.position.y -= yf;
                    fup.position.y -= yf;
                    fdown.position.y -= yf;
                    leg1.position.y -= yf;
                    leg2.position.y -= yf;
                    tick_elements();
                    continue;
                }
            }

            for(int i=0;i<=20;++i)
            {   
                bounding_box_t coin_c = {coin[i].position.x,coin[i].position.y,
                                0.1f,0.1f};   
                if(detect_collision(plyr_c,coin_c,3.0f) == 1)
                {
                    coin[i].position.y -= 100;
                    points += 1;
                    printf("points earned = %d\n",points);
                }
            }

            for(int i=0;i<=20;++i)
            {   
                bounding_box_t str_c = {star[i].position.x,star[i].position.y,
                                0.2f,0.2f};   
                if(detect_collision(plyr_c,str_c,3.0f) == 1)
                {
                    star[i].position.y -= 100;
                    lives += 1;
                    printf("lives increased to %d\n",lives);
                }
            }

            for(int j=1;j<10;++j)
            {
                for(int i=0;i<=14;++i)
                {
                    bounding_box_t line_c = {fireline[j][i].position.x,fireline[j][i].position.y,
                                    0.1f,0.1f};   
                    if(detect_collision(plyr_c,line_c,3.0f) == 1 && fltc[i] == 1)
                    {
                        fltc[i] = 0;
                        lives--;
                        if(lives == 0)
                            quit(window);
                    }
                }
            }

            if(detect_collision(plyr_c,fire_c,4.5f) && fbtc == 1)
            {
                fbtc = 0;
                lives--;
                if(lives == 0)
                    quit(window);
            }

            bounding_box_t lser_c = {laser.position.x,laser.position.y,
                                7.0f,0.2f};

            if(detect_collision(plyr_c,lser_c,3.0f) && lstc == 1)
            {
                lstc = 0;
                lives--;
                if(lives == 0)
                    quit(window);
            }

            for(int i=0;i<=10;++i)
            {
                if(magnet[i].position.x >= -3 && magnet[i].position.x <= 3)
                {
                    if(ball1.position.x >= -2.6 && ball1.position.x <= 2.6)
                    {
                        if(magnet[i].position.x > ball1.position.x)
                        {
                            ball1.position.x += 0.03;
                            upcap.position.x += 0.03;
                            downcap.position.x += 0.03;
                            quad.position.x += 0.03;
                            eye1.position.x += 0.03;
                            eye2.position.x += 0.03;
                            rect.position.x += 0.03;
                            fup.position.x += 0.03;
                            fdown.position.x += 0.03;
                            leg1.position.x += 0.03;
                            leg2.position.x += 0.03;
                        }
                        else if(magnet[i].position.x < ball1.position.x)
                        {
                            ball1.position.x -= 0.03;
                            upcap.position.x -= 0.03;
                            downcap.position.x -= 0.03;
                            quad.position.x -= 0.03;
                            eye1.position.x -= 0.03;
                            eye2.position.x -= 0.03;
                            rect.position.x -= 0.03;
                            fup.position.x -= 0.03;
                            fdown.position.x -= 0.03;
                            leg1.position.x -= 0.03;
                            leg2.position.x -= 0.03;
                        }
                    }
                    if(ball1.position.y >= -2.0 && ball1.position.y <= 2.0)
                    {
                        if(magnet[i].position.y > ball1.position.y)
                        {
                            ball1.speedy = 0.1;
                            upcap.speedy = 0.1;
                            downcap.speedy = 0.1;
                            quad.speedy = 0.1;
                            eye1.speedy = 0.1;
                            eye2.speedy = 0.1;
                            rect.speedy = 0.1;
                            fup.speedy = 0.1;
                            fdown.speedy = 0.1;
                            leg1.speedy = 0.1;
                            leg2.speedy = 0.1;
                        }
                    }
                }
            }

            bounding_box_t bmrg_c = {boomerang.position.x,boomerang.position.y,
                                0.5f,0.5f};

            if(detect_collision(plyr_c,bmrg_c,3.0f) && bmtc == 1)
            {
                bmtc = 0;
                lives--;
                if(lives == 0)
                    quit(window);
            }

            bounding_box_t rng_c = {-2.25,0,
                                0.75f,0.75f};

            if(ringmarker == 1 && detect_collision(plyr_c,rng_c,3.0f))
            {
                insidering = 1;
                double xd = ball1.position.x - 2.25;
                double yd = ball1.position.y - 0;
                theta = 0;
                ball1.position.x -= xd;
                upcap.position.x -= xd;
                downcap.position.x -= xd;
                quad.position.x -= xd;
                eye1.position.x -= xd;
                eye2.position.x -= xd;
                rect.position.x -= xd;
                fup.position.x -= xd;
                fdown.position.x -= xd;
                leg1.position.x -= xd;
                leg2.position.x -= xd;
                ball1.position.y -= yd;
                upcap.position.y -= yd;
                downcap.position.y -= yd;
                quad.position.y -= yd;
                eye1.position.y -= yd;
                eye2.position.y -= yd;
                rect.position.y -= yd;
                fup.position.y -= yd;
                fdown.position.y -= yd;
                leg1.position.y -= yd;
                leg2.position.y -= yd;
            }

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b, float closeness) {
    return (abs(a.x - b.x) * closeness < (a.width + b.width)) &&
           (abs(a.y - b.y) * closeness < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
