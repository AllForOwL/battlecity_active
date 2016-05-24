#ifndef TANK_H
#define TANK_H

#include "bullet.h"
//#include "tankforplayer.h"

class TankForPlayer;

class Tank: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tank(const QList<QString> fileNames,
                  QObject *parent = 0); // fileNames - пути к картинкам танка. Используются для анимации.
    ~Tank();

    QRectF boundingRect() const;        // Возвращет размеры танка в виде прямоугольника

    QPainterPath shape() const;         // Возвращет размеры танка в виде эллипса

    void paint(
               QPainter *painter,                       // Отрисовует танк и
               const QStyleOptionGraphicsItem *option,  // меняет его фреймы
               QWidget *widget
    );

    void setRotate2(int rotate); // поворачивание танка супротивника(при игре по сети)
    void LoadNewFrame(const QList<QString>& fileNames);


    bool ArrowUp;
    bool ArrowDown;
    bool ArrowRight;
    bool ArrowLeft;
    bool KeySpace;

    bool collision;

    int iArrowUp;
    int iArrowDown;
    int iArrowRight;
    int iArrowLeft;
    int iKeySpace;

    int _friendOrBattle;

    int bad_x;
    int bad_y;

    int m_iCountLevel;

protected:
    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };

    enum Action {
        Key_Up = 0,
        Key_Down,
        Key_Right,
        Key_Left,
        Key_Space
    };


    void rotateUp   (bool c) { ArrowUp    = c;  }
    void rotateDown (bool c) { ArrowDown  = c;  }
    void rotateRight(bool c) { ArrowRight = c;  }
    void rotateLeft (bool c) { ArrowLeft  = c;  }

    void setRotate(int r);

public:
    Bullet *shot();                             // Возвращает объект пули
    int currentFrame;                           // Значение текущего фрейма
    QList<Frame> frames;                        // Список фреймов, для танка.
                                                // Картинки, с которых делается анимация
    bool  _searchWayNow;
    int   _speed;                               // Скорость танка
    int   _rotate;                              // Быстрота текущее направление танка
    bool  _shot;
    int   _power;
    int   _numberKills;
    QMap<int, Action> actions;                  // Клавиши, которые "привязаны" к танку
    QList<int> activeKey;                       // Контейнер, в котором сохраняется последовательность,
                                                // зажатия несколько клавиш.
    QGraphicsItem *itemCollidesWith(QGraphicsItem *item);

public slots:
    void slotMoveTank();
    void slotTankShot(QString typeObject);
    void slotAllowShot();
    void slotGameOver();
    void slotKillBot();

signals:
    void signalShot(QString typeObject);                          // Сигнал стрельбы танка. Когда он поступает,
                                                // генерируется пуля и летит в своём направлении.
    void signalTankTookStar();
    void signalBuildProtectionForBase();
    void signalStopAllBots();
    void signalExplosionAllBots();

    void signalGameOver2();

    void signalSearchNewWay(bool useRotate);
};

#endif // TANK_H
