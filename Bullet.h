#pragma once

#include<qimage.h>
#include<qrect.h>
#include<qpoint.h>
#include"GlobalVar.h"

#include"Ship.h"

class Bullet :public Ship {

public:
	Bullet();
	~Bullet();

	void reset();
	void shoot();
	void bornNewBullet();
	

	QImage& getImage();
	QRect getRect();
	int getdY();
	int getBulletNumber();

	bool isActivated();
	bool isDestroyed();

	void setdY(int);
	void setdX(int);
	void setActivated(bool);
	void setDestroyed(bool);

	void getActualShipX(int); //get actual X Ship coordinate to leap
	void getActualShipY(int); //get actual Y Ship coordinate to leap


private:
	QImage img;
	QRect bully;

	bool activated;
	bool destroyed;
	int dy; // increment to move bullet Y axis
	int dx; // increment to leap and move bullet to X axis of Ship
	int x_act_ship; //actual X coordinate of Ship
	int y_act_ship; //actual Y coordinate of Ship

	//ship image is 40x26
	//bullet size 10x10
	static int number_of_bullet;

	const int INIT_X = (GlobalVar::WIDTH_W / 2)+(GlobalVar::SHIP_WIDTH / 2) - 5;
	const int INIT_Y = GlobalVar::HEIGHT_W - (26+10);
};