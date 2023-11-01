#pragma once

#include<qimage.h>
#include<qrect.h>

class Invader {

public:
	Invader(int,int);

	bool isDestroyed();

	void setDestroyed(bool);
	void setVader(QRect);

	QRect getRect();
	QImage& getImage();

private:
	QImage img;
	QRect rect;
	bool destroyed;

};