#include "Player.h"
#include "GlutApp.h"
#include <iostream>
static Player* Singleton;
void playerAnimationTimer(int id)
{
    Singleton->animation();
    glutTimerFunc(100,playerAnimationTimer, id);
}


Player::Player(float r, float g, float b): Rect(-0.5, -0.5, 0.06, 0.13, r, g, b){
    //Three possible animation. Run, Jump, Standing still
    MStay = new TexRect("images/MarioAnimation/MStay.png", this->x, this->y, 0.12,0.1);
    MRun = new Sprite("images/MarioAnimation/MRun.png", 1, 3,this->x, this->y, 0.12, 0.10);
    MJump = new TexRect("images/MarioAnimation/MJump.png", this->x, this->y, 0.12,0.1);

    flipImg = false;
    marioRun = false;
    accountForDisplacement = false;

    jumpVelocity=0.04;
    cmd = 2; //cmd = Command
    lives = 3;

    Singleton = this;
    playerAnimationTimer(1);
}

void Player::setCMD(int x, bool flip)
{
    cmd = x;
    if(flip)
        flipImg=true;
    else
        flipImg=false;
}


void Player::drawMario() const{
    if(cmd == 1)//Run animation
    {
        MRun->draw();
    }
    else if (cmd == 2)//Jump animation
    {
        MJump->draw();
    }
    else //Standing still animation
    {
        MStay->draw();
    }
}

void Player::updateMarioPosition()
{
    MStay->setY(this->y-0.035);
    MJump->setY(this->y-0.035);
    MRun ->setY(this->y-0.035);

    if(flipImg)
    {
        MRun->setW(abs(MRun->getW())*-1);
        MJump->setW(abs(MJump->getW())*-1);
        MStay->setW(abs(MStay->getW())*-1);

        MRun ->setX(this->x-0.02+0.12);
        MJump->setX(this->x-0.02+0.12);
        MStay->setX(this->x-0.02+0.12);
        accountForDisplacement = true;
        return;
    }

    if (accountForDisplacement)
    {
        MRun->setW(abs(MRun->getW()));
        MJump->setW(abs(MJump->getW()));
        MStay->setW(abs(MStay->getW()));

        MRun ->setX(this->x-0.02-0.12);
        MJump->setX(this->x-0.02-0.12);
        MStay->setX(this->x-0.02-0.12);
        accountForDisplacement = false;
    }
    
    else
    {
        MStay->setX(this->x-0.02);
        MRun ->setX(this->x-0.02);
        MJump->setX(this->x-0.02);
    }
}

void Player::animation()
{
    if(cmd == 1) // 1= Run animation
    {
        MRun->advance();
        if(MRun->isDone())
            MRun->reset();
    }
    glutPostRedisplay();   
}


float Player::getJumpVelocity()
{
    return jumpVelocity;
}

void Player::setJumpVelocity(float g, bool fall)
{
    if(fall == true)
        jumpVelocity = 0;
    jumpVelocity = jumpVelocity + g;
}

void Player::resetVelocity()
{
    jumpVelocity = 0.04;
}


int Player::getLives() const
{
    return lives;
}

void Player::death()
{
    lives--;
}

void Player::reset(bool resetLives){
    if(resetLives)
        lives = 3;
    this->x = -0.5;
	this->y = -0.5;
}


Player::~Player()
{
    delete MStay;
    delete MRun;
    delete MJump;
}