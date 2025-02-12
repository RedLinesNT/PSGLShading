#pragma once
#include <GLES/gl.h>

class Texture {
public:
    Texture(const char* name);
    ~Texture();

    // ---------------------------------------------------------------------------
    // Load a .DDS (DirectDraw Surface) texture and load it into PSGL.
    // ---------------------------------------------------------------------------
    // Parameters:
    //    - file
    //          Path to the target .DDS file to load.
    // ---------------------------------------------------------------------------
    void LoadDDS(const char* file);
    // ---------------------------------------------------------------------------
    // Create a CheckerBoard texture on the fly.
    // ---------------------------------------------------------------------------
    // Parameters:
    //    - resolution
    //          The resolution (width AND height) in pixels of the texture.
    //          This parameter also determine the number of rows and columns
    //          that will be created.
    //    - rowsColor
    //          The color alternating on each pixel with "colsColor".
    //          This is a hexadecimal (little-endian) RGBA value.
    //    - colsColor
    //          The color alternating on each pixel with "rowsColor".
    //          This is a hexadecimal (little-endian) RGBA value.
    // ---------------------------------------------------------------------------
    //  Example:
    //      I want a pink color for the rows, the RGBA value will be
    //      "rgba(255, 100, 255, 255)". In hexadecimal, the value will
    //      be "FF64FFFF". But because the PlayStation3 uses big endianness,
    //      my value at the end will be "FFFF64FF", or "abgr(255, 255, 100, 255)".
    //
    //      In final, if I'd like to generate a 8x8 CheckerBoard texture,
    //      with pink and cyan, I'll input
    //      "CreateCheckerBoardTexture(16, 0xFFFF64FF, 0xFF64FFFF)"
    // ---------------------------------------------------------------------------
    void CreateCheckerBoardTexture(unsigned int resolution, unsigned int rowsColor, unsigned int colsColor);

private:
    // ---------------------------------------------------------------------------
    // The name of this texture.
    // ---------------------------------------------------------------------------
    const char* name;
    // ---------------------------------------------------------------------------
    // Does this Texture has data?
    // ---------------------------------------------------------------------------
    bool hasData;
    // ---------------------------------------------------------------------------
    // The width of the Texture loaded.
    // ---------------------------------------------------------------------------
    unsigned int width;
    // ---------------------------------------------------------------------------
    // The height of the Texture loaded.
    // ---------------------------------------------------------------------------
    unsigned int height;
    // ---------------------------------------------------------------------------
    // The size of the Texture loaded.
    // ---------------------------------------------------------------------------
    unsigned int size;
    // ---------------------------------------------------------------------------
    // The handle of this Texture.
    // ---------------------------------------------------------------------------
    GLuint texHandle;
};
