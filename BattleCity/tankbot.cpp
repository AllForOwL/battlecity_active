#include "tankbot.h"
#include <QKeyEvent>
#include "constants.h"
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <time.h>
#include <QTime>

using namespace std;

TankBot::TankBot(const QList<QString> fileNames): Tank(fileNames)
{
    setRotate(270);
    deleteBullet = false;
    searchWay = false;
    indexWay  = 0;
    addTank = false;
    changeRotate = false;
    numberDeaths = 0;
    countStep = 0;
    algorithmSearchWay = new algorithmLI;

    QObject::connect(this, SIGNAL (signalOneSearchWay(int,int,int,int)), this, SLOT (slotSearchPath(int,int,int,int)));
    QObject::connect(this, SIGNAL (signalSearchNewWay(bool)),            this, SLOT (slotSearchNewWayAfterCollision(bool)));
}

void TankBot::slotSearchPath(int temp_x_begin, int temp_y_begin, int temp_x_end, int temp_y_end)
{

    algorithmSearchWay->AuditSearchWay(temp_x_begin, temp_y_begin, temp_x_end, temp_y_end);

    if  (algorithmSearchWay->vectorFoundWay.size() == 0)
    {
        return;
    }
    else
    {
        vectorFoundWay.resize(algorithmSearchWay->vectorFoundWay.size());
        copy(algorithmSearchWay->vectorFoundWay.begin(), algorithmSearchWay->vectorFoundWay.end(),
        vectorFoundWay.begin()); // копирование пути в вектор этого класса с класса нахождения пути

           indexWay = CNT_FOUND_WAY;
    }
}

// поиск пути для игроков
void TankBot::Atack(int xPlayer, int yPlayer)
{
   if (indexWay == 0) // если достигли финиша
   {
       emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, yPlayer/SIZE_WALL, xPlayer/SIZE_WALL);
       return;
   }
        if (indexWay == CNT_FOUND_WAY)
        {
            indexWay = vectorFoundWay.size()-1;           // получаем предпоследний елемент пути

            x_end = vectorFoundWay[indexWay].y * SIZE_WALL; // получаем x и y предпоследнего
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL; // елемента пути

            if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
            {
                if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                {
                    this->_rotate = 0;   // едем вверх
                }
                else
                {
                    this->_rotate = 180; // едем вниз
                }
            }
            else
            {
                if (x_end > this->x())   // если текущий x менше x следующего елемента пути
                {
                    this->_rotate = 90;  // едем вправо
                }
                else
                {
                    this->_rotate = 270; // едем влево
                }
            }
        }
        else if (this->x() == x_end && this->y() == y_end) // когда текущие x і y ровны елементу пути
                {
                    --indexWay;                                   // переходим к следующему елементу пути
                    x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
                    y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

                    if (x_end == this->x())
                    {
                        if (y_end < this->y())
                        {
                            this->_rotate = 0;
                        }
                        else
                        {
                            this->_rotate = 180;
                        }
                    }
                    else if (y_end == this->y())
                    {
                        if (x_end > this->x())
                        {
                            this->_rotate = 90;
                        }
                        else
                        {
                            this->_rotate = 270;
                        }
                    }
               }
                else
                 {
                    x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
                    y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

                    if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
                    {
                        if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                        {
                            this->_rotate = 0;   // едем вверх
                        }
                        else
                        {
                            this->_rotate = 180; // едем вниз
                        }
                    }
                    else
                    {
                        if (x_end > this->x())   // если тaекущий x менше x следующего елемента пути
                        {
                            this->_rotate = 90;  // едем вправо
                        }
                        else
                        {
                            this->_rotate = 270; // едем влево
                        }
                    }
                 }

    activeKey.clear();
    switch (this->_rotate)
    {
    case 0:
            activeKey.push_back(Qt::Key_Up);
        break;
    case 90:
            activeKey.push_back(Qt::Key_Right);
        break;
    case 180:
            activeKey.push_back(Qt::Key_Down);
        break;
    case 270:
            activeKey.push_back(Qt::Key_Left);
        break;
    }

      emit slotMoveTank();
      emit slotTankShot(this->objectName());
}

// поиск пути для ботов
void TankBot::Atack()
{
    if (countStep >= CNT_SEARCH_NEW_WAY)
    {
        countStep = 0;
        emit signalSearchNewWay(true);

        return;
    }
    else if (indexWay == CNT_END_WAY) // если достигли финиша
    {
        countStep = 0;
        emit signalSearchNewWay(false);

        return;
    }

    ++countStep;

        if (indexWay == CNT_FOUND_WAY)
        {
            indexWay = vectorFoundWay.size()-1;           // получаем предпоследний елемент пути

            x_end = vectorFoundWay[indexWay].y * SIZE_WALL; // получаем x и y предпоследнего
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL; // елемента пути

            if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
            {
                if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                {
                    this->_rotate = 0;   // едем вверх
                }
                else
                {
                    this->_rotate = 180; // едем вниз
                }
            }
            else
            {
                if (x_end > this->x())   // если текущий x менше x следующего елемента пути
                {
                    this->_rotate = 90;  // едем вправо
                }
                else
                {
                    this->_rotate = 270; // едем влево
                }
            }

        }
        else if (this->x() == x_end && this->y() == y_end) // когда текущие x і y ровны елементу пути
                {
                    --indexWay;                                   // переходим к следующему елементу пути
                    x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
                    y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

                    if (x_end == this->x())
                    {
                        if (y_end < this->y())
                        {
                            this->_rotate = 0;
                        }
                        else
                        {
                            this->_rotate = 180;
                        }
                    }
                    else if (y_end == this->y())
                    {
                        if (x_end > this->x())
                        {
                            this->_rotate = 90;
                        }
                        else
                        {
                            this->_rotate = 270;
                        }
                    }
               }
                else
                 {
                    x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
                    y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

                    if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
                    {
                        if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                        {
                            this->_rotate = 0;   // едем вверх
                        }
                        else
                        {
                            this->_rotate = 180; // едем вниз
                        }
                    }
                    else
                    {
                        if (x_end > this->x())   // если тaекущий x менше x следующего елемента пути
                        {
                            this->_rotate = 90;  // едем вправо
                        }
                        else
                        {
                            this->_rotate = 270; // едем влево
                        }
                    }
                 }

    activeKey.clear();
    switch (this->_rotate)
    {
    case 0:
        activeKey.push_back(Qt::Key_Up);
        break;
    case 90:
        activeKey.push_back(Qt::Key_Right);
        break;
    case 180:
        activeKey.push_back(Qt::Key_Down);
        break;
    case 270:
        activeKey.push_back(Qt::Key_Left);
        break;
    }

    emit slotMoveTank();
    emit slotTankShot(this->objectName());
}

void TankBot::slotSearchNewWayAfterCollision(bool useRotate)
{
    qsrand(QTime::currentTime().msec());

    int xPlayer = 0;
    int yPlayer = 0;

    if (useRotate)
    {
        if (this->y() <= 250)
        {
            switch (this->_rotate)
            {
                case 0:
                {qDebug() << "0";
                    if (this->x() >= 250)
                    {
                        xPlayer = rand() % 480 + 64 ;
                        yPlayer = this->y();
                    }
                    else
                    {
                        xPlayer = rand() % 440 + 380;
                        yPlayer = this->y();
                    }
                    break;
                }
                case 90:
                {qDebug() << "90";
                    if (this->y() >= 250)
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    else
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    break;
                }
                case 180:
                {qDebug() << "180";
                    if (this->x() >= 250)
                    {
                        xPlayer = rand() % 128 + 64;
                        yPlayer = this->y();
                    }
                    else
                    {
                        xPlayer = rand() % 480 + 380;
                        yPlayer = this->y();
                    }
                    break;
                }
                case 270:
                {qDebug() << "270";
                    if (this->y() >= 250)
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    else
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    break;
                }
            }
         }
        else
        {
            switch (this->_rotate)
            {
                case 0:
                {qDebug() << "90";
                    if (this->y() >= 250)
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    else
                    {
                        xPlayer = this->x();
                        yPlayer = rand() % 480 + 220;
                    }
                    break;
                }
                    case 90:
                    {qDebug() << "0";
                        if (this->x() >= 250)
                        {
                            xPlayer = rand() % 128 + 64;
                            yPlayer = this->y();
                        }
                        else
                        {
                            xPlayer = rand() % 440 + 380;
                            yPlayer = this->y();
                        }
                        break;
                    }


                    case 180:
                    {qDebug() << "270";
                        if (this->y() >= 250)
                        {
                            xPlayer = this->x();
                            yPlayer = rand() % 480 + 220;
                        }
                        else
                        {
                            xPlayer = this->x();
                            yPlayer = rand() % 480 + 220;
                        }
                        break;
                    }
                case 270:
                {qDebug() << "180";
                    if (this->x() >= 250)
                    {
                        xPlayer = rand() % 128 + 64;
                        yPlayer = this->y();
                    }
                    else
                    {
                        xPlayer = rand() % 480 + 340;
                        yPlayer = this->y();
                    }
                    break;
                }
            }
        }
    }
    else
    {
        xPlayer = rand() % 480 + 100;
        yPlayer = rand() % 480 + 220;
    }

    emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL,  yPlayer/SIZE_WALL, xPlayer/SIZE_WALL);
}

TankBot::~TankBot()
{
    deleteLater();
}
