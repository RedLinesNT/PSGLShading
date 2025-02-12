#include "Texture.h"

#include <cstdlib>
#include <GLES/glext.h>

#include "Core/Core.hpp"

Texture::Texture(const char* name): name(name) {
    hasData = false;
    size = 0;
    width = 0;
    height = 0;

    texHandle = NULL;
}

Texture::~Texture() {
    glDeleteTextures(1, &texHandle);

    DEBUG_PRINT("[Texture (%s)] '%u' bytes have been released.\n", name, size)
}

void Texture::LoadDDS(const char* file) {
    DEBUG_PRINT("[Texture (%s)] Texture::LoadDDS isn't implemented... Generating a default CheckerBoard texture instead.\n", name)
    CreateCheckerBoardTexture(8, 0xFF64FFFF, 0xFFFFFFFF);
}

void Texture::CreateCheckerBoardTexture(unsigned int resolution, unsigned int rowsColor, unsigned int colsColor) {
    glGenTextures(1, &texHandle);
    width = resolution;
    height = resolution;
    size = sizeof(unsigned int) * resolution * resolution;
    hasData = true;
    
    unsigned int *texData = (unsigned int*)std::malloc(size);
    unsigned int *texPixels = texData;
    bool flip = true; //flip is used to generate the CheckerBoard pattern

    for (unsigned int i=0; i<resolution; i++) {
        for (unsigned int j=0; j<resolution; j++) {
            if (flip) *texPixels = rowsColor;
            else *texPixels = colsColor;

            texPixels++;
            flip = !flip;
        }
        
        flip = !flip;
    }


    //Basic OpenGL texture setup...
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,(GLsizei)resolution,(GLsizei)resolution,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8, texData);

    std::free(texData);

    DEBUG_PRINT("[Texture (%s)] CheckerBoard texture created! (%ux%u - %u bytes)\n", name, width, height, size)
}
