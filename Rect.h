#ifndef RECT_H
#define RECT_H

#include "Shape.h"

class Rect: public Shape{
protected:
	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float b;

public:
	Rect();
	Rect(float x, float y, float w, float h, float r=0, float g=1, float b=0);

	void draw(float z=0) const;

	void setY(float y);
	float getY() const;
	float getX() const;
	void setX(float x);
	float getH() const;
	float getW() const;
	void setW(float w);


	bool contains(float x, float y, bool moving=false) const;
};

#endif
