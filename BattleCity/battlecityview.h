#ifndef BATTLECITYVIEW_H
#define BATTLECITYVIEW_H

#include <QGraphicsView>
#include <QObject>

#include "battlecitymap.h"
#include "constants.h"
#include "fieldgame.h"

class BattleCityView : public QGraphicsView
{
    Q_OBJECT
public:
    BattleCityView(int regimeGame, bool _friend, UdpClient* client);
    ~BattleCityView();

    void ShowWalls(const QString &strTypeWall, int numberTypeWall, const QString &pathToImage);
    void ShowStatistic();


    int _map[WINDOW_WIDTH][WINDOW_HEIGHT];

private:
    BattleCityMap* map;
    FieldGame* fieldGame;
    QGraphicsTextItem* m_txtLevel;
    QGraphicsTextItem* m_txtCountLife;

    QList<QGraphicsPixmapItem*> listTank;

public slots:

    void slotClose(int numberKillsOnePlayer, int numberKillsTwoPlayer);

    void slotKillBotStatistic();
    void slotKillTankStatistic();

    void slotLoadNextLevel();
};

#endif // BATTLECITYVIEW_H
