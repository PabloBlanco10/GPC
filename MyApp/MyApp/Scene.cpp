#include "Scene.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
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
    //    objetos.push_back(new MPR(20));
    
    int nP = 20;// Número de lados del polígono que aproxima la circunferencia que define el tubo
    int nQ = 200;// Número de rodajas que forman la hipotrocoide
    int aHipo = 7;
    int bHipo = 4;
    int cHipo = 2 ;
    
    objetos.push_back(new Hipotrocoide(nP, nQ, aHipo, bHipo, cHipo));
    
    ////////////////////////////////////////
////////////    BB8
    ////////////////////////////////////////

    CompoundEntity * bb8 = new CompoundEntity();
    objetos.push_back(bb8);
    
    CompoundEntity* cabeza = new CompoundEntity(); // Cabeza
    bb8->entities.push_back(cabeza);

    // Aquí se fija el color de la cabeza
    
    // Se sube la cabeza
    cabeza->modelMat=glm::translate(cabeza->modelMat, glm::dvec3(0, 40, 0));
    
    //semiesfera por revolucion
    MPR * testa = new MPR(50); // Testa
    testa->re = 1;
    testa->gr = 1;
    testa->bl = 1;
    cabeza->entities.push_back(testa);

    
    Sphere* ojo = new Sphere(2); //Ojo
    ojo->re = 0;
    ojo->gr = 0;
    ojo->bl = 0;
    cabeza->entities.push_back(ojo);

    ojo->modelMat = glm::translate(ojo->modelMat, glm::dvec3(14,14, 0));
    
    
    CompoundEntity* cuerpo = new CompoundEntity(); // Cabeza
    // Aquí se fija el color del cuerpo
    bb8->entities.push_back(cuerpo);
    
    Sphere* panza = new Sphere(40); // Cuerpo
    // Aquí se fija el color del cuerpo
    panza->re = 1;
    panza->gr = 1;
    panza->bl = 0.89;
    cuerpo->entities.push_back(panza);
    

    Sphere* testigo = new Sphere(2); // testigo
    // Aquí se fija el color del testigo
    testigo->re = 0;
    testigo->gr = 0;
    testigo->bl = 0;
    cuerpo->entities.push_back(testigo);
    

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
    //it[0]->render(camera->getViewMat());
    //it[1]->render(camera->getViewMat());
    glm::dmat4 viewMatAux = camera->getViewMat(); 
    viewMatAux = glm::scale(viewMatAux, glm::dvec3(50,50,50));
    //    modelMat = rotate(modelMat, radians(45.0), dvec3(0.0,0.0,1.0));
    
//    it[1]->render(viewMatAux);
    it[2]->render(camera->getViewMat());
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


