#include <iostream>
#include "App.h"


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    mainMenu = true;
    pause = new TexRect("images/pause.png",-1, 1, 2,2);
} 

void App::draw() const {
    if(mainMenu)
    {
        pause->draw();
    }
    else
        Game.draw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    else if (key == 'p')
        pauseMenu();
    else if (key=='r' && mainMenu)
        pauseMenu(true);
    else if (!mainMenu)
        Game.keyPressed(key);
}


void App::keyUp(unsigned char key, float x, float y){
    Game.keyUp(key);
}

void App::pauseMenu(bool reset)
{
    if(reset)
        Game.gameReset(true);
    
    Game.pauseGame();
    mainMenu = !mainMenu;
}
App::~App(){   
    std::cout << "Exiting..." << std::endl;
}
