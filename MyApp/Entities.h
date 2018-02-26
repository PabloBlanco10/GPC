//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

////////////////////////////////
// CODIGO INICIAL PARA WINDOWS
////////////////////////////////
//#include <GL/freeglut.h>
//#include <glm.hpp>


////////////////////////////////
// CODIGO PARA MAC
////////////////////////////////
#include "glm.hpp"
#include <GL/freeglut.h>

#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
    Entity() : modelMat(1.0) { };
    virtual ~Entity() { delete mesh; };
    
    virtual void render(glm::dmat4 const& modelViewMat);
    
protected:
    Mesh* mesh = nullptr;
    glm::dmat4 modelMat;
    virtual void draw();
    virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
    EjesRGB(GLdouble l);
    ~EjesRGB() { };
    virtual void draw();
};

class Triangle : public Entity
{
public:
    Triangle(GLdouble l);
    ~Triangle() { };
    virtual void draw();
};

class TriangleRGB : public Entity
{
public:
    TriangleRGB(GLdouble l);
    ~TriangleRGB() { };
    virtual void draw();
};


class TriPyramid : public Entity
{
public:
    TriPyramid(GLdouble r,GLdouble h);
    ~TriPyramid() { };
    virtual void draw();
};


class ContCubo : public Entity
{
public:
    ContCubo(GLdouble l);
    ~ContCubo() { };
    virtual void draw();
};


class Diabolo : public Entity
{
public:
    Diabolo(GLdouble r, GLdouble h);
    ~Diabolo() { };
    virtual void draw();
    virtual void render(glm::dmat4 const& modelViewMat);
    virtual void rotateDiabolo();
};

class Rectangle : public Entity
{
public:
    Rectangle(GLdouble w, GLdouble h);
    ~Rectangle() { };
    virtual void draw();
};


class Cubo : public Entity
{
public:
    Cubo(GLdouble h);
    ~Cubo() { };
    virtual void drawMesh();
    virtual void drawRectangleMesh();
    virtual void render(glm::dmat4 const& modelViewMat);
    
protected:
    Mesh* rectangleMesh = nullptr;
    GLdouble height;
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_
