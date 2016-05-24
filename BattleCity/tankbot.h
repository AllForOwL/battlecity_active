#ifndef TANKBOT_H
#define TANKBOT_H

#include "tank.h"
#include "constants.h"
#include <vector>       // vector<T>
#include "algorithmli.h"

using std::vector;

struct QPoint2D {
    int x;
    int y;

    QPoint2D() {
        x = y = 0;
    }

    QPoint2D(int x, int y) {
        this->x  = x;
        this->y  = y;
    }
};

class TankBot: public Tank
{
    Q_OBJECT
public:
    explicit TankBot(const QList<QString> fileNames);
    void setMap(int map[CNT_ROWS_MAP][CNT_COLS_MAP]);
    ~TankBot();

public:

    bool deleteBullet;
    int  map[CNT_ROWS_MAP][CNT_COLS_MAP];
    void outMap();

    vector <QPoint2D> path;
    vector <QPoint2D> shortPath;
    QVector <point> _previousStep;

    bool searchWay; // был ли поиск пути
    int  indexWay;   // в какой точке сейчас находимся

    algorithmLI    *algorithmSearchWay;
    QVector<point> vectorFoundWay;

    int    mapSearchWay[CNT_ROWS_MAP][CNT_COLS_MAP];

    QTimer* timerSetAtackRegime;

    bool changeRotate;

public:
    int x_end;
    int y_end;

    bool addTank;       // розрешение добавлени бота на карту
    int  numberDeaths;   // количевство смертей
    int  countStep;

signals:
    void signalOneSearchWay(int temp_x_begin, int temp_y_begin, int temp_x_end, int temp_y_end);

public slots:
    void slotSearchPath(int temp_x_begin, int temp_y_begin, int temp_x_end, int temp_y_end);
    void Atack(int xPlayer, int yPlayer);   // поиск пути для игроков
    void Atack();                           // поиск пути для ботов

    void slotSearchNewWayAfterCollision(bool useRotate);
};

#endif // TANKBOT_H
