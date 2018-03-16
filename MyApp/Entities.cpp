#include "Entities.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
        mesh->draw();
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
    mesh = Mesh::generateTriPyramidTex(r, h);
    //    mesh = Mesh::generateTriPyramid(r, h);
    texture.load("Bmps/floris.bmp");
//    texture.load("..\\Bmps\\floris.bmp");

}
//-------------generateTriPyramid---------------------------------------

void TriPyramid::draw()
{
    
    //    glLineWidth(2);
    texture.bind();
    mesh->draw();
    texture.unbind();
    //    glLineWidth(1);
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
    modelMat = translate(modelMat, dvec3(300,0,0));
    height = h;
    mesh = Mesh::generateTriPyramidTex(r, h);
    texture.load("Bmps/floris.bmp");
//    texture.load("..\\Bmps\\floris.bmp");
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{
    //    glLineWidth(2);
    
    texture.bind();
    mesh->draw();
    texture.unbind();
    //    glLineWidth(1);
}

void Diabolo::render(const glm::dmat4 &modelViewMat){
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    aMat = translate(aMat ,dvec3(0,0,-height));
    
    glLoadMatrixd(value_ptr(aMat));
    //    glColor3d(0.0, 0.0, 0.0);
    draw();
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
    glLoadMatrixd(value_ptr(aMat));
    //    glColor3d(1.0, 0.0, 0.0);
    draw();
    
    aMat = modelViewMat * modelMat;
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
    aMat = translate(aMat ,dvec3(0,0,-height));
    glLoadMatrixd(value_ptr(aMat));
    //    glColor3d(0.0, 0.0, 1.0);
    draw();
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
    glLoadMatrixd(value_ptr(aMat));
    //    glColor3d(0.0, 1.0, 0.0);
    draw();
}

void Diabolo::rotateDiabolo(){
    glMatrixMode(GL_MODELVIEW);
    modelMat = rotate(modelMat, radians(2.0), dvec3(0.0,0.0,1.0));
    glLoadMatrixd(value_ptr(modelMat));
}

//-------------------------------------------------------------------------

Rectangulo::Rectangulo(GLdouble w,GLdouble h, GLdouble replicaW, GLdouble replicaH): Entity()
{
//    mesh = Mesh::generateRectangle(w, h);

    mesh = Mesh::generateRectanguloTex(w, h, 0, 0);
    texture.load("Bmps/container.bmp");
//    texture.load("..\\Bmps\\container.bmp");

}
//-------------------------------------------------------------------------

void Rectangulo::draw()
{
//    glLineWidth(2);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    texture.bind();
    mesh->draw();
    texture.unbind();
//    glLineWidth(1);
}

//-------------------------------------------------------------------------


Cubo::Cubo(GLdouble h): Entity()
{
//    modelMat = translate(modelMat, dvec3(0,h/2,0));
    texture.load("Bmps/container.bmp");
	mesh = Mesh::generateCuboTex(h);
	//mesh = Mesh::generateRectanguloTex(h, h);
//    texture.load("..\\Bmps\\container.bmp");
    height = h;
    rectanguloMesh = Mesh::generateRectanguloTex(h, h, 1, 1);
    
}

void Cubo::drawMesh()
{
	texture.bind();
    //glLineWidth(2);
    mesh->draw();
	texture.unbind();
    texture.load("Bmps/container.bmp");

   // glLineWidth(1);
}

void Cubo::drawRectanguloMesh()
{
//    glLineWidth(2);
    texture.bind();
    rectanguloMesh->draw();
    texture.unbind();

//    glLineWidth(1);
}

void Cubo::render(const glm::dmat4 &modelViewMat){
    
    //para poner textura por dentro y por fuera
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    drawMesh();
    glDisable(GL_CULL_FACE);
    texture.load("Bmps/chuches.bmp");
    glPolygonMode(GL_BACK, GL_FILL);
    drawMesh();


    //glPolygonMode(GL_FRONT, GL_LINE);
    //glPolygonMode(GL_BACK, GL_POINT);
    

    dmat4 aMat = modelViewMat * modelMat;
    aMat = translate(aMat ,dvec3(0,height*0.85,0));
    aMat = translate(aMat ,dvec3(0,0,-(height*0.15)));
    aMat = rotate(aMat, radians(45.0), dvec3(1.0,0.0,0.0));

    glLoadMatrixd(value_ptr(aMat));
    drawRectanguloMesh();
    glPolygonMode(GL_FRONT, GL_FILL);

}


//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w,GLdouble h): Entity()
{
    //    mesh = Mesh::generateRectangle(w, h);
    dmat4 aMat = modelMat;
    aMat = rotate(aMat, radians(90.0), dvec3(1,0,0));
    aMat = translate(aMat, dvec3(0,400,0));
    texture.load("Bmps/baldosaC.bmp");
    modelMat = translate(modelMat, dvec3(00,-100,0));
    modelMat = rotate(modelMat, radians(90.0), dvec3(1,0,0));
    mesh = Mesh::generateRectanguloTex(w, h, 5, 5);

    //    texture.load("..\\Bmps\\baldosaC.bmp");
    
}
//-------------------------------------------------------------------------

void Suelo::draw()
{
    //    glLineWidth(2);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    texture.bind();
    mesh->draw();
    texture.unbind();
    //    glLineWidth(1);
}

//-------------------------------------------------------------------------

