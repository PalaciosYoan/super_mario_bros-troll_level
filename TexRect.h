#ifndef TexRect_h
#define TexRect_h

#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include "SOIL.h"
#else
#include <GL/freeglut.h>
#include "SOIL.h"
#endif


class TexRect: public Rect {
protected:
    GLuint texture_id;
    
    int texwidth;
    int texheight;
    
public:
    TexRect(const char* filename, float x, float y, float w, float h);
    
    void draw(float z=0) const;
};

#endif
