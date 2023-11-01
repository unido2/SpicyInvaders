#include "Invader.h"

Invader::Invader(int x, int y)
{
    destroyed = false;
    img.load("D:\\my_project\\qt\\SpicyInvaders\\img\\invader.png");

    rect = img.rect();
    rect.translate(x, y);
}

bool Invader::isDestroyed()
{
    return destroyed;
}

void Invader::setDestroyed(bool choise)
{
    destroyed = choise;
}

void Invader::setVader(QRect r)
{
    rect = r;
}

QRect Invader::getRect()
{
    return rect;
}

QImage& Invader::getImage()
{
    return img;
}
