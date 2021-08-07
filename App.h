#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "game.h"
#include "Circle.h"
#include "TexRect.h"

class App: public GlutApp {
TexRect* pause;
game Game;
bool mainMenu;
void pauseMenu(bool reset=false);
public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    
    ~App();
};

#endif
