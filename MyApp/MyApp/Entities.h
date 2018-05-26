//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <vector>


#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
    Entity() : modelMat(1.0) { };
    virtual ~Entity() { delete mesh; };
    virtual void render(glm::dmat4 const& modelViewMat);
    glm::dmat4 modelMat;
    //colores
    GLfloat re;
    GLfloat gr;
    GLfloat bl;

protected:
    Mesh* mesh = nullptr;
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
//    virtual void normalize();
//    virtual void render(glm::dmat4 const& modelViewMat);
protected:
    int m;
    int n;
//    glm::dvec3 * perfil;
};

class Hipotrocoide : public Entity
{
public:
    Hipotrocoide(int nP,int nQ, int aHipo, int bHipo, int cHipo);
    ~Hipotrocoide() { };
    virtual void draw();
//    virtual void getMatrix(){return modelMat};

protected:
    int nP;
    int nQ;
    GLfloat a, b, c;

};

class QuadricEntity : public Entity
{
public:
//    QuadricEntity(GLdouble l);
    ~QuadricEntity() { gluDeleteQuadric(q); };


   
protected:
    GLUquadricObj *q;
    GLdouble r;

};


class Sphere : public QuadricEntity
{
public:
    Sphere(GLdouble l);
    virtual void draw();
    
protected:
    
};



class CompoundEntity : public Entity
{
public:
    std::vector<Entity*> entities;
    virtual void render(glm::dmat4 const& modelViewMat);
    
protected:
    
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_
