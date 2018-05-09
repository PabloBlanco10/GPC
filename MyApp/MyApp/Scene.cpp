#include "Scene.h"

//-------------------------------------------------------------------------


void Scene::init()
{ // OpenGL basic setting
//    glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
//
    glClearColor(0.6f, 0.7f, 0.8f, 1.0); // Fondo azul (o el que prefieras)
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Light0
    GLfloat d[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
    GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);
    GLfloat p[] = { 50.0f, 50.0f, 50.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, p);
    camera->set3D();
    
    //    camera->setAZ();
    // lights
    // textures
    //    glEnable(GL_TEXTURE_2D);
    
    
    // objets
    
    //0
        objetos.push_back(new EjesRGB(350));
    //    objetos.push_back(new Triangle(200.0));
    //    objetos.push_back(new TriangleRGB(200.0));
    //    objetos.push_back(new TriPyramid(200.0, 300.0));
    //    objetos.push_back(new ContCubo(200.0));
    //    //5
    //    objetos.push_back(new Diabolo(100.0, 150.0));
    //    objetos.push_back(new Rectangulo(200.0, 200.0, 0, 0));
    //    objetos.push_back(new Suelo(1200.0, 1200.0));
    //    objetos.push_back(new Cubo(200.0));
    //    objetos.push_back(new Grass(100.0));
    //10
    //    objetos.push_back(new GlassPot(200.0));
    objetos.push_back(new MPR(20));

}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources
    
    //////////////////////////////
    //  PARA EJECUTAR EN EL MAC
    //////////////////////////////
    
    for(auto &it : objetos){
        delete it;
    }
    
    //////////////////////////////
    //  CODIGO INICIAL
    //////////////////////////////
    
    //  for each (Entity* it in objetos)
    //  {
    //    delete it;
    
    //  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
    glMatrixMode(GL_MODELVIEW);
    
    //////////////////////////////
    //      RENDERIZAR OBJETOS
    ////////////////////////////////
    //    auto &it = objetos;
    //    //
    //    it[0]->render(camera->getViewMat());
    //    it[8]->render(camera->getViewMat());
    //    it[7]->render(camera->getViewMat());
    
    
    renderPractica2();
    
    
    //////////////////////////////
    //      PARA PRACTICA1
    //////////////////////////////
//    renderScenario();
    
    //////////////////////////////
    //      PARA CUBO CON TAPA
    //////////////////////////////
    //        renderCubeWithAxes();
    
    
    //////////////////////////////
    //      PARA DIABOLO CON EJES
    //////////////////////////////
    
    //        renderDiaboloWithAxes();
    
    
    //////////////////////////////
    //    PARA DIVIDIR EN 4 EL PUERTO DE VISTA
    //////////////////////////////
    
    //            divideViewPort();
    
    
    //////////////////////////////
    ////    PARA EJECUTAR EN EL MAC
    //////////////////////////////
    
    //renderizar todos los objetos
    //        for(auto &it : objetos){
    //            it->render(camera->getViewMat());
    //        }
    
    //////////////////////////////
    //      CODIGO INICIAL
    //////////////////////////////
    
    //    for each (Entity* it in objetos)
    //    {
    //        it->render(camera->getViewMat());
    //    }
    
}
//----------------------------------

void Scene::rotarDiabolo(){
    for(auto &it: objetos){
        //casteamos para comprobar si es de la clase Diabolo
        if(dynamic_cast<Diabolo*>(it) != nullptr){
            //en caso de que sea de la clase Diabolo, llamamos a la funcion que lo rota
            static_cast<Diabolo*>(it)->rotateDiabolo();
        }
    }
}



void Scene::renderPractica2(){
    auto &it = objetos;
  //  it[0]->render(camera->getViewMat());
    it[1]->render(camera->getViewMat());
}

//-------------------------------------------------------------------------

void Scene::renderScenario(){
    auto &it = objetos;
    it[0]->render(camera->getViewMat());
    it[8]->render(camera->getViewMat());
    it[7]->render(camera->getViewMat());
    it[5]->render(camera->getViewMat());
    it[9]->render(camera->getViewMat());
    it[10]->render(camera->getViewMat());
}


//-------------------------------------------------------------------------

void Scene::renderDiaboloWithAxes(){
    auto &it = objetos;
    it[5]->render(camera->getViewMat());
    it[0]->render(camera->getViewMat());
}


//-------------------------------------------------------------------------

void Scene::renderCubeWithAxes(){
    auto &it = objetos;
    it[0]->render(camera->getViewMat());
    it[7]->render(camera->getViewMat());//
}


//-------------------------------------------------------------------------

void Scene::divideViewPort(){
    auto &it = objetos;
    Viewport viewport = *camera->getVP();
    viewport.setSize(400, 300);
    
    viewport.setPos(0, 0);
    it[0]->render(camera->getViewMat());
    viewport.setPos(400, 0);
    it[1]->render(camera->getViewMat());
    viewport.setPos(0, 300);
    it[2]->render(camera->getViewMat());
    viewport.setPos(400, 300);
    glColor3d(0.0, 0.0, 0.0);
    it[3]->render(camera->getViewMat());
}


