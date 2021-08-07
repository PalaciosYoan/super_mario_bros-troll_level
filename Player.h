#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Rect.h"
#include "TexRect.h"
#include "Sprite.h"
#include "Shape.h"
#include <vector>

class Player: public Rect{
TexRect* MStay;
Sprite* MRun;
TexRect* MJump;

bool flipImg;
bool marioRun;
bool accountForDisplacement;

float jumpVelocity;
int cmd;
int lives;

public:
	Player(float r=0, float g=1, float b=0);

    void setCMD(int x, bool flip=false);

    void drawMario() const;
    void updateMarioPosition();
    void animation();

    float getJumpVelocity();
    void setJumpVelocity(float g, bool fall = false);
    void resetVelocity();

    int getLives() const;
    void death();
    
    void reset(bool resetLives=false);

    friend void playerAnimationTimer(int id);
    ~Player();
};

#endif