#include "enemies.h"
static enemies* e;

void enemyAnimationTimer(int id)
{
    for(auto i =e->enemyAnimation.begin(); i != e->enemyAnimation.end(); i++)
    {
        (*i)->advance();
        glutPostRedisplay();
        if((*i)->isDone())
            (*i)->reset();
    }
    e->updateX();
    e->enemyState();
    glutTimerFunc(75,enemyAnimationTimer, id);
}


enemies::enemies()
{

    ripGoomba = new TexRect("images/Deadgoomba.png", -0.5, 0.5, 0.13, 0.12);
    enemyAnimation.push_back(new Sprite("images/Alivegoomba.png", 1, 2, 0, -0.1, 0.15, 0.12));
    enemyAnimation.push_back(new Sprite("images/Alivegoomba.png", 1, 2, 5.15,-0.62,0.15, 0.12));

    dead = false;
    directionR = true;
    count = 0;

    e=this;
    enemyAnimationTimer(5);
}

void enemies::draw() const
{
    if(dead)
        ripGoomba->draw();
    
    else if (!dead)
        for(auto i=enemyAnimation.begin(); i!=enemyAnimation.end();i++)
            (*i)->draw();   
}

void enemies::updateX(bool death)
{
    //count is to let time pass so my program can do the death animation of enemy
    if(dead && count == 3)
    {
        dead = false;
    }
    else if(dead)
        count++;
    
    //Automation for all enemies on the map...
    for(auto i=enemyAnimation.begin(); i!=enemyAnimation.end();i++)
    {
        if(directionR)
            (*i)->setX((*i)->getX()+0.016);
        else 
            (*i)->setX((*i)->getX()-0.016);
    }
}

void enemies::helperUpdate(std::vector<Rect*> mapOb, int movingMap)
{
    //1 = moving enemy left, 2= moving enemy right
    //Taking into account if the whole map moves to update enemies new location
    if(this->mapOb.empty())
        this->mapOb = mapOb;
    if(movingMap == 1)
    {
        for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
        {
            (*i)->setX((*i)->getX()-0.008);
        }
    }
    else if(movingMap == 2)
    {
        for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
        {
            (*i)->setX((*i)->getX()+0.008);
        }
    }


    for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
    {
        for(int j = 0; j<mapOb.size(); j++)
        {
            if(
                mapOb[j]->contains((*i)->getX()+(*i)->getW(), (*i)->getY()-(*i)->getH()) ||
                mapOb[j]->contains((*i)->getX(), (*i)->getY()-(*i)->getH())
            )
            {
                //if edge of the platform then go to the other side
                if((*i)->getX() <= mapOb[j]->getX())
                    directionR=true;
                else if((*i)->getX()+(*i)->getW() >= mapOb[j]->getX()+mapOb[j]->getW())
                    directionR=false;
            }
        }
    }
}

void enemies::enemyState()
{
    if(!this->mapOb.empty())
        for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
        {
            for(int j = 0; j<mapOb.size(); j++)
            {
                if(
                    mapOb[j]->contains((*i)->getX()+(*i)->getW(), (*i)->getY()-(*i)->getH()) ||
                    mapOb[j]->contains((*i)->getX(), (*i)->getY()-(*i)->getH())
                )
                {
                    break;
                }
                else if ((*i)->getX() >= mapOb[j]->getX() && (*i)->getX() < mapOb[j]->getX()+mapOb[j]->getW())
                {
                    (*i)->setY((*i)->getY()-0.012);
                }
            }
        }
}

bool enemies::collision(float x, float y, float w, float h, int collisionSide)
{
    // ground = 1;
    // roof = 2;
    // left = 3;
    // right = 4;
    for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
        if(
            collisionSide == 1 &&
            ((*i)->contains(x, y-h) || 
            (*i)->contains(x+w, y-h))
        )
            {
                return true;
            }       
        else if(
            collisionSide == 3 &&
            ((*i)->contains(x, y)||
            (*i)->contains(x, y-h))
        )
            return true;
        else if(
            collisionSide == 4 &&
            ((*i)->contains(x+w, y)||
            (*i)->contains(x+w, y-h))
        )
            return true;
    return false;
}

void enemies::death(float x, float y, float w, float h)
{
    int count = 0;

    int location;
    for(int i = 0; i<enemyAnimation.size(); i++)
    {
        location = i+1;
        if(enemyAnimation[i]->contains(x, y-h) || enemyAnimation[i]->contains(x+w, y-h))
        {
            ripGoomba->setX(enemyAnimation[i]->getX());
            ripGoomba->setY(enemyAnimation[i]->getY());
            enemyAnimation.erase(enemyAnimation.begin()+location-1, enemyAnimation.begin()+location);
            break;
        }
    }
    dead = true;
}
bool enemies::collided(float x, float y)
{
    for(auto i = enemyAnimation.begin(); i != enemyAnimation.end(); i++)
        if(x >= (*i)->getX() && x <= (*i)->getX()+(*i)->getW() && y <= (*i)->getY()+0.05 && y >= (*i)->getY()-(*i)->getH())
            return true;
    return false;
}
void enemies::reset(bool newGame)
{
    enemyAnimation.erase(enemyAnimation.begin(), enemyAnimation.end());
    mapOb.erase(mapOb.begin(),mapOb.end());

    enemyAnimation.push_back(new Sprite("images/Alivegoomba.png", 1, 2, 0.1, -0.1, 0.15, 0.12));
    enemyAnimation.push_back(new Sprite("images/Alivegoomba.png", 1, 2, 5.15,-0.62,0.15, 0.12));
}