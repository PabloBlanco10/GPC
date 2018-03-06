//
//  Texture.hpp
//  MyApp
//
//  Created by Pablo Blanco Peris on 6/3/18.
//  Copyright © 2018 Pablo Blanco Peris. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp


#include <GL/freeglut.h>
#include <glm.hpp>
#include <stdio.h>
#include <iostream>


class Texture // utiliza la clase PixMap32RGBA para el método load
{
    
public:
    Texture(): w(0), h(0), id(0) {};
    ~Texture() {if (id !=0 ) glDeleteTextures(1, &id); };
    bool load(const std::string & BMP_Name, GLubyte alpha = 255);
    // cargar y transferir a openGL
    void bind();
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
    GLuint w, h; // dimensiones de la imagen
    GLuint id; // identificador interno (GPU) de la textura
    void init();
    
};



#endif /* Texture_hpp */
