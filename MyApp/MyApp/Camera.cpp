#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

extern glm::dvec2 mCoord;


//-------------------------------------------------------------------------

void Viewport::setPos(GLsizei l, GLsizei b)
{
    x = l;
    y = b;
    set();
}

//-------------------------------------------------------------------------

void Viewport::setSize(GLsizei aw, GLsizei ah) 
{ 
    w = aw;
    h = ah;
    set();
}
//-------------------------------------------------------------------------

void Viewport::set() 
{ 
    glViewport(x, y, w, h);
}
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
    eye= dvec3(0, 0, 500);
    look= dvec3(0, 0, 0);
    up= dvec3(0, 1, 0);
    yawAttribute = 0;
    pitchAttribute = 0;
    updateFrontRight();
    viewMat = lookAt(eye, look, up);
    setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
    eye= dvec3(500, 500, 500);
    look= dvec3(0, 10, 0);
    up= dvec3(0, 1, 0);
    updateFrontRight();
    updatePitchYaw();
    viewMat = lookAt(eye, look, up);
    setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
    a = a*10;
    
    rotatePY(a,0);
//    viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));

}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
    
    a = a*10;
    rotatePY(0,a);
    
//    viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
    a = a*10;
    viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
    factScale -= s;
    if (s < 0) s = 0.01;
    setPM();
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
    xRight = aw / 2.0;
    xLeft = -xRight;
    yTop = ah / 2.0;
    yBot = -yTop;
    
    setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{

    if(orto){
        projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
    }
    else{
        projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(value_ptr(projMat));
    glMatrixMode(GL_MODELVIEW);

}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs) // Left / Right
{
    eye = eye + (right * cs);
    viewMat = lookAt(eye, eye + front, up);
}

void Camera::moveFB(GLdouble cs) // Forward / Backward
{
    eye = eye + (front * cs);
    viewMat = lookAt(eye, eye + front, up);
}

void Camera::moveUD(GLdouble cs) // Up / Down
{
    eye = eye + (down * cs);
    viewMat = lookAt(eye, eye + front, up);
}

void Camera::rotatePY(GLdouble offsetP, GLdouble offsetY) {
    pitchAttribute+= offsetP;
    yawAttribute+= offsetY; // Actualizar los ‡ngulos
    
    if (pitchAttribute > 89.5)
        pitchAttribute = 89.5; // Limitar los ‡ngulos ...
    
    // Actualizar la direcci—n de vista
    front.x = sin(radians(yawAttribute)) * cos(radians(pitchAttribute));
    front.y = sin(radians(pitchAttribute));
    front.z = -cos(radians(yawAttribute)) * cos(radians(pitchAttribute));
    front = glm::normalize(front);
    
    viewMat = lookAt(eye, eye + front, up);
    right = (normalize(cross(up,-front))); // ortogonal a up y n
}


//void Camera::setPrj(){
//    if(orto == true){
//        glMatrixMode(GL_PROJECTION);
//        projMat = ortho(xLeft, xRight, yBot, yTop, yTop, farVal);
//        glLoadMatrixd(value_ptr(projMat));
//        glMatrixMode(GL_MODELVIEW);
//    }
//    else{
//        glMatrixMode(GL_PROJECTION);
//        projMat = frustum(xLeft, xRight, yBot, yTop, yTop, farVal);
//        glLoadMatrixd(value_ptr(projMat));
//        glMatrixMode(GL_MODELVIEW);
//    }
//
//}

void Camera::changeOrto(){
    orto = !orto;
    
//    setPrj();
    setPM();
}

void Camera::updateFrontRight(){
    front = -(normalize(eye-look)); // -n es la direcci—n de vista
    right = (normalize(cross(up,-front))); // ortogonal a up y n
}

void Camera::updateDown(){
    down = cross(-front, right); // ortogonal a n y u
}

void Camera::updatePitchYaw(){
    pitchAttribute = degrees(asin(front.y));
    yawAttribute = degrees(asin(front.x / cos(radians(pitchAttribute))));
}

