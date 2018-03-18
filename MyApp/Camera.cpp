#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;


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
    viewMat = lookAt(eye, look, up);
    setVM();
    //setPM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
    eye= dvec3(500, 500, 500);
    look= dvec3(0, 10, 0);
    up= dvec3(0, 1, 0);
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
    
    viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
    a = a*10;
    
    viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
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
    projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(value_ptr(projMat));
    glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs) // Left / Right
{//tengo dudas con right, down, front
	
	eye = eye + (right * cs);
	//viewMat = lookAt(eye, eye + right, up);
}
void Camera::moveFB(GLdouble cs) // Forward / Backward
{
	eye = eye + (front * cs);
	viewMat = lookAt(eye, eye + front, up);
}
void Camera::moveUD(GLdouble cs) // Up / Down
{
	eye = eye + (down * cs);
	viewMat = lookAt(eye, eye + down, up);
}

//void rotatePY(GLdouble incrPitch, GLdouble incrYaw) {
//
//
//	pitch += incrPitch; 
//	yaw += incrYaw; // Actualizar los ángulos
//	if (pitch > 89.5) pitch = 89.5; // Limitar los ángulos
//	…
//		// Actualizar la dirección de vista
//		front.x = sin(radians(yaw)) * cos(radians(pitch));
//	front.y = sin(radians(pitch));
//	front.z = -cos(radians(yaw)) * cos(radians(pitch));
//	front = glm::normalize(front);
//	viewMat = lookAt(eye, eye + front, up);
//	…
//}



