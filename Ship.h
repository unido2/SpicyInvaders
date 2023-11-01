#pragma once

#include<qimage.h>
#include<qrect.h>
#include<qpoint.h>
#include"GlobalVar.h"


class Ship {

public:
	Ship();

	void reset();
	void move();
	void setdX(int);
	void returnToBorders();
	
	QImage& getImage();
	QRect getRect();

	int getShipyXLeft();
	int getShipyTop() { return shipy.top(); }

protected:
	

private:
	QImage img;
	int dx;
	QRect shipy;

	//ship image is 40x26
	const int INIT_X = GlobalVar::WIDTH_W / 2;
	const int INIT_Y = GlobalVar::HEIGHT_W-30;
};