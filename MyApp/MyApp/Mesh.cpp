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

    for (int i = 0; i < nn; i++){
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

HipoMesh::HipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c){
    
    this-> nP = nP;
    this-> nQ = nQ;
    this-> a = a;
    this-> b = b;
    this-> c = c;
    this->vertices = new dvec3[nP*nQ];
    this->numVertices = nP*nQ;
    
    creaBase();
    GLdouble t = 0.0;
    cargaMatriz(t);
    creaVerticesIniciales();
    GLdouble saltoEntreRodajas = 8*3.1416/(nQ-1);
    for (int i = 1; i < nQ; i++) {
        t += saltoEntreRodajas;
        cargaMatriz(t);
        creaRodaja(i);
    }
    glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);
    normalize(nQ, nP);
}

void HipoMesh::creaBase(){ //Guarda en base el polígono que aproxima la circunferencia del tubo
    double inc=(2*3.1416/nP);
    base = new dvec3[nP];
    
    for (int i=0; i<nP; i++)
        base[i]= glm::dvec3(r*cos(i*inc), r*sin(i*inc),0); // El uno, define un punto en la rodaja
}

void HipoMesh::creaVerticesIniciales(){//Añade los primeros nP vértices
    creaRodaja(0);
}

void HipoMesh::creaRodaja(int v){//Añade nP nuevos vértices, a partir de la componente v
    dvec4 *baseAux = new dvec4[nP];

    for (int i=0; i<nP; i++){
        baseAux[i] = glm::dvec4(base[i][0], base[i][1], base[i][2], 1);
        vertices[i + v*nP] = multiplicar(m, baseAux[i]);
     }
}

void HipoMesh::cargaMatriz(GLdouble t){//Define la matriz m para t
    dvec3 vector_curva = curva(t);
    dvec3 vector_primera_derivada = derivada(t);
    dvec3 vector_segunda_derivada = segundaDerivada(t);
    dvec3 vector_t = glm::normalize(vector_primera_derivada);
    dvec3 vector_b = glm::normalize(glm::cross(vector_primera_derivada, vector_segunda_derivada));
    dvec3 vector_n = glm::cross(vector_b, vector_t);
    
//    La transformación es la matriz 4×4 M(t)=(N(t), B(t), T(t), C(t))
//    donde las tres primeras columnas son vectores y la última, punto.
    for (int i = 0; i < 3; i++){
        m[i][0] = vector_n[i];
        m[i][1] = vector_b[i];
        m[i][2] = vector_t[i];
        m[i][3] = vector_curva[i];
    }
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
    
}

void HipoMesh::normalize (int nQ, int nP){
    normals = new dvec3[numVertices];

    for (int i = 0; i < nQ; i++)
        for (int j = 0; j < nP-1; j++) {
            int indice = i*nP + j;
            // Por cada cara a la que pertenece el vértice índice,
            // se determinan 3 índices i0, i1, i2 de 3 vértices consecutivos de esa cara
            int i0 = (indice+nP) % (nQ*nP);
            int i1 = (indice+nP+1) % (nQ*nP);
            int i2 = indice + 1;
            
            dvec3 aux0 = vertices[indice];//vértice de i0;
            dvec3 aux1 = vertices[i1];
            dvec3 aux2 = vertices[i2];
            
            dvec3 norm = glm::cross(aux1 - aux2, aux0 - aux2);
            normals[indice] += norm;
            normals[i1] += norm;
            normals[i2] += norm;
            normals[i0] += norm;
        }
    // Finalmente, se normalizan todos los vectores normales
    for (int i = 0; i < nQ; i++){
        for(int j = 0; j < nP; j++){
            normals[i * nP + j] = glm::normalize(normals[i * nP + j]);
        }
    }
//    for(int i = 0; i < nP * nQ; i++){
//        normals[i] = normals[i] * 50.0;
//    }
    //    for(int i = 0; i < mm*nn; i++){
    //        normals[i] = glm::normalize(normals[i]);
    //    }
    
}


dvec3 HipoMesh::multiplicar(dmat4 m, dvec4 vertice){
    
    dvec4 vectAux;
    double totalCelda = 0;
    for (int i =0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            totalCelda += m[i][j] * vertice[j];
        }
        vectAux[i] = totalCelda;
        totalCelda = 0;
    }
    
    //vectAux[3] = 1;//en la ultima posición del vector se pone 1 para indicar que es un punto no un vector
    return dvec3(vectAux[0], vectAux[1], vectAux[2]);
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

glm::dmat4 HipoMesh::getM(GLdouble t){
    dmat4 matrix;
    
    dvec3 vector_curva = curva(t);
    dvec3 vector_primera_derivada = derivada(t);
    dvec3 vector_segunda_derivada = segundaDerivada(t);
    dvec3 vector_t = glm::normalize(vector_primera_derivada);
    dvec3 vector_b = glm::normalize(glm::cross(vector_primera_derivada, vector_segunda_derivada));
    dvec3 vector_n = glm::cross(vector_b, vector_t);
    
//    (N B T | 0)
//    ( C(T) | 1)
    for (int i = 0; i < 3; i++){
        matrix[i][0] = vector_n[i];
        matrix[i][1] = vector_b[i];
        matrix[i][2] = vector_t[i];
        matrix[3][i] = vector_curva[i];
    }
    matrix[0][3] = 0;
    matrix[1][3] = 0;
    matrix[2][3] = 0;
    matrix[3][3] = 1;
    
    return matrix;
}



//dvec3 HipoMesh::cargaN(dvec3 v){
//
//}



