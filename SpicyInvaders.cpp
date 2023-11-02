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

    timerMain = timer2=-1;
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
        startTimerEasy(timerMain, DELAY);
        qDebug() << "timerMain" << timerMain;

    }
}

void SpicyInvaders::pause()
{
    if (game_paused) {
        game_paused = false;
        stopTimerEasy(timer2);
        startTimerEasy(timerMain, DELAY);
    }
    else {
        game_paused = true;
        startTimerEasy(timer2, DELAY1);
        stopTimerEasy(timerMain);
    }
}

void SpicyInvaders::stop()
{
    stopTimerEasy(timerMain);
    game_over = true;
    game_started = false;
}

void SpicyInvaders::win()
{
    stopTimerEasy(timerMain);
    game_won = true;
    game_started = false;
}



void SpicyInvaders::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    if (game_over)
        drawMessageScreen(&painter, "Game over");
    else
        if (game_won)
            drawMessageScreen(&painter, "Incredible win");
        else
            drawMainGame(&painter);

}

void SpicyInvaders::timerEvent(QTimerEvent*event)
{
    //MainTimer events
    if (event->timerId() == timerMain) {
        setStyleSheet("background-color:black;");
        moveObj();
        checkCollision();
    }

    //Events for pause()
    if (event->timerId() == timer2) {
        setStyleSheet("background-color:yellow;");

#ifndef NODEBUG
        qDebug() << "timer 2 work";
#endif // !NODEBUG

    }
    repaint();

}

void SpicyInvaders::keyPressEvent(QKeyEvent* event)
{
    //reset counter and Reborn destroyed bullets
    if (b_counter == NUMB_BULLETS) { 
        b_counter = 0;
        for (int i = 0; i < NUMB_BULLETS; i++) {
            if(bullet[i]->isDestroyed())
                bullet[i]->setDestroyed(false);
        }
    }

    int step = 1; //increment for moving bullets and ship

    //press key events
    switch (event->key()) {
    case Qt::Key_Left:
        ship->setdX(-step);
        if (!bullet[0]->isActivated()) {
           bullet[0]->getActualShipX(ship->getRect().x());
           bullet[0]->setdX(-step);
        }
        break;
    case Qt::Key_Right:
        ship->setdX(step);
        if (!bullet[0]->isActivated()) {
            bullet[0]->getActualShipX(ship->getRect().x());
            bullet[0]->setdX(step);
        }
        break;
    case Qt::Key_Escape:
        pause();
        break;
    case Qt::Key_Space:
        start();
        break;
    case Qt::Key_Control:

        if (b_counter < NUMB_BULLETS) {
            if (!bullet[b_counter]->isActivated()) {
                bullet[b_counter]->setActivated(true);
                bullet[b_counter]->getActualShipX(ship->getRect().x()); //
                bullet[b_counter]->getActualShipY(ship->getRect().y()); //

            }

            bullet[b_counter]->setdY(step);
            b_counter++;
        }
#ifndef NODEBUG
            qDebug() << "bullet: " << b_counter;
#endif // !NODEBUG
        
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
        bullet[0]->setdX(-step);
        break;
    case Qt::Key_Right:
        ship->setdX(step);
        bullet[0]->setdX(step);
        break;
    }
    
}

//draw messages, need for pause(), game_end(), start_screen() etc
void SpicyInvaders::drawMessageScreen(QPainter* painter, QString msg)
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

void SpicyInvaders::drawMainGame(QPainter* painter)
{
    //draw bullets
    for (int i = 0; i < NUMB_BULLETS; i++) {
        if (bullet[i]->isActivated())
            painter->drawImage(bullet[i]->getRect(), bullet[i]->getImage());
    }
    
    //draw ship
    painter->drawImage(ship->getRect(), ship->getImage());

    //draw spicy invaders
    for (int i = 0; i < NUMB_INVADER; i++)
        if (!invaders[i]->isDestroyed())
            painter->drawImage(invaders[i]->getRect(), invaders[i]->getImage());
    
    if (game_paused) {
        drawMessageScreen(painter, "pause");
    }

}

void SpicyInvaders::moveObj()
{
    static int c = 0;
    ship->move();

    for (int i = 0; i < NUMB_BULLETS; i++)
        if(bullet[i]->isActivated())
            bullet[i]->shoot();

}



void SpicyInvaders::checkCollision()
{
    if (game_started) {
        for (int i = 0; i < NUMB_BULLETS; i++) {

            ///check collision with invaders
            for (int j = 0; j < NUMB_INVADER; j++) {
                if (!invaders[j]->isDestroyed()) {
                    if (bullet[i]->getRect().intersects(invaders[j]->getRect())) {
                        invaders[j]->setDestroyed(true);
                        bullet[i]->setDestroyed(true);
                        bullet[i]->setActivated(false);
                        bullet[i]->reset();
                        break;
                    }
                }
                    if (bullet[i]->getRect().y() < TOP_BORDER) {
                        bullet[i]->setDestroyed(true);
                        bullet[i]->setActivated(false);
                        bullet[i]->reset();
                    }
                
            }
        }


        //check ship collision with left, right border 
        if (ship->getRect().x() < 1 || ship->getRect().right() > GlobalVar::WIDTH_W-1) {
            //qDebug() << "border";
            ship->returnToBorders();
        }
    }
}

//methods for comfort timerEvent work

void SpicyInvaders::startTimerEasy(int& timerid, int delay)
{
    if (timerid == -1)
        timerid = startTimer(delay);
    qDebug() << "timerid" << timerid;
}

void SpicyInvaders::stopTimerEasy(int& timerid)
{
    if (timerid != -1)
        killTimer(timerid);
    timerid = -1;
}
