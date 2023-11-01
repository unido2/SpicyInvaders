#pragma once

#include <qwidget.h>
#include <QKeyEvent>
#include<qtimer.h>
#include"Bullet.h"
#include"Ship.h"
#include"Invader.h"

#define N_ROW_INVADERS 6
#define N_COL_INVADERS 14

class SpicyInvaders : public QWidget
{
    Q_OBJECT

public:
    SpicyInvaders(QWidget* parent = nullptr);
    ~SpicyInvaders();

protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

    void draw(QPainter*);
    void gameEnd(QPainter*, QString);
    void moveObj();

    void start();
    void pause();
    void stop();
    void win();
    void checkCollision();

private:
    //int x;

    static int b_counter;

    static const int TOP_BORDER = 10;
    static const int NUMB_BULLETS = 10;
    static const int NUMB_INVADER = N_COL_INVADERS*N_ROW_INVADERS;
    static const int W_H_INVADER = 20;
    static const int DELAY = 10;

    int timerMain;
    QTimer *timerBullet[NUMB_BULLETS];

    Invader* invaders[NUMB_INVADER];
    Ship* ship;
    Bullet* bullet[NUMB_BULLETS];

    bool game_over;
    bool game_won;
    bool game_started;
    bool game_paused;
};
