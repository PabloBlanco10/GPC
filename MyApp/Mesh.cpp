#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
    delete[] vertices;
    delete[] colors;
}
//-------------------------------------------------------------------------

//void Mesh::draw()
//{
//    if (vertices != nullptr) {
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate
//        if (colors != nullptr) {
//            glEnableClientState(GL_COLOR_ARRAY);
//            glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate
//        }
//        
//        glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count
//        
//        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//        glDisableClientState(GL_COLOR_ARRAY);
//        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
////            glEnable(GL_TEXTURE_2D);
//
//    }
//}


void Mesh::draw()
{
    if (vertices != nullptr) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate
        if (colors != nullptr) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate
        }
        if(texCoords != nullptr){
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        }
        glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count
        
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
   
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
    Mesh *m = new Mesh();
    m->type = GL_LINES;
    m->numVertices = 6;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(0.0, 0.0, 0.0);
    m->vertices[1] = dvec3(l, 0.0, 0);
    m->vertices[2] = dvec3(0, 0.0, 0.0);
    m->vertices[3] = dvec3(0.0, l, 0.0);
    m->vertices[4] = dvec3(0.0, 0.0, 0.0);
    m->vertices[5] = dvec3(0.0, 0.0, l);
    
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
    m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
    
    return m;
}

//genera losvértice sdel triángulo equilátero, de radio r, centrado en el plano Z=0
//(Utiliza la primitiva TRIANGLES).
// para generar el triangulo tiene q haber 360 grados, el primero + 120 y el siguiente +120
//sin(radians(90)) + 120 + 120

Mesh * Mesh::generateTriangle(GLdouble r){
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLES;
    m->numVertices = 3;
    GLdouble valor = 90.0;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(r*cos(radians(valor)),r* sin(radians(valor)) , 0.0);
    m->vertices[1] = dvec3(r*cos(radians(valor+120)), r*sin(radians(valor+120)), 0.0);
    m->vertices[2] = dvec3(r*cos(radians(valor+240)), r*sin(radians(valor+240)), 0.0);
    
    
    //   rosa - rgb(255,105,180)
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.4, 0.7, 1.0);
    m->colors[1] = dvec4(1.0, 0.4, 0.7, 1.0);
    m->colors[2] = dvec4(1.0, 0.4, 0.7, 1.0);
    
    return m;
}
//-------------------------------------------------------------------------


Mesh * Mesh::generateTriangleRGB(GLdouble r){
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLES;
    m->numVertices = 3;
    GLdouble valor = 90.0;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(r*cos(radians(valor)),r* sin(radians(valor)) , 0.0);
    m->vertices[1] = dvec3(r*cos(radians(valor+120)), r*sin(radians(valor+120)), 0.0);
    m->vertices[2] = dvec3(r*cos(radians(valor+240)), r*sin(radians(valor+240)), 0.0);
    
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
    
    return m;
}

Mesh * Mesh::generateTriPyramid(GLdouble r,GLdouble h){
    
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLE_FAN;
    m->numVertices = 5;
    GLdouble valor = 90.0;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(0.0, 0.0, h);
    m->vertices[1] = dvec3(r*cos(radians(valor)),r* sin(radians(valor)) , 0.0);
    m->vertices[2] = dvec3(r*cos(radians(valor+120)), r*sin(radians(valor+120)), 0.0);
    m->vertices[3] = dvec3(r*cos(radians(valor+240)), r*sin(radians(valor+240)), 0.0);
    m->vertices[4] = dvec3(r*cos(radians(valor)),r* sin(radians(valor)) , 0.0);
    
    //sirve para pintar solo las lineas y dibujarlo vacio
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //quitamos los colores para pintar el diabolo
    //    m->colors = new dvec4[m->numVertices];
    //    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    //    m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
    //    m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
    //    m->colors[3] = dvec4(1.0, 0.0, 0.0, 1.0);
    //    m->colors[4] = dvec4(0.0, 1.0, 0.0, 1.0);
    //
    return m;
}

Mesh * Mesh::generateTriPyramidTex(GLdouble r,GLdouble h){
    Mesh *m = generateTriPyramid(r, h);
    m->texCoords = new dvec2[m->numVertices];
    m->texCoords[0] = dvec2(0, 1);
    m->texCoords[1] = dvec2(0, 0);
    m->texCoords[2] = dvec2(1, 1);
    m->texCoords[3] = dvec2(1, 0);
    m->texCoords[4] = dvec2(0, 1);

    return m;
}

Mesh * Mesh::generateContCubo(GLdouble l){
    
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLE_STRIP;
    m->numVertices = 10;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(-(l/2), l/2, l/2);
    m->vertices[1] = dvec3(-(l/2), -(l/2), l/2);
    m->vertices[2] = dvec3(l/2, l/2, l/2);
    m->vertices[3] = dvec3(l/2, -(l/2), l/2);
    m->vertices[4] = dvec3(l/2, l/2, -(l/2));
    m->vertices[5] = dvec3(l/2, -(l/2), -(l/2));
    m->vertices[6] = dvec3(-(l/2), l/2, -(l/2));
    m->vertices[7] = dvec3(-(l/2), -(l/2), -(l/2));
    m->vertices[8] = dvec3(-(l/2), l/2, l/2);
    m->vertices[9] = dvec3(-(l/2), -(l/2), l/2);
    
    
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
    m->colors[3] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[4] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[5] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[6] = dvec4(0.0, 0.0, 1.0, 1.0);
    m->colors[7] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[8] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[9] = dvec4(0.0, 0.0, 1.0, 1.0);
    return m;
}

Mesh * Mesh::generateRectangulo(GLdouble w,GLdouble h){
    
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLE_STRIP;
    m->numVertices = 4;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(-(w/2), -(h/2), 0);
    m->vertices[1] = dvec3(-(w/2), h/2, 0);
    m->vertices[2] = dvec3(w/2, -(h/2), 0);
    m->vertices[3] = dvec3(w/2, h/2, 0);
    
    //sirve para pintar solo las lineas y dibujarlo vacio
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
    m->colors[3] = dvec4(1.0, 0.0, 0.0, 1.0);
    
    return m;
}

Mesh * Mesh::generateRectanguloTex(GLdouble w,GLdouble h){
    
    Mesh *m = generateRectangulo(w, h);
    m->texCoords = new dvec2[m->numVertices];
    m->texCoords[0] = dvec2(0, 1);
    m->texCoords[1] = dvec2(0, 0);
    m->texCoords[2] = dvec2(1, 1);
    m->texCoords[3] = dvec2(1, 0);
    return m;
    
}



