//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);

// Scene entities
Scene scene(&camera);


glm::dvec2 mCoord;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);

void mouse(int button, int state, int x, int y);
void motion(int x, int y);


//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    cout << "Starting console..." << '\n';
    
    // Initialization
    
    glutInit(&argc, argv);
    
    
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitWindowSize(800, 600);   // window size
    glutInitWindowPosition (140, 140);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL
    
    int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
    
    // Callback registration
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutDisplayFunc(display);
    
    camera.updateFront();
    camera.updateRight();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    
    cout << glGetString(GL_VERSION) << '\n';
    cout << glGetString(GL_VENDOR) << '\n';
    
    scene.init();    // after creating the context
    
    glutMainLoop();
    
    //cin.sync();   cin.get();
    glutDestroyWindow(win);  // Destroy the context
    
    return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene.render();
    
    glutSwapBuffers();
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
    // Resize Viewport
    viewPort.setSize(newWidth, newHeight);
    // Resize Scene Visible Area
    camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
    bool need_redisplay = true;
    Texture texture;
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    
    switch (key) {
        case 27:  // Escape key
            //    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop
            break;
        case '+':
            camera.scale(+0.10);   // zoom in
            break;
        case '-':
            camera.scale(-0.10);   // zoom out
            break;
        case 'l':
            camera.set3D();
            camera.updateRight();
            camera.updateFront();
            camera.updatePitchYaw();
            break;
        case 'o':
            camera.setAZ();
            camera.updateRight();
            camera.updateFront();
            camera.updatePitchYaw();
            break;
        case 'a':
            scene.rotarDiabolo();
            break;
        case 'F':
            texture.loadColorBuffer(w, h);
            texture.save("prueba");
            break;
        case 'A':
            camera.moveLR(-100.0);
//            camera.updateRight();
            break;
        case 'D':
            camera.moveLR(100.0);
//            camera.updateRight();
            break;
        case 'W':
            camera.moveFB(100.0);
//            camera.updateFront();
//            camera.updatePitchYaw();
            break;
        case 'S':
            camera.moveFB(-100.0);
//            camera.updateFront();
//            camera.updatePitchYaw();
            break;
        case 'p':
            camera.changeOrto();
            camera.setPrj();
            camera.updateFront();
            camera.updateRight();
            camera.updatePitchYaw();
            break;
        default:
            need_redisplay = false;
            break;
    }//switch

    if (need_redisplay)
        glutPostRedisplay();

}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
    bool need_redisplay = true;
    
    switch (key) {
        case GLUT_KEY_RIGHT:
//            camera.pitch(1);   // rotate 1 on the X axis
            camera.yaw(-1);     // rotate 1 on the Y axis
            break;
        case GLUT_KEY_LEFT:
            camera.yaw(1);     // rotate 1 on the Y axis
            break;
        case GLUT_KEY_UP:
//            camera.roll(1);    // rotate 1 on the Z axis
            camera.pitch(-1);   // rotate 1 on the X axis

            break;
        case GLUT_KEY_DOWN:
//            camera.roll(-1);   // rotate -1 on the Z axis
            camera.pitch(1);   // rotate 1 on the X axis

            break;
        default:
            need_redisplay = false;
            break;
    }//switch

    if (need_redisplay)
        glutPostRedisplay();
}
//-------------------------------------------------------------------------


void mouse(int button, int state, int x, int y){
    mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}


void motion(int x, int y){
    glm::dvec2 mOffset = mCoord; // var. global
    mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
    camera.rotatePY(mOffset.y, mOffset.x);
    glutPostRedisplay();
}


