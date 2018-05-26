//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"

//-------------------------------------------------------------------------

class Scene	: public CompoundEntity
{ 
public:
    Scene(Camera * cam): camera(cam) { };
    ~Scene();
    void init();
    void render();
    void rotarDiabolo();
    void movebb8();
    void divideViewPort();
    void renderDiaboloWithAxes();
    void renderCubeWithAxes();
    void renderScenario();
    void renderPractica2();

    

    
protected:
    Camera * camera;
    std::vector<Entity*> objetos;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

