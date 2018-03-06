//
//  Texture.cpp
//  MyApp
//
//  Created by Pablo Blanco Peris on 6/3/18.
//  Copyright © 2018 Pablo Blanco Peris. All rights reserved.
//

#include "Texture.h"
#include "PixMap32RGBA.h"


void Texture:: init() {
    glGenTextures(1, &id); // genera un identificador para una nueva textura glBindTexture(GL_TEXTURE_2D, id); // Filters and clamping glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
}

void Texture:: bind() {
    // argumento para el modo de mezclar los colores glBindTexture(GL_TEXTURE_2D, id); // activa la textura
    // la función de mezcla de colores no queda guardada en el objeto
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // GL_MODULATE / GL_ADD ...
}


bool Texture:: load(const std::string & BMP_Name, GLubyte alpha) {
    if (id == 0) init();
    PixMap32RGBA pixMap; // var. local para cargar la imagen del archivo pixMap.load_bmp24BGR(BMP_Name); // carga y añade alpha=255
    // carga correcta?
    if (alpha != 255) pixMap.set_alpha(alpha);
    w = pixMap.width();
    h = pixMap.height();
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, pixMap.data());
    
    return false;
}
