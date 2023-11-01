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
	void setdY(int);
	void bornNewBullet();
	

	QImage& getImage();
	QRect getRect();
	int getdY();
	int getBulletNumber();

	bool isActivated();
	bool isDestroyed();

	void setActivated(bool);
	void setDestroyed(bool);
	void setXShip(int);
	

private:
	QImage img;
	QRect bully;

	bool activated;
	bool destroyed;
	int dy;
	int x_ship;


	//ship image is 40x26
	//bullet size 10x10
	static int number_of_bullet;

	const int INIT_X = (GlobalVar::WIDTH_W / 2)+(GlobalVar::SHIP_WIDTH / 2) - 5;
	const int INIT_Y = GlobalVar::HEIGHT_W - (26+10);
};