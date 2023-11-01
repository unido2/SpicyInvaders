#include<iostream>
#include<qapplication.h>
#include<qpainter.h>

#include "SpicyInvaders.h"

#define NODEBUG


int SpicyInvaders::b_counter = 0;

SpicyInvaders::SpicyInvaders(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:black;");
    resize(GlobalVar::WIDTH_W, GlobalVar::HEIGHT_W);

    timerMain = NULL;
    game_over = false;
    game_won = false;
    game_paused = false;
    game_started = false;
    
    ship = new Ship();
    
    for (int i = 0; i < NUMB_BULLETS; i++)
         bullet[i] = new Bullet();

    int count_inv = 0;
    for (int row = 0; row < N_ROW_INVADERS; row++)
        for (int col = 0; col < N_COL_INVADERS; col++)
            invaders[count_inv++] = new Invader(TOP_BORDER + col * W_H_INVADER, TOP_BORDER + row * W_H_INVADER);

}

SpicyInvaders::~SpicyInvaders()
{
    delete ship;
    
    for (int count = 0; count < NUMB_BULLETS; count++)
        delete bullet[count];

    for (int count = 0; count < NUMB_INVADER; count++)
        delete invaders[count];

}

void SpicyInvaders::start()
{
    if (!game_started) {

        ship->reset();

        for (int i = 0; i < NUMB_BULLETS; i++) {
            bullet[i]->reset();
            bullet[i]->setActivated(false);
            bullet[i]->setDestroyed(false);
        }

        for (int i = 0; i < NUMB_INVADER; i++) {
            invaders[i]->setDestroyed(false);
        }

        game_over = false;
        game_won = false;
        game_started = true;
        timerMain = startTimer(DELAY);
    }
}

void SpicyInvaders::pause()
{
    if (game_paused) {
        game_paused = false;
        timerMain = startTimer(DELAY);
    }
    else {
        game_paused = true;
        killTimer(timerMain);
    }
}

void SpicyInvaders::stop()
{
    killTimer(timerMain);
    game_over = true;
    game_started = false;
}

void SpicyInvaders::win()
{
    killTimer(timerMain);
    game_won = true;
    game_started = false;
}



void SpicyInvaders::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    if (game_over)
        gameEnd(&painter, "Game over");
    else
        if (game_won)
            gameEnd(&painter, "Incredible win");
        else
            draw(&painter);

}

void SpicyInvaders::timerEvent(QTimerEvent*e)
{
    Q_UNUSED(e);

    moveObj();
    checkCollision();
    repaint();

}

void SpicyInvaders::keyPressEvent(QKeyEvent* event)
{
    int step = 1;

    switch (event->key()) {
    case Qt::Key_Left:
        ship->setdX(-step);
        break;
    case Qt::Key_Right:
        ship->setdX(step);
        break;
    case Qt::Key_Escape:
        pause();
        break;
    case Qt::Key_W:
        start();
        break;
    case Qt::Key_Space:

        //if (b_counter < NUMB_BULLETS) {
        if (!bullet[0]->isActivated()) {
            bullet[0]->setActivated(true);
            bullet[0]->setXShip(ship->getRect().x());

        }
        //timerBullet[0]->setInterval(5);
         bullet[0]->setdY(step);
#ifndef NODEBUG
            qDebug() << b_counter;
            for (int i = 0; i < NUMB_BULLETS; i++)
                if (bullet[i]->isActivated())
                    qDebug() << "bullet" << i;
#endif // !NODEBUG
           // b_counter++;
        
        /*
        else {
            b_counter = 0;
        }
        */
        break;

    default:QWidget::keyPressEvent(event);
    }
}

void SpicyInvaders::keyReleaseEvent(QKeyEvent* event)
{
    
    int step = 0;

    switch (event->key()) {
    case Qt::Key_Left:
        ship->setdX(step);
        break;
    case Qt::Key_Right:
        ship->setdX(step);
        break;
       /*
    case Qt::Key_Space:
        for(int i=0;i<NUMB_BULLETS;i++)
            if(!bullet[i]->isActivated())
                bullet[b_counter]->setActivated(false);      
        break;
        
      */  
    }
    
}



void SpicyInvaders::gameEnd(QPainter* painter, QString msg)
{
    QFont font("Monospace", 12);
    QFontMetrics fm(font);
    int t_width = fm.horizontalAdvance(msg);

    painter->setFont(font);
    int w = width();
    int h = height();

    painter->translate(QPoint(w / 2, h / 2));
    painter->drawText(-t_width / 2, 0, msg);

}

void SpicyInvaders::draw(QPainter* painter)
{
    painter->drawImage(ship->getRect(), ship->getImage());

   // for (int i = 0; i < NUMB_BULLETS; i++) {
     //   if (bullet[i]->isActivated())
            painter->drawImage(bullet[0]->getRect(), bullet[0]->getImage());
    //}

    for (int i = 0; i < NUMB_INVADER; i++)
        if (!invaders[i]->isDestroyed())
            painter->drawImage(invaders[i]->getRect(), invaders[i]->getImage());

}

void SpicyInvaders::moveObj()
{
    static int c = 0;
    ship->move();

    //for (int i = 0; i < NUMB_BULLETS; i++)
      //  if(bullet[i]->isActivated())
            bullet[0]->shoot();

}



void SpicyInvaders::checkCollision()
{
    if (game_started) {
        for (int i = 0; i < NUMB_BULLETS; i++) {

            for (int j = 0; j < NUMB_INVADER; j++) {
                if (!invaders[j]->isDestroyed()) {
                    if (bullet[i]->getRect().intersects(invaders[j]->getRect())) {
                        invaders[j]->setDestroyed(true);
                        //bullet[i]->setDestroyed(true);
                        bullet[i]->setActivated(false);
                        bullet[i]->reset();
                        break;
                    }
                }
                    if (bullet[i]->getRect().y() < TOP_BORDER) {
                        bullet[i]->setDestroyed(true);
                        bullet[i]->setActivated(false);
                    }
                
            }
        }
        if (ship->getRect().x() < 1 || ship->getRect().right() > GlobalVar::WIDTH_W-1) {
            qDebug() << "border";
            ship->returnToBorders();
        }
    }
}
