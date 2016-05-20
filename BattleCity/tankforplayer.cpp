#include "tankforplayer.h"
#include "constants.h"

#include <QKeyEvent>
#include <QDebug>

TankForPlayer::TankForPlayer(const QList<QString> fileNames, int numberOfPlayer):
    Tank(fileNames)
{
    numberLife   = 3;
    _numberKills = 0;

    switch (numberOfPlayer) {
        case 1: {
            actions.insert( Qt::Key_Up   , Key_Up   );
            actions.insert( Qt::Key_Down , Key_Down );
            actions.insert( Qt::Key_Right, Key_Right);
            actions.insert( Qt::Key_Left , Key_Left );
            actions.insert( Qt::Key_Space, Key_Space);

            iArrowUp    = Qt::Key_Up;
            iArrowDown  = Qt::Key_Down;
            iArrowRight = Qt::Key_Right;
            iArrowLeft  = Qt::Key_Left;
            iKeySpace   = Qt::Key_Space;

            break;
        }
        case 2: {
            actions.insert( Qt::Key_W, Key_Up   );
            actions.insert( Qt::Key_S, Key_Down );
            actions.insert( Qt::Key_D, Key_Right);
            actions.insert( Qt::Key_A, Key_Left );
            actions.insert( Qt::Key_B, Key_Space);

            iArrowUp    = Qt::Key_W;
            iArrowDown  = Qt::Key_S;
            iArrowRight = Qt::Key_D;
            iArrowLeft  = Qt::Key_A;
            iKeySpace   = Qt::Key_B;

            break;
        }
    }

}

TankForPlayer::~TankForPlayer()
{
    deleteLater();
}

int TankForPlayer::getNumberLife()
{
    return numberLife;
}

void TankForPlayer::setNumberLife()
{
    --numberLife;
}

void TankForPlayer::setInBeginPosition()
{
    if (this->_friendOrBattle)
    {
        this->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);

    }
    else
    {
        emit signalKillTank();
        this->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);
    }
}

/* virtual */ void TankForPlayer::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();

    if (event->isAutoRepeat() || !actions.contains(key)) {
        event->ignore();
        return;
    }

    if (key == iArrowUp) {
        rotateUp( false );
        activeKey.removeOne(iArrowUp);
    }
    else if (key == iArrowDown) {
        rotateDown( false );
        activeKey.removeOne(iArrowDown);
    }
    else if (key == iArrowRight) {
        rotateRight( false );
        activeKey.removeOne(iArrowRight);
    }
    else if (key == iArrowLeft) {
        rotateLeft( false );
        activeKey.removeOne(iArrowLeft);
    }

    event->accept();
}

/* virtual */ void TankForPlayer::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    Tank* t = dynamic_cast<Tank* >(QObject::sender());

    if (event->isAutoRepeat() || !actions.contains(key)) {
        event->ignore();
        return;
    }

    if (key != iKeySpace)
        activeKey.push_back(key);

    if (key == iArrowUp)
        rotateUp( true );
    else if (key == iArrowDown)
        rotateDown( true );
    else if (key == iArrowRight)
        rotateRight( true );
    else if (key == iArrowLeft)
        rotateLeft( true );
    else if (key == iKeySpace)
        emit signalShot(OBJ_NAME_PLAYER_1);

    event->accept();
}
