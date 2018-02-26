//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

////////////////////////////////
// CODIGO INICIAL PARA WINDOWS
////////////////////////////////
//#include <GL/freeglut.h>
//#include <glm.hpp>


////////////////////////////////
// CODIGO PARA MAC
////////////////////////////////
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "glm.hpp"

//-------------------------------------------------------------------------

class Mesh 
{
public:
    static Mesh * generateAxesRGB(GLdouble l);
    static Mesh * generateTriangle(GLdouble r);
    static Mesh * generateTriangleRGB(GLdouble r);
    static Mesh * generateTriPyramid(GLdouble r,GLdouble h);
    static Mesh * generateContCubo(GLdouble l);
    static Mesh * generateDiabolo(GLdouble r,GLdouble h);
    static Mesh * generateRectangle(GLdouble w,GLdouble h);
    
    Mesh(void) { };
    ~Mesh(void);
    virtual void draw();
    glm::dvec3 * getVertices() { return vertices; };
    glm::dvec4 * getColours() { return colors; };
    
protected:
    GLuint numVertices = 0;
    GLuint type = GL_POINTS;
    glm::dvec3 * vertices = nullptr;
    glm::dvec4 * colors = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_