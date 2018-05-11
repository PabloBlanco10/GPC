#include "Mesh.h"

#define USE_MATH_DEFINE
#include <math.h>


using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
    delete[] vertices;
    delete[] colors;
}
//-------------------------------------------------------------------------

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

Mesh * Mesh::generateCuboTex(GLdouble l) {
    
    Mesh *m = generateContCubo(l);
    m->texCoords = new dvec2[m->numVertices];
    m->texCoords[0] = dvec2(0, 1);
    m->texCoords[1] = dvec2(0, 0);
    m->texCoords[2] = dvec2(1, 1);
    m->texCoords[3] = dvec2(1, 0);
    m->texCoords[4] = dvec2(2, 1);
    m->texCoords[5] = dvec2(2, 0);
    m->texCoords[6] = dvec2(3, 1);
    m->texCoords[7] = dvec2(3, 0);
    m->texCoords[8] = dvec2(4, 1);
    m->texCoords[9] = dvec2(4, 0);
    return m;
    
}

Mesh * Mesh::generateRectangulo(GLdouble w,GLdouble h){
    
    Mesh *m = new Mesh();
    m->type = GL_TRIANGLE_STRIP;
    m->numVertices = 4;
    
    m->vertices = new dvec3[m->numVertices];
    m->vertices[0] = dvec3(-(w/2), (h/2), 0);
    m->vertices[1] = dvec3(-(w/2), -(h/2), 0);
    m->vertices[2] = dvec3(w/2, h/2, 0);
    m->vertices[3] = dvec3(w/2, -(h/2), 0);
    
    //sirve para pintar solo las lineas y dibujarlo vacio
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    m->colors = new dvec4[m->numVertices];
    m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
    m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
    m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
    m->colors[3] = dvec4(1.0, 0.0, 0.0, 1.0);
    
    return m;
}

Mesh * Mesh::generateRectanguloTex(GLdouble w,GLdouble h, GLdouble replicaW, GLdouble replicaH){
    
    Mesh *m = generateRectangulo(w, h);
    m->texCoords = new dvec2[m->numVertices];
    m->texCoords[0] = dvec2(0, 1*replicaH);
    m->texCoords[1] = dvec2(0, 0);
    m->texCoords[2] = dvec2(1*replicaW, 1*replicaH);
    m->texCoords[3] = dvec2(1*replicaW, 0);
    return m;
    
}

Mesh * Mesh::generaMallaPorRevolucion(int m, int n, glm::dvec3* perfil){
    Mesh* mesh = new Mesh();
//    mesh->type = GL_LINE_LOOP;
    mesh->numVertices = n*m;
    mesh->vertices = new dvec3[mesh->numVertices];
    
    // Vertices de la malla
    for (int i=0; i<n; i++){ // Generar el perfil i-ésimo
        double theta = i*2*3.1416 / (double)n;
        double c = cos(theta);
        double s = sin(theta);
        // R_y es la matriz de rotación sobre el eje Y
        for (int j=0; j<m; j++) {
            int indice = i*m+j;
            // Transformar el punto j-ésimo del perfil original
            double x = c*perfil[j][0] + s*perfil[j][2];
            double z = -s*perfil[j][0] + c*perfil[j][2];
            dvec3 p = glm::dvec3(x, perfil[j].y, z);
            mesh->vertices[indice] = p;
        }
    }
//    mesh->normalize(m, n);
    return mesh;
}

void Mesh::normalize (int mm, int nn){
    normals = new dvec3[numVertices];
    /*for(int i = 0; i < mm*nn; i++){
        normals[i] = dvec3(0,0,0);
    }*/
    // Se ponen al vector nulo todas las componentes de normals
    for (int i = 0; i < nn; i++)
        for (int j = 0; j < mm-1; j++) {
            int indice = i*mm + j;
            // Por cada cara a la que pertenece el vértice índice,
            // se determinan 3 índices i0, i1, i2 de 3 vértices consecutivos de esa cara
            int i0 = (indice+mm) % (nn*mm);
            int i1 = (indice+mm+1) % (nn*mm);
            int i2 = indice + 1;
            
            dvec3 aux0 = vertices[indice];//vértice de i0;
            dvec3 aux1 = vertices[i0];
            dvec3 aux2 = vertices[i1];
            
            dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
            normals[indice] += norm;
            normals[i0] += norm;
            normals[i1] += norm;
            normals[i2] += norm;
            
        }
    // Finalmente, se normalizan todos los vectores normales
    for (int i = 0; i < nn; i++){
        for(int j = 0; j < mm; j++){
            normals[i * mm + j] = glm::normalize(normals[i * mm + j]);
        }
    }
//    for(int i = 0; i < mm*nn; i++){
//        normals[i] = glm::normalize(normals[i]);
//    }
    
}



dvec3 HipoMesh::curva(GLdouble t){
    return dvec3((a - b) * cos(t) + c * cos(t * ((a - b) / b )),
                 0,
                 (a - b) * sin(t) - c * sin(t * ((a - b) / b )));
}

dvec3 HipoMesh::derivada(GLdouble t){
    return dvec3(- (a - b) * sin(t) - c * ((a - b) / b) * sin(t * ((a - b) / b )),
                 0,
                 (a - b) * cos(t) - c * ((a - b) / b) * cos(t * ((a - b) / b )));
}

dvec3 HipoMesh::segundaDerivada(GLdouble t){
    return dvec3(- (a - b) * cos(t) - c * ((a - b) / b) * ((a - b) / b) *  cos(t * ((a - b) / b )),
                 0,
                 - (a - b) * sin(t) - c * ((a - b) / b) * ((a - b) / b) * sin(t * ((a - b) / b )));
}

//dvec3 HipoMesh::cargaN(dvec3 v){
//
//}



