#ifndef enemies_h
#define enemies_h
#include "Rect.h"
#include "Sprite.h"
#include "TexRect.h"
#include <vector>
#include <algorithm>

class enemies: public Rect {
TexRect* ripGoomba;
std::vector<Rect*> mapOb;

bool dead;
bool directionR;
int count;

public:
    std::vector<Sprite*> enemyAnimation;
    enemies();
    void draw() const;

    void updateX(bool death = false);
    void helperUpdate(std::vector<Rect*> mapOb, int movingMap=0);
    void enemyState();

    bool collision(float x, float y, float w, float h, int collisionSide);
 
    void death(float x=0, float y=0, float w=0, float h=0);
    void reset(bool newGame=false);

    bool collided(float x, float y);

    friend void timers(int id);
};


#endif