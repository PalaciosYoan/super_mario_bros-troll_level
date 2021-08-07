#ifndef game_h
#define game_h
#include <vector>
#include "Rect.h"
#include "Player.h"
#include "Sprite.h"
#include "TexRect.h"
#include "enemies.h"
#include <string>

class game {
enemies enemy;
TexRect* mapTex;
TexRect* gg;
TexRect* wonAni;
Player playerOne;
std::vector<Rect*> mapOb;
std::vector<Sprite*> coins;
std::vector<Sprite*> explosion;
std::vector<TexRect*> lives;
Sprite* explo;

bool hasJump;
bool isRun;
bool onGround;
bool faceJumpDir;
bool lastPressedA;
bool coinExplosion;
bool coinAni;
bool pause;
bool Mdeath;
bool hasWon;

float gravity;

int ground;
int roof;
int left;
int right;

bool* keyStates = new bool[256];

void redraw();
void animation();

public:
    game();
    void draw() const;
    void keyPressed(unsigned char key);
    void keyUp(unsigned char key);

    bool collision(float x, float y, float w, float h, int collisionSide);

    float getGravity() const;
    void setJump(bool);
    bool getJump();
    
    void playerState();
    void playerMovement();

    void pauseGame();
    bool getPause();

    void enemyAnimation();
    void gameReset(bool restart=false);
    
    friend void coinAnimation(int id);
    friend void explisionAnimation(int id);
    friend void GameLoop(int id);

    ~game();
};

#endif