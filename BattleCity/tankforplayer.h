#ifndef TANKFORPLAYER_H
#define TANKFORPLAYER_H

#include "tank.h"


class TankForPlayer: public Tank
{
    Q_OBJECT
public:
    explicit TankForPlayer(const QList<QString> fileNames, int numberOfPlayer);
    ~TankForPlayer();

    int  getNumberLife();
    void setNumberLife();
    void setInBeginPosition();
    int  _regimeGame;

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    int numberLife;

signals:
    void signalGameOver();
    void signalKillTank();
};

#endif // TANKFORPLAYER_H


