////////////////////////////////
// CODIGO INICIAL PARA WINDOWS
////////////////////////////////
//#include "Entities.h"
//
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

////////////////////////////////
// CODIGO PARA MAC
////////////////////////////////
#include "Entities.h"

#include "matrix_transform.hpp"
#include "type_ptr.hpp"

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
    setMvM(modelViewMat);
    draw();
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
    if (mesh != nullptr)
        mesh -> draw();
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
    mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble r): Entity()
{
    mesh = Mesh::generateTriangle(r);
}
//-------------------------------------------------------------------------

void Triangle::draw()
{
    glLineWidth(2);
    //sirve para pintar solo las lineas y dibujarlo vacio
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    mesh->draw();
    glLineWidth(1);
}

//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble r): Entity()
{
    mesh = Mesh::generateTriangleRGB(r);
    
    //    mover
    //    modelMat = translate(modelMat, dvec3(200,200,0));
    
    //    rotar
    //    modelMat = rotate(modelMat, radians(45.0), dvec3(0.0,0.0,1.0));
    
    //    escalar
    //    modelMat = scale(modelMat, dvec3(1.5,1.5,1.0));
    
}
//-------------------------------------------------------------------------

void TriangleRGB::draw()
{
    glLineWidth(2);
    //sirve para pintar lo de dentro
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    mesh->draw();
    glLineWidth(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
}


//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLdouble r,GLdouble h): Entity()
{
    mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void TriPyramid::draw()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}

//-------------------------------------------------------------------------

ContCubo::ContCubo(GLdouble l): Entity()
{
    mesh = Mesh::generateContCubo(l);
}
//-------------------------------------------------------------------------

void ContCubo::draw()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}

//-------------------------------------------------------------------------

Diabolo::Diabolo(GLdouble r,GLdouble h): Entity()
{
    mesh = Mesh::generateTriPyramid(r, 400);
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}

void Diabolo::render(const glm::dmat4 &modelViewMat){
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    aMat = translate(aMat ,dvec3(0,0,-400));
    
    glLoadMatrixd(value_ptr(aMat));
    glColor3d(0.0, 0.0, 0.0);
    draw();
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
    glLoadMatrixd(value_ptr(aMat));
    glColor3d(1.0, 0.0, 0.0);
    draw();
    
    aMat = modelViewMat * modelMat;
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
    aMat = translate(aMat ,dvec3(0,0,-400));
    glLoadMatrixd(value_ptr(aMat));
    glColor3d(0.0, 0.0, 1.0);
    draw();
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
    glLoadMatrixd(value_ptr(aMat));
    glColor3d(0.0, 1.0, 0.0);
    draw();
}

void Diabolo::rotateDiabolo(){
    glMatrixMode(GL_MODELVIEW);
    modelMat = rotate(modelMat, radians(2.0), dvec3(0.0,0.0,1.0));
    glLoadMatrixd(value_ptr(modelMat));
}

//-------------------------------------------------------------------------

Rectangle::Rectangle(GLdouble w,GLdouble h): Entity()
{
    mesh = Mesh::generateRectangle(w, h);
}
//-------------------------------------------------------------------------

void Rectangle::draw()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}

//-------------------------------------------------------------------------


Cubo::Cubo(GLdouble h): Entity()
{
    mesh = Mesh::generateContCubo(h);
    height = h;
    rectangleMesh = Mesh::generateRectangle(h, h);
}

void Cubo::drawMesh()
{
    glLineWidth(2);
    mesh->draw();
    glLineWidth(1);
}

void Cubo::drawRectangleMesh()
{
    glLineWidth(2);
//    glRotatef(45, 1, 0, 0);
//    glTranslatef(1, 1.75*height,1);

//    glTranslatef(1, 1, -(height/2) * cos(45));
    
//    glTranslatef(0, 0, -(height/2));
    rectangleMesh->draw();
    glLineWidth(1);
}

void Cubo::render(const glm::dmat4 &modelViewMat){
    
    glMatrixMode(GL_MODELVIEW);
//    dmat4 aMat = modelViewMat * modelMat;
    glPolygonMode(GL_FRONT, GL_LINE);
//    glPolygonMode(GL_BACK, GL_POINT);

    drawMesh();
    
    
    dmat4 aMat = modelViewMat * modelMat;
    aMat = translate(aMat ,dvec3(0,height*0.85,0));
    aMat = translate(aMat ,dvec3(0,0,-(height*0.15)));
    aMat = rotate(aMat, radians(45.0), dvec3(1.0,0.0,0.0));

    
    glLoadMatrixd(value_ptr(aMat));
    drawRectangleMesh();
//    glLoadMatrixd(value_ptr(modelMat));

}