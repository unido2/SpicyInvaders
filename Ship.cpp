#include<qdebug.h>
#include "Ship.h"

Ship::Ship()
{
    dx = 0;
    img.load("D:\\my_project\\qt\\SpicyInvaders\\img\\ship.png");
    if (img.isNull())
        exit(1);
    shipy = img.rect();

    reset();
}

void Ship::reset()
{
    shipy.moveTo(INIT_X, INIT_Y);

}

void Ship::move()
{
    int x = shipy.x() + dx;

    int y = shipy.top();
    shipy.moveTo(x, y);

    //qDebug() << "Shipy x: " << shipy.x();
}

void Ship::setdX(int xx)
{
    dx = xx;
}

void Ship::returnToBorders()
{
    int x_left = shipy.x();

    if (x_left < 1)
        shipy.moveTo(2,shipy.top());
    if (x_left > (GlobalVar::WIDTH_W-shipy.width())-1)
        shipy.moveTo(GlobalVar::WIDTH_W-shipy.width()-2,shipy.top());
}

QImage& Ship::getImage()
{
    return img;
    
}

QRect Ship::getRect()
{
    return shipy;
}

int Ship::getShipyXLeft() { 
    
    return shipy.x(); 
}

