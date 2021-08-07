#include "game.h"
#include "GlutApp.h"
#include <iostream>

static game* gamestate;

int count =0;
void GameLoop(int id)
{
    if(!gamestate->getPause())
    {
        gamestate->playerState();
        gamestate->animation();
        gamestate->enemyAnimation();
    }
    glutTimerFunc(10,GameLoop, id);
}

void coinAnimation(int id)
{
    for(auto i =gamestate->coins.begin(); i != gamestate->coins.end(); i++)
    {
        (*i)->advance();
        glutPostRedisplay();
        if((*i)->isDone())
            (*i)->reset();
    }
    if(gamestate->coinExplosion)
        for(auto i =gamestate->explosion.begin(); i != gamestate->explosion.end(); i++)
        {
            (*i)->advance();
            glutPostRedisplay();
            if((*i)->isDone())
                gamestate->coinAni=false;
        }
    glutPostRedisplay();
    glutTimerFunc(125,coinAnimation, id);
}
void explisionAnimation(int id)
{
    if(gamestate->Mdeath)
    {
        gamestate->explo->advance();
        glutPostRedisplay();
        if(gamestate->explo->isDone())
        {
            gamestate->explo->reset();
            gamestate->Mdeath = false;
            gamestate->gameReset();
        }
    }
    glutPostRedisplay();
    glutTimerFunc(125,explisionAnimation, id);
}
void keyInput(int id)
{
    gamestate->playerMovement();
    glutTimerFunc(10,keyInput, id);
}

game::game(){
    //Lives animation
    lives.push_back(new TexRect("images/1Lives.png", -0.95, 0.95, 0.08, 0.1));
    lives.push_back(new TexRect("images/2Lives.png", -0.95, 0.95, 0.16, 0.1 ));
    lives.push_back(new TexRect("images/3Lives.png", -0.95, 0.95, 0.24, 0.1 ));

    //GG Screen
    gg = new TexRect("images/gg.png", -0.5, 0.5, 1, 1.5);
    //Won animation
    wonAni = new TexRect("images/won.png", -0.5, 0.5, 1, 1.5);

    //Setting up the map
    mapOb.push_back(new Rect(-1, -0.76, 0.67, .065, 0, 0, 0));//0 Start up platform

    mapOb.push_back(new Rect(-0.13, -0.66, 0.18, 0.06, 0, 0, 0));//1
    mapOb.push_back(new Rect(0.13, -0.228, 0.36, .06, 0, 0, 0)); //2
    mapOb.push_back(new Rect(0.24, 0.31, 0.21, .06, 0, 0, 0));//3

    mapOb.push_back(new Rect(0.52, -0.65, 0.14, .06, 0, 0, 0));//4
    mapOb.push_back(new Rect(0.665, -0.095, 0.21, .06, 0, 0, 0));//5

    mapOb.push_back(new Rect(0.92, 0.45, 0.29, .08, 0, 0, 0));//6
    mapOb.push_back(new Rect(1.4, -0.8, 0.125, .08, 0, 0, 0));//7
    mapOb.push_back(new Rect(1.8, -0.793, 0.22, .05, 0, 0, 0));//8

    mapOb.push_back(new Rect(2.09, -0.793, 0.22, .05, 0, 0, 0));//9
    mapOb.push_back(new Rect(1.85, 0.32, 0.16, .06, 0, 0, 0));//10
    mapOb.push_back(new Rect(2.32, -0.235, 0.12, .06, 0, 0, 0));//11

    mapOb.push_back(new Rect(2.62, 0.18, 0.25, .06, 0, 0, 0)); // 12
    mapOb.push_back(new Rect(3.05, 0.32, 0.09, .06, 0, 0, 0)); // 13

    mapOb.push_back(new Rect(3.6, 0.45, 0.09, .06, 0, 0, 0)); //14
    mapOb.push_back(new Rect(3.93, 0.04, 0.33, .06, 0, 0, 0)); // 15
    mapOb.push_back(new Rect(4.49, -0.24, 0.18, .06, 0, 0, 0)); //16

    mapOb.push_back(new Rect(4.77, -0.24, 0.18, .06, 0, 0, 0)); //17
    mapOb.push_back(new Rect(5.1, -0.76, 0.42, .06, 0, 0, 0)); //18
    mapOb.push_back(new Rect(5.8, -0.76, 1.5, .06, 0, 0, 0)); //19

    mapOb.push_back(new Rect(6.2, -0.76, 0.03, -.5, 0, 0, 1)); //20


    //adding map textures
    mapTex = new TexRect("images/Map12.png", -1, 1, 8, 2);
    
    //Explosion Animation for my Player
    explo = new Sprite("images/Explosion.png", 4, 3, 3.08,0.457, 0.13, 0.19);

    //Adding coin animation
    coins.push_back(new Sprite("images/coin.png", 1, 6, -0.2,-0.5, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.08,0.457, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.44,0.587, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.63,0.587, 0.04, 0.14));

    //preparing to Explosions for coins
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, -0.2,-0.5, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.08,0.457, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.44,0.587, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.63,0.587, 0.04, 0.14));

    gravity = -0.00138;
    ground = 1;
    roof = 2;
    left = 3;
    right = 4;

    hasJump = false;
    isRun = false;
    onGround = false;
    faceJumpDir = false;
    lastPressedA = false;
    coinExplosion = false;
    coinAni = true;
    pause = true;
    Mdeath = false;
    hasWon =false;

    gamestate = this;

    GameLoop(1);
    coinAnimation(2);
    explisionAnimation(3);
    keyInput(4);

    for(int i =0; i<256; i++)
        keyStates[i]=false;

}
void game::draw() const{
    playerOne.draw();

    //drawing maps platform
    for(auto i = mapOb.begin(); i != mapOb.end(); i++)
        (*i)->draw();

    mapTex->draw();
    if(hasWon)
    {
        wonAni->draw();
        return;
    }
    //exploding coins?
    if (coinExplosion && coinAni)
        for(auto i = explosion.begin(); i != explosion.end(); i++)
            (*i)->draw();
    else if (coinAni) //animation of coins continue?
        for(auto i = coins.begin(); i != coins.end(); i++)
            (*i)->draw();
    
    //did mario die?
    if(Mdeath)
        explo->draw();
    else if(playerOne.getLives() >0)
        playerOne.drawMario();
    
    enemy.draw();

    if(playerOne.getLives()==3)
        lives[2]->draw();
    else if(playerOne.getLives()==2)
        lives[1]->draw();
    else if(playerOne.getLives()==1)
        lives[0]->draw();
    else
    {
        gg->draw();
    }
    
}


void game::keyPressed(unsigned char  key)
{
    keyStates[key]=true;
    if(keyStates[' '])
    {
        setJump(true);
        onGround = false;
    }
}

void game::keyUp(unsigned char key)
{
    keyStates[key]=false;
}

bool game::collision(float x, float y, float w, float h, int collisionSide)
{
    //checks if object has collided with an platform
    for(auto i = mapOb.begin(); i != mapOb.end(); i++)
        if(
            collisionSide == ground &&
            ((*i)->contains(x, y-h) || 
            (*i)->contains(x+w, y-h))
        )
            {
                //if player has collided with platform 13 then explode the coins
                if((*i)->getX() == mapOb[13]->getX())
                    coinExplosion = true;
                return true;
            }
        else if(
            collisionSide == roof &&
            ((*i)->contains(x, y) || 
            (*i)->contains(x+w, y))
        )
            return true;
        else if(
            collisionSide == left &&
            ((*i)->contains(x, y) || 
            (!onGround && (*i)->contains(x, y-h)))
        )
            return true;
        else if(
            collisionSide == right &&
            ((!onGround&&(*i)->contains(x+w, y-h)) || 
            (*i)->contains(x+w, y))
        )
            return true;

    
    return false;
}


float game::getGravity() const
{
    return gravity;
}


void game::setJump(bool x)
{
    hasJump = x;
}

bool game::getJump()
{
    return hasJump;
}

void game::playerState()
{
    //if player has not jump and is touching ground then do nothing
    if( collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), ground) && !(getJump()))
        return;

    //Players walk off an object without jumping "player is at free fall" same affects if player hits the roof of an object
    if (collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), roof) || !(getJump()))
        playerOne.setJumpVelocity(-0.0118, true);
    
    //updates player's Y based on his velocity. Also, Update's the player's velocity based on gravity
    playerOne.setY(playerOne.getY()+playerOne.getJumpVelocity());
    playerOne.setJumpVelocity(getGravity());

    //see where to look while jumping
    if(keyStates['a'])
        faceJumpDir = true;
    else if(keyStates['d'])
        faceJumpDir = false;

    playerOne.setCMD(2,faceJumpDir);

    if(playerOne.getY() < -1)
    {
        gameReset();
    }

    // checks if collision with an object at Y-axis
    if(collision(playerOne.getX(), playerOne.getY()+playerOne.getJumpVelocity(), playerOne.getW(), playerOne.getH(), ground) && count == 1) 
    {
        playerOne.resetVelocity();
        count = 0;
        onGround = true;
        setJump(false);
        playerOne.setCMD(0, lastPressedA);
    }

    count = 1; //If zero means that were are touching the ground before jumping
    playerOne.updateMarioPosition(); // Updates player texture's location
    redraw();
}

void game::playerMovement()
{
    //mapOb.push_back(new Rect(6.2, -0.76, 0.03, -.5, 0, 0, 1)); //20
    if(playerOne.getX() >= mapOb[20]->getX())
        hasWon = true;
    //When moving right or left make sures that player's right side has not collided with an object
    if(keyStates['d'] && !(collision(playerOne.getX()+0.01, playerOne.getY(), playerOne.getW(), playerOne.getH(), right)))
    {
        //If player at edge of the map then don't move the map
        if((mapTex->getX()+mapTex->getW())-playerOne.getX()>=1.5 && playerOne.getX() >= -0.2 && playerOne.getX() <= 0.2)
        {
            enemy.helperUpdate(mapOb, 1);
            playerOne.setX(playerOne.getX()+0.0005); 
            mapTex->setX(mapTex->getX()-0.008);
            for(auto i = mapOb.begin(); i != mapOb.end(); i++){
                (*i)->setX((*i)->getX()-0.008);
            }
            for(auto i = coins.begin(); i != coins.end(); i++){
                (*i)->setX((*i)->getX()-0.008);
            }
            for(auto i = explosion.begin(); i != explosion.end(); i++){
                (*i)->setX((*i)->getX()-0.008);
            }
        }
        else
        {
            playerOne.setX(playerOne.getX()+0.008);
        }
    }

    else if(keyStates['a'] && !(collision(playerOne.getX()-0.01, playerOne.getY(), playerOne.getW(), playerOne.getH(), left))) 
    {
        //If player at edge of the map then don't move the map
        if(playerOne.getX()-mapTex->getX()>=.5 && playerOne.getX() >= -0.2 && playerOne.getX() <= 0.2)
        {
            enemy.helperUpdate(mapOb, 2);
            playerOne.setX(playerOne.getX()-0.0005);
            mapTex->setX(mapTex->getX()+0.008);
            for(auto i = mapOb.begin(); i != mapOb.end(); i++)
                (*i)->setX((*i)->getX()+0.008);
            for(auto i = coins.begin(); i != coins.end(); i++){
                (*i)->setX((*i)->getX()+0.008);
            }
            for(auto i = explosion.begin(); i != explosion.end(); i++){
                (*i)->setX((*i)->getX()+0.008);
            }
        }
        else
            playerOne.setX(playerOne.getX()-0.008);
        
    }
    
    playerOne.updateMarioPosition(); //Always update's player's textures position
    redraw();
}

void game::pauseGame()
{
    pause = !pause;
}

bool game::getPause()
{
    return pause;
}

void game::enemyAnimation()
{
    enemy.helperUpdate(mapOb);
}

void game::redraw(){
    glutPostRedisplay();
}

void game::animation()
{
    //if Player has jump on top of enemy then enemy has die
    if(
        (enemy.collided(playerOne.getX(), playerOne.getY()-playerOne.getH()) ||
        enemy.collided(playerOne.getX()+playerOne.getW(), playerOne.getY()-playerOne.getH())) &&
        !collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), ground)
    )
    {
        enemy.death(playerOne.getX(), playerOne.getY()-0.01, playerOne.getW(), playerOne.getH());
        Mdeath = false;
    }
    else if(
        enemy.collided(playerOne.getX(), playerOne.getY()-playerOne.getH()) ||
        enemy.collided(playerOne.getX()+playerOne.getW(), playerOne.getY()-playerOne.getH()) ||
        enemy.collided(playerOne.getX(), playerOne.getY()) ||
        enemy.collided(playerOne.getX()+playerOne.getW(), playerOne.getY())
    )
    {
        explo->setX(playerOne.getX());
        explo->setY(playerOne.getY());
        Mdeath = true;
    }

    //0 = standstill, 1 = Run, 2=Jump
    if(!keyStates['a'] && !keyStates['d'] && collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), ground))
        playerOne.setCMD(0, lastPressedA);
    
    if(keyStates['a'] && collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), ground))
    {
        playerOne.setCMD(1, true); //flip imagi
        lastPressedA = true;
    }
    if(keyStates['d'] && collision(playerOne.getX(), playerOne.getY(), playerOne.getW(), playerOne.getH(), ground))
    {
        playerOne.setCMD(1, false); //dont flip the imagi
        lastPressedA = false;
    }
}

void game::gameReset(bool restart)
{
    //Something happened resetting game
    mapOb.erase(mapOb.begin(), mapOb.end());
    coins.erase(coins.begin(), coins.end());
    explosion.erase(explosion.begin(), explosion.end());


    //Setting up the map
    mapOb.push_back(new Rect(-1, -0.76, 0.67, .065, 0, 0, 0));//0 Start up platform

    mapOb.push_back(new Rect(-0.13, -0.66, 0.18, 0.06, 0, 0, 0));//1
    mapOb.push_back(new Rect(0.13, -0.228, 0.36, .06, 0, 0, 0)); //2
    mapOb.push_back(new Rect(0.24, 0.31, 0.21, .06, 0, 0, 0));//3

    mapOb.push_back(new Rect(0.52, -0.65, 0.14, .06, 0, 0, 0));//4
    mapOb.push_back(new Rect(0.665, -0.095, 0.21, .06, 0, 0, 0));//5

    mapOb.push_back(new Rect(0.92, 0.45, 0.29, .08, 0, 0, 0));//6
    mapOb.push_back(new Rect(1.4, -0.8, 0.125, .08, 0, 0, 0));//7
    mapOb.push_back(new Rect(1.8, -0.793, 0.22, .05, 0, 0, 0));//8

    mapOb.push_back(new Rect(2.09, -0.793, 0.22, .05, 0, 0, 0));//9
    mapOb.push_back(new Rect(1.85, 0.32, 0.16, .06, 0, 0, 0));//10
    mapOb.push_back(new Rect(2.32, -0.235, 0.12, .06, 0, 0, 0));//11

    mapOb.push_back(new Rect(2.62, 0.18, 0.25, .06, 0, 0, 0)); // 12
    mapOb.push_back(new Rect(3.05, 0.32, 0.09, .06, 0, 0, 0)); // 13

    mapOb.push_back(new Rect(3.6, 0.45, 0.09, .06, 0, 0, 0)); //14
    mapOb.push_back(new Rect(3.93, 0.04, 0.33, .06, 0, 0, 0)); // 15
    mapOb.push_back(new Rect(4.49, -0.24, 0.18, .06, 0, 0, 0)); //16

    mapOb.push_back(new Rect(4.77, -0.24, 0.18, .06, 0, 0, 0)); //17
    mapOb.push_back(new Rect(5.1, -0.76, 0.42, .06, 0, 0, 0)); //18
    mapOb.push_back(new Rect(5.8, -0.76, 1.5, .06, 0, 0, 0)); //19

    mapOb.push_back(new Rect(6.2, -0.76, 0.03, -.5, 0, 0, 1)); //20


    //adding map textures
    mapTex = new TexRect("images/Map12.png", -1, 1, 8, 2);


    //Adding coin animation
    coins.push_back(new Sprite("images/coin.png", 1, 6, -0.2,-0.5, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.08,0.457, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.44,0.587, 0.04, 0.14));
    coins.push_back(new Sprite("images/coin.png", 1, 6, 3.63,0.587, 0.04, 0.14));

    //preparing to Explosions for coins
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, -0.2,-0.5, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.08,0.457, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.44,0.587, 0.04, 0.14));
    explosion.push_back(new Sprite("images/Explosion.png", 4, 3, 3.63,0.587, 0.04, 0.14));
    hasWon = false;
    coinExplosion = false;
    coinAni = true;
    playerOne.death();
    if(playerOne.getLives() >=1)
        playerOne.reset(); 
    enemy.reset();

    if(restart)
        playerOne.reset(true);
}

game::~game(){
    for(auto i = mapOb.begin(); i != mapOb.end(); i++){
        delete *i;
    }
    for(auto i = coins.begin(); i != coins.end(); i++){
        delete *i;
    }
    for(auto i = explosion.begin(); i != explosion.end(); i++){
        delete *i;
    }
    // delete keyStates;


    // delete explo;
    // delete mapTex;
}