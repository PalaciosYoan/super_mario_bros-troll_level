#pragma once

#include "TexRect.h"

class Sprite: public TexRect{
	int rows;
	int cols;

	float xinc;
	float yinc;

	int curr_row;
	int curr_col;

	float left;
	float right;
	float top;
	float bottom;

	bool done;

public:
	Sprite(const char* filename, int rows, int cols, float x, float y, float w, float h): TexRect(filename, x, y, w, h){
		this->rows = rows;
		this->cols = cols;

		xinc = 1.0 / cols;
		yinc = 1.0 / rows;

		curr_row = 1;
		curr_col = 1;

		left = xinc * (curr_col - 1);
		right = xinc * curr_col;
		top = 1 - yinc * (curr_row - 1);
		bottom = 1 - yinc * curr_row;

		done = false;

	}
	void draw(float z = 0);
	
	bool isDone () const;

	void reset();

	void advance();

	~Sprite();
};
