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
    modelMat = translate(modelMat, dvec3(250,0,-150));
    modelMat = rotate(modelMat, radians(30.0), dvec3(0,1,0));
    height = h;
    mesh = Mesh::generateTriPyramidTex(r, h);
    texture.load("Bmps/floris.bmp");
//    texture.load("..\\Bmps\\floris.bmp");
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{    
    texture.bind();
    mesh->draw();
    texture.unbind();
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

    mesh = Mesh::generateRectanguloTex(w, h, 0, 0);
    texture.load("Bmps/container.bmp");
//    texture.load("..\\Bmps\\container.bmp");

}
//-------------------------------------------------------------------------

void Rectangulo::draw()
{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    texture.bind();
    mesh->draw();
    texture.unbind();
}

//-------------------------------------------------------------------------


Cubo::Cubo(GLdouble h): Entity()
{
    height = h;
    modelMat = translate(modelMat, dvec3(-height/2,0,0));
    texture.load("Bmps/container.bmp");
    textureIn.load("Bmps/chuches.bmp");
//    texture.load("..\\Bmps\\container.bmp");
    mesh = Mesh::generateCuboTex(h);
    rectanguloMesh = Mesh::generateRectanguloTex(h, h, 1, 1);
}

void Cubo::drawMesh()
{
	texture.bind();
    mesh->draw();
	texture.unbind();
}

void Cubo::drawRectanguloMesh()
{
    texture.bind();
    rectanguloMesh->draw();
    texture.unbind();
}

void Cubo::drawMeshIn()
{
    textureIn.bind();
    mesh->draw();
    textureIn.unbind();
}

void Cubo::render(const glm::dmat4 &modelViewMat){
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    glLoadMatrixd(value_ptr(aMat));
    //para poner textura por dentro y por fuera
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    drawMesh();
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_BACK, GL_FILL);
    drawMeshIn();

    //glPolygonMode(GL_FRONT, GL_LINE);
    //glPolygonMode(GL_BACK, GL_POINT);

    aMat = modelViewMat * modelMat;
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
    texture.load("Bmps/baldosaC.bmp");
    //    texture.load("..\\Bmps\\baldosaC.bmp");
    modelMat = translate(modelMat, dvec3(00,-100,0));
    modelMat = rotate(modelMat, radians(90.0), dvec3(1,0,0));
    mesh = Mesh::generateRectanguloTex(w, h, 5, 5);
    
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


GlassPot::GlassPot(GLdouble l): Entity()
{
    modelMat = translate(modelMat, dvec3(500.0, 0.0, -500.0));
    texture.load("Bmps/window.bmp", 50);
    mesh = Mesh::generateCuboTex(l);
}
//-------------------------------------------------------------------------

void GlassPot::draw()
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texture.bind();
    mesh->draw();
    texture.unbind();
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

}

void GlassPot::render(const glm::dmat4 &modelViewMat){
    glMatrixMode(GL_MODELVIEW);
    
    dmat4 aMat = modelViewMat * modelMat;
    glLoadMatrixd(value_ptr(aMat));
    draw();
    
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
    
    aMat = modelViewMat * modelMat;
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
    
    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
}


//-------------------------------------------------------------------------


Grass::Grass(GLdouble l): Entity()
{

    modelMat = translate(modelMat, dvec3(500.0, 0.0, -500.0));
//    modelMat = rotate(modelMat, radians(180.0), dvec3(0.0,1.0,0.0));
    texture.load("Bmps/grass.bmp", ivec3(0,0,0), 0);

    mesh = Mesh::generateRectanguloTex(l, l, 1, 1);
}
//-------------------------------------------------------------------------

void Grass::draw()
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texture.bind();
    mesh->draw();
    texture.unbind();
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

//void Grass::render(const glm::dmat4 &modelViewMat){
//    glMatrixMode(GL_MODELVIEW);
//
//    dmat4 aMat = modelViewMat * modelMat;
//    glLoadMatrixd(value_ptr(aMat));
//    draw();
//
//
//    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
//    glLoadMatrixd(value_ptr(aMat));
//    draw();
//
//    aMat = modelViewMat * modelMat;
//    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
//    glLoadMatrixd(value_ptr(aMat));
//    draw();
//
//    aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
//    glLoadMatrixd(value_ptr(aMat));
//    draw();
//}
