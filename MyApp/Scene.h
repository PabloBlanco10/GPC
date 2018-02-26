//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

////////////////////////////////
// CODIGO INICIAL PARA WINDOWS
////////////////////////////////
//#include <GL/freeglut.h>
//#include <vector>
//#include "Camera.h"
//#include "Entities.h"

////////////////////////////////
// CODIGO PARA MAC
////////////////////////////////
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"


//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera & cam): camera(cam) { };
    ~Scene();
    void init();
    void render();
    void rotarDiabolo();
    void divideViewPort();
    void renderDiaboloWithAxes();
    
protected:
    Camera & camera;
    std::vector<Entity*> objetos;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

