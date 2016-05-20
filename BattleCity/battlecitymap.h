#ifndef BATTLECITYMAP_H
#define BATTLECITYMAP_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QThread>

#include "tankforplayer.h"
#include "parsing.h"
#include "redwall.h"
#include <tankbot.h>
#include "udpclient.h"

class BattleCityMap: public QGraphicsScene {
    Q_OBJECT
public:
    BattleCityMap(int regimeGame, bool _friend,  UdpClient* client, QObject* parent = 0);
            ~BattleCityMap();

    void StopGameForSwitchNewLevel();
    void LoadMapForNewLevel();

    int n_Map[CNT_ROWS_MAP][CNT_COLS_MAP];      // розмер карты
    QList <QGraphicsItem *> listObjectAtBase;   // Елементы что розмещены вокруг базы

    bool AuditPressKey(int key);

    int  _regimeGame;
    bool _deleteBase;

    QTimer* timerMoveTank1;                 // Таймер для переміщення танку плеєра 1
    QTimer* timerMoveTank2;                 // та плеєра 2
    QTimer* timerRunBot;
    QTimer* timerRunBot_2;
    QTimer* timerRunBot_3;
    QTimer* timerRunBot_4;
    QTimer* timerMoveBot;
    QTimer* timerMoveBot_2;
    QTimer* timerMoveBot_3;
    QTimer* timerMoveBot_4;
    QTimer* timerAuditBots;
    QTimer* timerMoveBots;

    QTimer* timerForShowBonus;              // Таймер для відображення та знищення бонусів
    QTimer* timerRemoveStar;

    QTimer* timerForShowProtectionBase;
    QTimer* timerRemoveProtectionBase;

    QTimer* timerForShowTimeBonus;
    QTimer* timerForSearchTimerBonus;
    QTimer* timerRemoveTimerBonus;

    QTimer* timerForShowExplosionBonus;
    QTimer* timerRemoveExplosionBonus;

    TankForPlayer* TankForPlay1;            // Танк первого и
    TankForPlayer* TankForPlay2;            // в второго игрока

    TankBot* bot;
    TankBot* bot_2;
    TankBot* bot_3;
    TankBot* bot_4;

    QGraphicsTextItem* textGameOver;

    bool runOneBot;     // розрешает добавление первого бота на карту
    bool runTwoBot;
    bool runThreeBot;
    bool runFourBot;
    bool updateOnlyTwoBots; // переместить в данный момент только 2 бота(что-бы все боти одновременно не обновлялисьs)
    int  updateOnlyOneBots; // переместить в данный момень только 1 бота(когда все боты уже на карте)

    QGraphicsPixmapItem *pixmapForStar;     // Тут зберігається картинка бонуса
    QGraphicsPixmapItem *pixmapForBase;
    QGraphicsPixmapItem *pixmapForBuildBase;
    QGraphicsPixmapItem *pixmapForRemoveBase;
    QGraphicsPixmapItem *pixmapForTime;
    QGraphicsPixmapItem *pixmapForExplosion;

    QList <QGraphicsPixmapItem *> listItems;    // обьекты белой стенки для защиты базы(если взят бонус защитить базу)

    Parsing *p_ReadFromFile;                // Клас для парсингу карти

    QGraphicsScene* m_gsHeadScene;


    bool m_blShowNameLevel;

    QList <QString> m_listFileNamesEasyBots;
    QList <QString> m_listFileNamesMiddleBots;
    QList <QString> m_listFileNamesHighBots;
    QList <QString> m_listFileNamesTankPlayer;

    void ShowNewLevel();

    /* /// Сеть /// */

    UdpClient *_client;
    QTimer    *timerForSendPosPlayer;
    bool       shot;

    int _increaseSpeedBots;

protected:
    virtual void keyPressEvent(QKeyEvent *event);       // Обробка нажаття клавіші та
    virtual void keyReleaseEvent(QKeyEvent *event);     // відпущення


signals:
    void signalTimeoutForOneBot   (                        ); // вызывается когда нужно переместить бота
    void signalTimeoutForTwoBot   (                        );
    void signalTimeoutForOneBot   ( int xBase , int yBase  ); // уничтожение базы
    void signalTimeoutForTwoBot   ( int xBase , int yBase  );

    void signalTimeoutForThreeBot (int xPlayer, int yPlayer);
    void signalTimeoutForFourBot  (int xPlayer, int yPlayer);

    void signalMoveOneBot   ();
    void signalMoveTwoBot   ();
    void signalMoveThreeBot (int x, int y);
    void signalMoveFourBot  (int x, int y);

    void signalUpdateBase(QString typeWall);

    void signalGameOver(int numberKillsOnePlayer, int numberKillsTwoPlayer);

    void signalKillBotForStatistic();

    void signalShowNextLevel();

    void signalKillTankForStatistic();

public slots:
    void slotAddBot_1 ();           // появление бота на карте после уничтожения
    void slotAddBot_2 ();
    void slotAddBot_3 ();
    void slotAddBot_4 ();

    void slotShowBonus   ();        // отображение бонусов
    void slotRemoveBonus ();        // удаление бонусов

    void slotShowProtectionBase      ();    // показать бонус защиты базы
    void slotBuildProtectionForBase  ();    // построить защуиту вокруг базы
    void slotRemoveBonusForBase      ();    // удалить защиту вокруг базы

    void slotShowTimeBonus           ();    // показать бонус остановки танков
    void slotStopAllBots             ();    // остановить всех танков
    void slotRemoveBonusForTimeBonus ();    // завести всех танков

    void slotShowExplosionBonus        ();
    void slotRemoveExplosionBonus      ();
    void slotRemoveExplosionBonusTimer ();

    void slotRunOneBot   ();        // первоначальное помещение бота на карту
    void slotRunTwoBot   ();
    void slotRunThreeBot ();
    void slotRunFourBot  ();

    void slotMoveThreeBot();
    void slotMoveFourBot();

    void slotGameOver    ();

    void slotSetPosPlayerForSend();
    void slotMoveOpponent(int x, int y, int rotate, bool shot2);
    void slotShotTank(QString str);

    void slotKillTank();

};

#endif // BATTLECITYMAP_H
