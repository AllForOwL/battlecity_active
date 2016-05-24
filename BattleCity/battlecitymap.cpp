#include <QList>
#include <QString>
#include <QKeyEvent>
#include <QThread>
#include <QGraphicsTextItem>
#include "sprite.h"
#include "battlecitymap.h"
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QEventLoop>

BattleCityMap::BattleCityMap(int regimeGame, bool _friend, UdpClient* client, QObject* parent) : QGraphicsScene(parent)
{
    m_blShowNameLevel = true;

    m_iCountDeath = 0;
    m_iCountLevel = 1;

    this->setBackgroundBrush(Qt::black);                            // Встановлення фонового кольору
    this->setSceneRect(0, 0, WINDOW_WIDTH+100, WINDOW_HEIGHT);      // Встановлення розміру сцени з початковими координатами 0,0
    // вверху лівої частини вікна

    timerForSendPosPlayer = new QTimer(this);
    shot = false;

    _regimeGame = regimeGame;
    _increaseSpeedBots = CNT_SPEED_MOVE_BOTS;
    _deleteBase = false;

    p_ReadFromFile = new Parsing();
    p_ReadFromFile->ParsTextFile(":/map/level_1.txt", n_Map, false);   // Завантаження карти з файлу

    m_listFileNamesEasyBots
            << ":/easyTanks/Tanks/tankBots/easyTank/down_1.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/down_2.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/left_1.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/left_2.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/up_1.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/up_2.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/right_1.png"
            << ":/easyTanks/Tanks/tankBots/easyTank/right_2.png"
               ;

    m_listFileNamesMiddleBots
            << ":/middleTanks/Tanks/tankBots/middleTank/down_1.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/down_2.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/left_1.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/left_2.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/up_1.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/up_2.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/right_1.png"
            << ":/middleTanks/Tanks/tankBots/middleTank/right_2.png"
               ;

    m_listFileNamesHighBots
            << ":/highTanks/Tanks/tankBots/highTank/down_1.png"
            << ":/highTanks/Tanks/tankBots/highTank/down_2.png"
            << ":/highTanks/Tanks/tankBots/highTank/left_1.png"
            << ":/highTanks/Tanks/tankBots/highTank/left_2.png"
            << ":/highTanks/Tanks/tankBots/highTank/up_1.png"
            << ":/highTanks/Tanks/tankBots/highTank/up_2.png"
            << ":/highTanks/Tanks/tankBots/highTank/right_1.png"
            << ":/highTanks/Tanks/tankBots/highTank/right_2.png"
               ;

    m_listFileNamesTankPlayer
              << ":/Tanks/tankPlayer/tank_Yellow_down_1.png"
              << ":/Tanks/tankPlayer/tank_Yellow_down_2.png"
              << ":/Tanks/tankPlayer/tank_Yellow_left_1.png"
              << ":/Tanks/tankPlayer/tank_Yellow_left_2.png"
              << ":/Tanks/tankPlayer/tank_Yellow_up_1.png"
              << ":/Tanks/tankPlayer/tank_Yellow_up_2.png"
              << ":/Tanks/tankPlayer/tank_Yellow_right_1.png"
              << ":/Tanks/tankPlayer/tank_Yellow_right_2.png"
                 ;

    timerMoveTank1      = new QTimer(this);
    timerMoveTank2      = new QTimer(this);

    timerForShowBonus   = new QTimer(this);
    timerRemoveStar     = new QTimer(this);

    timerForShowProtectionBase = new QTimer(this);
    timerRemoveProtectionBase  = new QTimer(this);

    timerForSearchTimerBonus = new QTimer(this);
    timerForShowTimeBonus    = new QTimer(this);
    timerRemoveTimerBonus    = new QTimer(this);

    timerForShowExplosionBonus = new QTimer(this);
    timerRemoveExplosionBonus  = new QTimer(this);

    timerRunBot    = new QTimer(this);
    timerRunBot_2  = new QTimer(this);
    timerRunBot_3  = new QTimer(this);
    timerRunBot_4  = new QTimer(this);

    timerMoveBot    = new QTimer(this);
    timerMoveBot_2  = new QTimer(this);
    timerMoveBot_3  = new QTimer(this);
    timerMoveBot_4  = new QTimer(this);
    timerMoveBots   = new QTimer(this);

    timerShowNextLevel = new QTimer(this);

    runOneBot   = false;
    runTwoBot   = false;
    runThreeBot = false;
    runFourBot  = false;

    updateOnlyTwoBots   = false;
    updateOnlyOneBots   = 0;

    if (regimeGame == 1)    // режым игры одного игрока
    {
        TankForPlay1 = new TankForPlayer(m_listFileNamesTankPlayer, 1);             // TankForPlayer приймає 2 параметри:
                                                                    // 1) фрейми для анімації
                                                                    // 2) Номер клавіш управління. Наприклад:
                                                                    //      1 - керування стрілками та вистріл через клавішу "space"
                                                                    //      2 - керування W,A,S,D та вистріл через клавішу "b"

        TankForPlay1->setZValue(0.5);
        TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(TankForPlay1);                                            // Добавлення на сцену

        timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);
        timerRunBot->setObjectName(OBJ_NAME_BOT_1);

        timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);
        timerRunBot_2->setObjectName(OBJ_NAME_BOT_2);

        timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);
        timerRunBot_3->setObjectName(OBJ_NAME_BOT_3);

        timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
        timerRunBot_4->setObjectName(OBJ_NAME_BOT_4);

    }
    else if (regimeGame == 2)   // режым игры двоих игроков
    {
        TankForPlay1 = new TankForPlayer(m_listFileNamesTankPlayer, 1);
        TankForPlay1->setZValue(0.5);
        TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(TankForPlay1);                                            // Добавлення на сцену

        TankForPlay2 = new TankForPlayer(m_listFileNamesTankPlayer, 2);
        TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        TankForPlay2->setPos(CNT_BEGIN_X_TWO_PLAYER, CNT_BEGIN_Y_TWO_PLAYER);
        TankForPlay2->setZValue(0.5);
        this->addItem(TankForPlay2);

        if (!_friend)
        {
            _deleteBase = true;
            TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);
        }
        else
        {

            timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);
            timerRunBot->setObjectName(OBJ_NAME_BOT_1);

            timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            timerRunBot_2->setObjectName(OBJ_NAME_BOT_2);

            timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            timerRunBot_3->setObjectName(OBJ_NAME_BOT_3);

            timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            timerRunBot_4->setObjectName(OBJ_NAME_BOT_4);

            timerMoveBots->start(_increaseSpeedBots);
        }

        QObject::connect( timerMoveTank2 , SIGNAL( timeout()           ), TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank(QString) ));   // Постріл танком

        QObject::connect( TankForPlay2, SIGNAL( signalTankTookStar() ), this, SLOT( slotRemoveBonus() ));

        timerMoveTank2->start(CNT_SPEED_MOVE_ONE_PLAYER);
        timerMoveTank2->setObjectName(OBJ_NAME_PLAYER_2);
    }
    else if (regimeGame == 3)                        // игра по сети
    {
        TankForPlay1 = new TankForPlayer(m_listFileNamesTankPlayer, 1);
        TankForPlay1->setZValue(0.5);
        TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(TankForPlay1);                                            // Добавлення на сцену

        TankForPlay2 = new TankForPlayer(m_listFileNamesTankPlayer, 2);
        TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        TankForPlay2->setPos(-40, 0);
        TankForPlay2->setZValue(0.5);
        this->addItem(TankForPlay2);

        if (!_friend)
        {
            _deleteBase = true;
            TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);
            TankForPlay1->_friendOrBattle = true;
        }
        else
        {
            timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);
            timerRunBot->setObjectName(OBJ_NAME_BOT_1);

            timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            timerRunBot_2->setObjectName(OBJ_NAME_BOT_2);

            timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            timerRunBot_3->setObjectName(OBJ_NAME_BOT_3);

            timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            timerRunBot_4->setObjectName(OBJ_NAME_BOT_4);

            timerMoveBots->start(_increaseSpeedBots);
        }

        _client = new UdpClient(client);
        timerForSendPosPlayer->start(CNT_TIMER_FOR_SEND_POS_PLAYER);

        QObject::connect( timerMoveTank2 , SIGNAL( timeout()           ), TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank()        ));   // Постріл танком
        QObject::connect( TankForPlay2   , SIGNAL( signalTankTookStar()), this          , SLOT( slotRemoveBonus()     ));

        QObject::connect( client , SIGNAL( signalReadInformationOpponent(int,int, int, bool)), this, SLOT( slotMoveOpponent(int,int, int, bool) ));

    }
    else
    {
        TankForPlay1 = new TankForPlayer(m_listFileNamesTankPlayer, 1);
        TankForPlay1->setZValue(0.5);
        TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        TankForPlay1->setPos(CNT_BEGIN_X_TWO_PLAYER, CNT_BEGIN_Y_TWO_PLAYER);   // Початкова позиція
        this->addItem(TankForPlay1);                                            // Добавлення на сцену

        TankForPlay2 = new TankForPlayer(m_listFileNamesTankPlayer, 2);
        TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        TankForPlay2->setPos(-40, 0);
        TankForPlay2->setZValue(0.5);
        this->addItem(TankForPlay2);

        if (!_friend)
        {
            _deleteBase = true;
        }
        else
        {
            timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);
            timerRunBot->setObjectName(OBJ_NAME_BOT_1);

            timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            timerRunBot_2->setObjectName(OBJ_NAME_BOT_2);

            timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            timerRunBot_3->setObjectName(OBJ_NAME_BOT_3);

            timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            timerRunBot_4->setObjectName(OBJ_NAME_BOT_4);

            timerMoveBots->start(_increaseSpeedBots);
        }

        _client = new UdpClient(client);
        timerForSendPosPlayer->start(CNT_TIMER_FOR_SEND_POS_PLAYER);

        QObject::connect( timerMoveTank2 , SIGNAL( timeout()           ), TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank(QString) ));   // Постріл танком
        QObject::connect( TankForPlay2   , SIGNAL( signalTankTookStar()), this          , SLOT( slotRemoveBonus()     ));

        QObject::connect( client , SIGNAL( signalReadInformationOpponent(int,int, int, bool)), this, SLOT( slotMoveOpponent(int,int, int, bool) ));
    }

    bot = new TankBot(m_listFileNamesEasyBots);
    bot->addTank = false;
    bot->setData(0, OBJ_NAME_BOT_1);
    bot->setObjectName(OBJ_NAME_BOT_1);
    bot->setPos(-32, 0);
    bot->setZValue(0.5);
    this->addItem(bot);

    bot_2 = new TankBot(m_listFileNamesEasyBots);
    bot_2->addTank = false;
    bot_2->setData(0, OBJ_NAME_BOT_2);
    bot_2->setObjectName(OBJ_NAME_BOT_2);
    bot_2->setPos(-32, 0);
    bot_2->setZValue(0.5);
    this->addItem(bot_2);

    bot_3 = new TankBot(m_listFileNamesEasyBots);
    bot_3->addTank = false;
    bot_3->setData(0, OBJ_NAME_BOT_3);
    bot_3->setObjectName(OBJ_NAME_BOT_3);
    bot_3->setPos(-32, 0);
    bot_3->setZValue(0.5);
    this->addItem(bot_3);

    bot_4 = new TankBot(m_listFileNamesEasyBots);
    bot_4->addTank = false;
    bot_4->setData(0, OBJ_NAME_BOT_4);
    bot_4->setObjectName(OBJ_NAME_BOT_4);
    bot_4->setPos(-32, 0);
    bot_4->setZValue(0.5);
    this->addItem(bot_4);

    timerMoveTank1->start(CNT_SPEED_MOVE_ONE_PLAYER);
    timerMoveTank1->setObjectName(OBJ_NAME_PLAYER_1);

//    timerForShowBonus->start(CNT_SECOND_SHOW_STAR);
//    timerForShowProtectionBase->start(CNT_SECOND_PROTECTION_BASE);
//    timerForShowTimeBonus->start(CNT_SECOND_STOP_ALL_BOT);
//    timerForShowExplosionBonus->start(CNT_SECOND_EXPLOSION_ALL_BOTS);

    QObject::connect( timerMoveTank1 , SIGNAL( timeout()           ) , TankForPlay1 , SLOT( slotMoveTank()        ));   // Переміщення танка
    QObject::connect( TankForPlay1   , SIGNAL( signalShot(QString) ) , TankForPlay1 , SLOT( slotTankShot(QString) ));   // Постріл танком
    QObject::connect( TankForPlay1   , SIGNAL( signalShot(QString) ) , this         , SLOT( slotShotTank(QString) ));   // Постріл танком

    QObject::connect( bot   , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_1() )); // убили первого бота - вернуть на карту
    QObject::connect( bot_2 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_2() ));
    QObject::connect( bot_3 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_3() ));
    QObject::connect( bot_4 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_4() ));


    QObject::connect(timerRunBot,  SIGNAL (timeout()),           this, SLOT (slotRunOneBot()));        // добавить первого бота на карту
    QObject::connect(timerMoveBot, SIGNAL (timeout()),           bot,  SLOT (Atack()));
    QObject::connect(bot,          SIGNAL (signalShot(QString)), bot,  SLOT (slotTankShot(QString))); // стрелять

    QObject::connect(timerRunBot_2,  SIGNAL (timeout()),           this,  SLOT (slotRunTwoBot()));
    QObject::connect(timerMoveBot_2, SIGNAL (timeout()),           bot_2, SLOT (Atack()));
    QObject::connect(bot_2,          SIGNAL (signalShot(QString)), bot_2, SLOT (slotTankShot(QString)));

    QObject::connect(timerRunBot_3,  SIGNAL (timeout()),                   this,  SLOT (slotRunThreeBot()));
    QObject::connect(timerMoveBot_3, SIGNAL (timeout()),                   this,  SLOT (slotMoveThreeBot()));
    QObject::connect(this,           SIGNAL (signalMoveThreeBot(int,int)), bot_3, SLOT (Atack(int, int)));
    QObject::connect(bot_3,          SIGNAL (signalShot(QString)),         bot_3, SLOT (slotTankShot(QString)));

    QObject::connect(timerRunBot_4,  SIGNAL (timeout()),                  this,  SLOT (slotRunFourBot()));
    QObject::connect(timerMoveBot_4, SIGNAL (timeout()),                  this,  SLOT (slotMoveFourBot()));
    QObject::connect(this,           SIGNAL (signalMoveFourBot(int,int)), bot_4, SLOT (Atack(int, int)));
    QObject::connect(bot_4,          SIGNAL (signalShot(QString)),        bot_4, SLOT (slotTankShot(QString)));

    QObject::connect( timerForShowBonus          , SIGNAL( timeout()                      ), SLOT( slotShowBonus()              ));                 // Додавання бонусів на карту
    QObject::connect( timerRemoveStar            , SIGNAL( timeout()                      ), SLOT( slotRemoveBonus()            ));

    QObject::connect( timerForShowProtectionBase , SIGNAL( timeout()                      ), SLOT( slotShowProtectionBase()     ));
    QObject::connect( TankForPlay1               , SIGNAL( signalBuildProtectionForBase() ), SLOT( slotBuildProtectionForBase() ));
    QObject::connect( timerRemoveProtectionBase  , SIGNAL( timeout()                      ), SLOT( slotRemoveBonusForBase()     ));

    QObject::connect( timerForShowTimeBonus    , SIGNAL( timeout()           ), SLOT( slotShowTimeBonus()           ));
    QObject::connect( TankForPlay1             , SIGNAL( signalStopAllBots() ), SLOT( slotStopAllBots()             ));
    QObject::connect( timerForSearchTimerBonus , SIGNAL( timeout()           ), SLOT( slotRemoveBonusForTimeBonus() ));
    QObject::connect( timerRemoveTimerBonus    , SIGNAL( timeout()           ), SLOT( slotRemoveBonusForTimeBonus() ));

    QObject::connect( timerForShowExplosionBonus , SIGNAL( timeout()                ), SLOT( slotShowExplosionBonus()        ));
    QObject::connect( TankForPlay1               , SIGNAL( signalExplosionAllBots() ), SLOT( slotRemoveExplosionBonus()      ));
    QObject::connect( timerRemoveExplosionBonus  , SIGNAL( timeout()                ), SLOT( slotRemoveExplosionBonusTimer() ));

    QObject::connect( TankForPlay1, SIGNAL( signalTankTookStar() ), this, SLOT( slotRemoveBonus() ));   // Піднімання бонусів танком



    QObject::connect( TankForPlay1, SIGNAL( signalKillTank()     ), this, SLOT( slotKillTank()    ));   // 3 убийствах танка

    QObject::connect( TankForPlay1, SIGNAL( signalGameOver()     ), this, SLOT( slotGameOver()    ));   // 3 убийствах танка
    QObject::connect( TankForPlay1, SIGNAL( signalGameOver2()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( bot         , SIGNAL( signalGameOver2()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( bot_2       , SIGNAL( signalGameOver2()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( bot_3       , SIGNAL( signalGameOver2()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( bot_4       , SIGNAL( signalGameOver2()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы

   // QObject::connect( timerShowNextLevel, SIGNAL(timeout()), this, SLOT(slotLoadNextLevel()));

   // QObject::connect( timerForSendPosPlayer , SIGNAL( timeout()), this, SLOT( slotSetPosPlayerForSend() ));

    delete p_ReadFromFile;
}

BattleCityMap::~BattleCityMap() {
    delete timerMoveTank1;
    delete timerMoveTank2;

    delete _client;

    delete TankForPlay1;
    if (_regimeGame == 2 || _regimeGame == 4)
    {
        delete TankForPlay2;
    }

    delete bot;
    delete bot_2;
    delete bot_3;
    delete bot_4;

    delete timerForSearchTimerBonus;
    delete timerForSendPosPlayer;
    delete timerForShowBonus;
    delete timerForShowExplosionBonus;
    delete timerForShowProtectionBase;
    delete timerForShowTimeBonus;
    delete timerMoveBot;
    delete timerMoveBots;
    delete timerMoveBot_2;
    delete timerMoveBot_3;
    delete timerMoveBot_4;
    delete timerRemoveExplosionBonus;
    delete timerRemoveProtectionBase;
    delete timerRemoveStar;
    delete timerRemoveTimerBonus;

}

void BattleCityMap::StopGameForSwitchNewLevel()
{
    timerMoveBot->stop();
    timerMoveBot_2->stop();
    timerMoveBot_3->stop();
    timerMoveBot_4->stop();

    timerMoveTank1->stop();

    bot->setPos(-32, 0);
    bot_2->setPos(-32, 0);
    bot_3->setPos(-32, 0);
    bot_4->setPos(-32, 0);

    TankForPlay1->setPos(-32, 0);
}

void BattleCityMap::LoadMapForNewLevel()
{
    p_ReadFromFile->ParsTextFile(":/log_parsing.txt", n_Map, false);   // Завантаження карти з файлу

    timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);
    timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);
    timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);
    timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);

    timerMoveTank1->start(CNT_SPEED_MOVE_ONE_PLAYER);

    TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);
}

bool BattleCityMap::AuditPressKey(int key)
{
    if (!_regimeGame == 2)   // если один игрок или сервер
    {
        if (
            key != Qt::Key_Space &&
            key != Qt::Key_Up    &&
            key != Qt::Key_Down  &&
            key != Qt::Key_Left  &&
            key != Qt::Key_Right
           )
        {
            return false;
        }
    }
    else                     // два игрока
    {
        if (
            key != Qt::Key_Space &&
            key != Qt::Key_Up    &&
            key != Qt::Key_Down  &&
            key != Qt::Key_Left  &&
            key != Qt::Key_Right &&
            key != Qt::Key_B     &&
            key != Qt::Key_W     &&
            key != Qt::Key_S     &&
            key != Qt::Key_A     &&
            key != Qt::Key_D
          )
        {
            return false;
        }
    }
    return true;
}

void BattleCityMap::ShowNewLevel()
{
    TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);

    timerRunBot->start(CNT_TIME_APPEARANCE_ONE_BOT);

    timerRunBot_2->start(CNT_TIME_APPEARANCE_TWO_BOT);

    timerRunBot_3->start(CNT_TIME_APPEARANCE_THREE_BOT);

    timerRunBot_4->start(CNT_TIME_APPEARANCE_FOUR_BOT);

    timerMoveTank1->start(CNT_SPEED_MOVE_ONE_PLAYER);
}

void BattleCityMap::slotSetPosPlayerForSend()
{
    int x = TankForPlay1->x();
    int y = TankForPlay1->y();
    int rotate = TankForPlay1->_rotate;

    _client->SendMessage(x, y, rotate, shot);

    shot = false;
}

void BattleCityMap::slotMoveOpponent(int x, int y, int rotate, bool shot2)
{
    TankForPlay2->setPos(x, y);
    TankForPlay2->setRotate2(rotate);

    if (shot2)
    {
        emit TankForPlay2->signalShot(TankForPlay2->objectName());
    }
}

void BattleCityMap::slotShotTank(QString str)
{
    shot = true;
}

void BattleCityMap::slotKillTank()
{
    emit signalKillTankForStatistic();
}

void BattleCityMap::slotRunOneBot()
{
    timerRunBot->stop();                                     // останавливаем таймер для бота
    timerMoveBot->start(CNT_SPEED_MOVE_BOTS);

    bot->setPos(CNT_BEGIN_X_ONE_BOT, CNT_BEGIN_Y_ONE_BOT);    // помещяем на карту
    runOneBot = true;                                         // розрешаем боту двигатся
}

void BattleCityMap::slotRunTwoBot()
{
    timerRunBot_2->stop();
    timerMoveBot_2->start(CNT_SPEED_MOVE_BOTS);

    bot_2->setPos(CNT_BEGIN_X_TWO_BOT, CNT_BEGIN_Y_TWO_BOT);
    runTwoBot = true;
}

void BattleCityMap::slotRunThreeBot()
{
    timerRunBot_3->stop();
    timerMoveBot_3->start(CNT_SPEED_MOVE_BOTS);

    bot_3->setPos(CNT_BEGIN_X_THREE_BOT, CNT_BEGIN_Y_THREE_BOT);
    runThreeBot = true;

}

void BattleCityMap::slotRunFourBot()
{
    timerRunBot_4->stop();
    timerMoveBot_4->start(CNT_SPEED_MOVE_BOTS);

    bot_4->setPos(CNT_BEGIN_X_FOUR_BOT, CNT_BEGIN_Y_FOUR_BOT);
    runFourBot = true;
}

void BattleCityMap::slotMoveThreeBot()
{
    emit signalMoveThreeBot(CNT_BASE_X, CNT_BASE_Y);
}

void BattleCityMap::slotMoveFourBot()
{
    emit signalMoveFourBot(CNT_BASE_X, CNT_BASE_Y);
}

void BattleCityMap::slotGameOver()
{
    if (_regimeGame == 1)
    {
        emit signalGameOver(TankForPlay1->_numberKills, 0);
    }
    else
    {
        emit signalGameOver(TankForPlay1->_numberKills, TankForPlay2->_numberKills);
    }
}

void BattleCityMap::slotShowBonus() {

    int x = (rand() % WINDOW_WIDTH)-30;
    int y = (rand() % WINDOW_HEIGHT)-30;

    pixmapForStar = addPixmap(QPixmap(PATH_TO_STAR));

    pixmapForStar->setPos(x, y);
    pixmapForStar->setData(0, OBJ_NAME_STAR);

    timerForShowBonus->stop();
    timerRemoveStar->start(CNT_TIME_SHOW_BONUS);
}

void BattleCityMap::slotShowProtectionBase()
{
    int x = (rand() % WINDOW_WIDTH)-30;
    int y = (rand() % WINDOW_HEIGHT)-30;

    pixmapForBase = addPixmap(QPixmap(PATH_TO_BONUS_BASE));

    pixmapForBase->setPos(x, y);
    pixmapForBase->setData(0, OBJ_NAME_BASE_BONUS);

    timerForShowProtectionBase->stop();
    timerRemoveProtectionBase->start(CNT_TIME_SHOW_BONUS);
}

void BattleCityMap::slotRemoveBonus()
{
    this->removeItem(pixmapForStar);
    timerForShowBonus->start(CNT_SECOND_SHOW_STAR);
}

void BattleCityMap::slotBuildProtectionForBase()
{
    this->removeItem(pixmapForBase);
    timerForShowProtectionBase->stop();
    timerRemoveProtectionBase->start(CNT_TIME_SHOW_BONUS);

    for (int i(0); i < listObjectAtBase.size(); i++)    // удалаем текущие елементы вокруг базы
    {
        removeItem(listObjectAtBase[i]);
    }

    for (int i(28); i < 32; i++)
    {
        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));

        pixmapForBuildBase->setPos(14*SIZE_WALL, i*SIZE_WALL);
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        listItems.push_back(pixmapForBuildBase);
    }

    for (int i(14); i < 19; i++)
    {
        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));

        pixmapForBuildBase->setPos(i*SIZE_WALL, 28*SIZE_WALL);
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        listItems.push_back(pixmapForBuildBase);
    }

    for (int i(28); i < 32; i++)
    {
        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));

        pixmapForBuildBase->setPos(19*SIZE_WALL, i*SIZE_WALL);
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        listItems.push_back(pixmapForBuildBase);
    }
}

void BattleCityMap::slotRemoveBonusForBase()
{
    this->removeItem(pixmapForBase);
    timerForShowProtectionBase->start(CNT_SECOND_PROTECTION_BASE);
    timerRemoveProtectionBase->stop();

    for (int i(0); i < listItems.size(); i++)           // удаляем временную белую стену
    {
        removeItem(listItems[i]);
    }

    for (int i(0); i < listObjectAtBase.size(); i++)    // помещяем елементы вокруг базы(что были с самого начала)
    {
        addItem(listObjectAtBase[i]);
    }
}

void BattleCityMap::slotShowTimeBonus()
{
    int x = (rand() % WINDOW_WIDTH)-30;
    int y = (rand() % WINDOW_HEIGHT)-30;

    pixmapForTime = addPixmap(QPixmap(PATH_TO_BONUS_TIME));

    pixmapForTime->setPos(x, y);
    pixmapForTime->setData(0, OBJ_NAME_TIME_BONUS);

    timerForShowTimeBonus->stop();
    timerRemoveTimerBonus->start(CNT_TIME_SHOW_BONUS);
}

void BattleCityMap::slotShowExplosionBonus()
{
    pixmapForExplosion = addPixmap(QPixmap(PATH_TO_BONUS_EXPLOSION));

    pixmapForExplosion->setPos(175, 440);
    pixmapForExplosion->setData(0, OBJ_NAME_EXPLOSION_BONUS);

    timerForShowExplosionBonus->stop();
    timerRemoveExplosionBonus->start(CNT_TIME_SHOW_BONUS);
}

void BattleCityMap::slotRemoveExplosionBonus()
{
    this->removeItem(pixmapForExplosion);
    timerForShowExplosionBonus->start(CNT_SECOND_EXPLOSION_ALL_BOTS);
    timerRemoveExplosionBonus->stop();

    Sprite *explosion;
    QRectF  tankExplosionF  (-25, -25, 50, 50);

    explosion = new Sprite(QPoint(bot->x(), bot->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_1();

    explosion = new Sprite(QPoint(bot_2->x(), bot_2->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_2();

    explosion = new Sprite(QPoint(bot_3->x(), bot_3->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_3();

    explosion = new Sprite(QPoint(bot_4->x(), bot_4->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_4();
}

void BattleCityMap::slotRemoveExplosionBonusTimer()
{
    this->removeItem(pixmapForExplosion);
    timerForShowExplosionBonus->start(CNT_SECOND_EXPLOSION_ALL_BOTS);
    timerRemoveExplosionBonus->stop();
}

void BattleCityMap::slotStopAllBots()
{
    timerMoveBots->stop();
    timerForSearchTimerBonus->start(CNT_TIME_STOP_BOTS);
}

void BattleCityMap::slotRemoveBonusForTimeBonus()
{
    this->removeItem(pixmapForTime);

    timerForShowTimeBonus->start(CNT_SECOND_STOP_ALL_BOT);
    timerRemoveTimerBonus->stop();
    timerForSearchTimerBonus->stop();
    timerMoveBots->start(CNT_SPEED_MOVE_BOTS);
}

/* virtual*/ void BattleCityMap::keyPressEvent(QKeyEvent *event) {

//    if (m_blShowNameLevel)
//    {
//        emit signalShowNextLevel();
//        return;
//    }

    int key = event->key();

    if (!AuditPressKey(key))
    {
        return;
    }

    if (TankForPlay1->actions.contains(key)) {
        emit TankForPlay1->keyPressEvent(event);
    }
    else if (TankForPlay2->actions.contains(key)) {
        emit TankForPlay2->keyPressEvent(event);
    }
}

/* virtual */void BattleCityMap::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();

    if (!AuditPressKey(key))
    {
        return;
    }

    if (TankForPlay1->actions.contains(key)) {
        emit TankForPlay1->keyReleaseEvent(event);
    }
    else if (TankForPlay2->actions.contains(key)) {
        emit TankForPlay2->keyReleaseEvent(event);
    }
}

void BattleCityMap::slotAddBot_2()
{
    emit signalKillBotForStatistic();

    ++m_iCountDeath;
    ++bot_2->numberDeaths;

    if (/*bot->numberDeaths == 3 &&*/ m_iCountDeath == 4)
    {
        timerMoveBot->stop();
        timerMoveBot_2->stop();
        timerMoveBot_3->stop();
        timerMoveBot_4->stop();

        bot->setPos(-32,0);
        bot_2->setPos(-32,0);
        bot_3->setPos(-32,0);
        bot_4->setPos(-32,0);

        emit signalLoadNextLevel();

        return;
    }
    else if (bot_2->numberDeaths == 3)
    {
        timerMoveBot_2->stop();
        return;
    }

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(64);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 32;
        listItems = this->items(myRect, Qt::IntersectsItemBoundingRect);

        if (_x > 480)
        {
            _x = 0;
        }

    } while(listItems.size() != 0);

    bot_2->setPos(_x, 0);
    bot_2->setData(0, OBJ_NAME_BOT_2);
    bot_2->setObjectName(OBJ_NAME_BOT_2);
    bot_2->setZValue(0.5);
    this->addItem(bot_2);

}

void BattleCityMap::slotAddBot_3()
{
    emit signalKillBotForStatistic();

    ++m_iCountDeath;
    ++bot_3->numberDeaths;

    if (/*bot->numberDeaths == 3 &&*/ m_iCountDeath == 4)
    {
        timerMoveBot->stop();
        timerMoveBot_2->stop();
        timerMoveBot_3->stop();
        timerMoveBot_4->stop();

        bot->setPos(-32,0);
        bot_2->setPos(-32,0);
        bot_3->setPos(-32,0);
        bot_4->setPos(-32,0);

        emit signalLoadNextLevel();

        return;
    }
    else if (bot_3->numberDeaths == 3)
    {
        timerMoveBot_3->stop();
        return;
    }

    bot_3->indexWay = 0;

    qsrand(QTime::currentTime().msec());

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(64);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 32;
        listItems = this->items(myRect, Qt::IntersectsItemBoundingRect);

        if (_x > 480)
        {
            _x = 0;
        }

    } while(listItems.size() != 0);

    bot_3->setPos(_x, 0);
    bot_3->setData(0, OBJ_NAME_BOT_3);
    bot_3->setObjectName(OBJ_NAME_BOT_3);
    bot_3->setZValue(0.5);
    this->addItem(bot_3);
}

void BattleCityMap::slotAddBot_4()
{
    emit signalKillBotForStatistic();

    ++m_iCountDeath;
    ++bot_4->numberDeaths;

    if (/*bot->numberDeaths == 3 &&*/ m_iCountDeath == 4)
    {
        timerMoveBot->stop();
        timerMoveBot_2->stop();
        timerMoveBot_3->stop();
        timerMoveBot_4->stop();

        bot->setPos(-32,0);
        bot_2->setPos(-32,0);
        bot_3->setPos(-32,0);
        bot_4->setPos(-32,0);

        emit signalLoadNextLevel();

        return;
    }
    else if (bot_4->numberDeaths == 3)
    {
        timerMoveBot_4->stop();
        return;
    }

    bot_4->indexWay = 0;

    qsrand(QTime::currentTime().msec());

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(64);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 32;
        listItems = this->items(myRect, Qt::IntersectsItemBoundingRect);

        if (_x > 480)
        {
            _x = 0;
        }

    } while(listItems.size() != 0);

    bot_4->setPos(_x, 0);
    bot_4->setData(0, OBJ_NAME_BOT_4);
    bot_4->setObjectName(OBJ_NAME_BOT_4);
    bot_4->setZValue(0.5);
    this->addItem(bot_4);
}

void BattleCityMap::slotAddBot_1()
{
    emit signalKillBotForStatistic();

    ++m_iCountDeath;
    ++bot->numberDeaths;

    if (/*bot->numberDeaths == 3 &&*/ m_iCountDeath == 1)
    {
        timerMoveBot->stop();
        timerMoveBot_2->stop();
        timerMoveBot_3->stop();
        timerMoveBot_4->stop();
        timerRunBot->stop();
        timerRunBot_2->stop();
        timerRunBot_3->stop();
        timerRunBot_4->stop();


        /*bot->setPos(-32,0);

        bot_2->setPos(-32,0);
        bot_3->setPos(-32,0);
        bot_4->setPos(-32,0);
        */

     //   bot->~QGraphicsItem();

        timerShowNextLevel->start(5000);

     //   emit signalLoadNextLevel();

        return;
    }
    else if (bot->numberDeaths == 3)
    {
        timerMoveBot->stop();
        return;
    }

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(64);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 32;
        listItems = this->items(myRect, Qt::IntersectsItemBoundingRect);

        if (_x > 480)
        {
            _x = 0;
        }

    } while(listItems.size() != 0);

    bot->setPos(_x, 0);
    bot->setData(0, OBJ_NAME_BOT_1);
    bot->setObjectName(OBJ_NAME_BOT_1);
    bot->setZValue(0.5);
    this->addItem(bot);
}
