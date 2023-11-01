#include<iostream>
#include<qdebug.h>

#include "Bullet.h"

int Bullet::number_of_bullet=0;

Bullet::Bullet()
{
    activated = destroyed = false;
    dy = 0;
    x_ship = 0;

    img.load("D:\\my_project\\qt\\SpicyInvaders\\img\\bullet.png");
    if (img.isNull())
        exit(1);

    bully = img.rect();

    reset();

    ++number_of_bullet;
    std::cout << "bulet born: " << number_of_bullet << std::endl;
}

Bullet::~Bullet()
{
    --number_of_bullet;
    if (number_of_bullet == 0)
        std::cout << "all bullet terminated" << std::endl;
}

void Bullet::reset()
{
    bully.moveTo(INIT_X, INIT_Y);
}

void Bullet::shoot()
{
    if (activated) {

        int x = x_ship + (GlobalVar::SHIP_WIDTH / 2) - 5;
        int y = bully.y() - dy;

        qDebug() << "x: " <<x<< " y: " << y;

        bully.moveTo(x, y);
    }
}

void Bullet::setdY(int yy)
{
    dy = yy;
}

void Bullet::bornNewBullet()
{
    
}

QImage& Bullet::getImage()
{
    return img;
}

QRect Bullet::getRect()
{
    return bully;
}

int Bullet::getdY()
{
    return dy;
}

int Bullet::getBulletNumber()
{
    return number_of_bullet;
}

bool Bullet::isActivated()
{
    return activated;
}

bool Bullet::isDestroyed()
{
    return destroyed;
}

void Bullet::setActivated(bool choice)
{
    activated = choice;
}

void Bullet::setDestroyed(bool choice)
{
    destroyed = choice;
}

void Bullet::setXShip(int x)
{
    x_ship = x;
}
