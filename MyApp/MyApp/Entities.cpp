#include "Entities.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{
    glColor3d(re, gr, bl);
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

//-------------------------------------------------------------------------


Grass::Grass(GLdouble l): Entity()
{
    modelMat = translate(modelMat, dvec3(500.0, -l/2, -500.0));
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


void Grass::render(const glm::dmat4 &modelViewMat){    
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    glLoadMatrixd(value_ptr(aMat));
    draw();
    aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
    aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
    aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
    glLoadMatrixd(value_ptr(aMat));
    draw();
}

MPR::MPR(int n) : Entity(){
    //    glPolygonMode(GL_FRONT, GL_FILL);
//    glColor3d(1.0, 1.0, 1.0);

    glColor3f(re, gr, bl);

    //    this->m = 3; //número de puntos del perfil //mm
    //    this->n = n;
    //    dvec3* perfil = new dvec3[m];
    //    perfil[0] = dvec3(0, 0, 0);
    //    perfil[1] = dvec3(20, 0, 0);
    //    perfil[2] = dvec3(0, 50, 0);
    
    
    this->m = 100; //número de puntos del perfil //mm
    this->n = n;
    
    //PERFIL PARA EL CASCO DEL BB8
    int r = 20;
    dvec3* perfil = new dvec3[m];
    perfil[0] = dvec3(0, 0, 0);
    double angulo = 3.1416 /( 2 *( m - 3));
    
    perfil[1] = dvec3(r*0.9 * cos(-3.1416/180),r*0.8 * sin(-3.1416/180), 0);
    
    for(int i = 2; i < m-2; i++){
        perfil[i] = dvec3(r * cos(angulo*i) ,r * sin(angulo*i) , 0);
    }

//    double angulo = M_PI / (2 * (this->m - 3));
//    perfil[0] = dvec3(0.0, 0.0, 0.0);
//    perfil[1] = dvec3(r*cos(-M_PI / 160), r*sin(-M_PI / 160), 0.0);
//    for(int i = 2; i < this->m-1; i++){
//        perfil[i] = dvec3(r*cos(angulo*i), r*sin(angulo*i), 0.0);
//    }
    
    
    perfil[m-1] = dvec3(0, r, 0);
    this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
    mesh->normalize(m, n);
}


void MPR::draw() {
    //    ...
    dvec3* vertices = mesh->getVertices();
    //dvec4* colors = mesh->getColours();
    dvec3* normals = mesh-> getNormals();
    if (vertices != nullptr) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glNormalPointer(GL_DOUBLE, 0, normals);
        //        if (colors != nullptr) {
        //            glEnableClientState(GL_COLOR_ARRAY);
        //            glColorPointer(4, GL_DOUBLE, 0, colors);
        //
        //        }
        //if (normals != nullptr){
        // }
    }
    // Después del dibujo de los elementos por índices,
    // se deshabilitan los vertex arrays, como es habitual
    //        ...
    // Definición de las caras
    for (int i=0; i< n; i++){ // Unir el perfil i-ésimo con el (i+1)%n-ésimo
        for (int j=0; j<(m-1); j++) { // Esquina inferior-izquierda de una cara
            int indice = i*m+j;
            int stripIndices[] = {indice, (indice + m) %(n*m),(indice + m + 1) %(n*m), indice + 1};
            //            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, stripIndices);
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
            // o GL_POLYGON, si se quiere las caras con relleno
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}



Hipotrocoide::Hipotrocoide(int nP,int nQ, int aHipo, int bHipo, int cHipo) : Entity() {
    
    //    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3d(0.0, 0.0, 1.0);
    this-> nP = nP;
    this-> nQ = nQ;
    this-> a = aHipo;
    this-> b = bHipo;
    this-> c = cHipo;
    
    //    mesh = new HipoMesh(nP,nQ,a,b,c);
    HipoMesh *hipomesh = new HipoMesh(nP,nQ,a,b,c);
    hipomesh->normalize(nQ, nP);
    mesh = hipomesh;
//        mesh->normalize(nQ, nP);
    
}

void Hipotrocoide::draw(){
    
    dvec3* vertices = mesh->getVertices();
    //dvec4* colors = mesh->getColours();
    dvec3* normals = mesh-> getNormals();
    if (vertices != nullptr) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glNormalPointer(GL_DOUBLE, 0, normals);
        //        if (colors != nullptr) {
        //            glEnableClientState(GL_COLOR_ARRAY);
        //            glColorPointer(4, GL_DOUBLE, 0, colors);
        //        }
        //if (normals != nullptr){
        // }
    }
    // Después del dibujo de los elementos por índices,
    // se deshabilitan los vertex arrays, como es habitual
    //        ...
    // Definición de las caras
    for (int i=0; i < nQ - 1; i++){ // Unir el perfil i-ésimo con el (i+1)%n-ésimo
        for (int j=0; j< (nP-1); j++) { // Esquina inferior-izquierda de una cara
            int indice = (i*nP) + j;
            int stripIndices[] = {indice, (indice + 1),(indice + nP + 1), indice + nP};
            //            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, stripIndices);
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
            // o GL_POLYGON, si se quiere las caras con relleno
        }
        int indice = i * nP + (nP - 1);
        int stripIndices[] = {indice, (indice - (nP - 1)),(indice + 1), indice + nP};
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
        
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}



Sphere::Sphere(GLdouble l) :QuadricEntity(){
    r = l;
    q = gluNewQuadric();
    //    gluQuadricTexture(sphere, GLU_TRUE);
}

void Sphere::draw()
{
    glColor3f(re, gr, bl);
    // En la Práctica 2, el color se debe incorporar con tres
    // atributos en Entity de tipo GLfloat o con un nuevo atributo de
    // clase Color que tiene 3 atributos de tipo GLfloat
    
    gluQuadricDrawStyle(q, GLU_FILL);
    gluSphere(q, r, 30, 30);
    gluQuadricTexture(q, GLU_TRUE);

    //    texture.bind();
    gluSphere(q, r, r, r);
    //    texture.unbind();
    
    //    mesh->draw();
}


void CompoundEntity::render(const glm::dmat4 &modelViewMat){
    //    if (visible) {
    //        ... // Se sitúa en la escena (post-)multiplicando
    // por su matriz modelMat y se guarda el resultado en aMat // Se renderizan sus componentes con respecto a aMat
    
    glMatrixMode(GL_MODELVIEW);
    dmat4 aMat = modelViewMat * modelMat;
    glLoadMatrixd(value_ptr(aMat));
    
        for(auto &it : entities){
            it->render(aMat);
        }
    //        for each (Entity* it in entities) {
    //            it->render(aMat);
    //        }
    //    }
}


