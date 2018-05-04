//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

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
    Texture texture;
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
protected:
    GLdouble height;
};

class Rectangulo : public Entity
{
public:
    Rectangulo(GLdouble w, GLdouble h, GLdouble replicaW, GLdouble replicaH);
    ~Rectangulo() { };
    virtual void draw();
};


class Cubo : public Entity
{
public:
    Cubo(GLdouble h);
    ~Cubo() { };
    virtual void drawMesh();
    virtual void drawRectanguloMesh();
    virtual void drawMeshIn();
    virtual void render(glm::dmat4 const& modelViewMat);
    
protected:
    Mesh* rectanguloMesh = nullptr;
    GLdouble height;
    Texture textureIn;
};


class Suelo : public Entity
{
public:
    Suelo(GLdouble w, GLdouble h);
    ~Suelo() { };
    virtual void draw();
};


class GlassPot : public Entity
{
public:
    GlassPot(GLdouble l);
    ~GlassPot() { };
    virtual void draw();
};


class Grass : public Entity
{
public:
    Grass(GLdouble l);
    virtual void render(glm::dmat4 const& modelViewMat);
    ~Grass() { };
    virtual void draw();
};




class MPR : public Entity
{
public:
    MPR(int n);
    ~MPR() { };
    virtual void draw();
//    virtual void render(glm::dmat4 const& modelViewMat);
protected:
    int m;
    int n;

};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_
