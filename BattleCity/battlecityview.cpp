#include <QGraphicsTextItem>
#include <QGraphicsGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "battlecityview.h"
#include <QImage>
#include <QList>

BattleCityView::BattleCityView(int regimeGame, bool _friend, UdpClient *client): QGraphicsView() {

    map = new BattleCityMap(regimeGame,_friend, client);
    this->setScene(map);

    this->setFixedSize(WINDOW_WIDTH+100, WINDOW_HEIGHT+2);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);

    m_txtLevel     = new QGraphicsTextItem();
    m_txtCountLife = new QGraphicsTextItem();

    ShowWalls(OBJ_NAME_WATER     , OBJ_TYPE_WATER     , ":/walls/1.jpg");
    ShowWalls(OBJ_NAME_ICE       , OBJ_TYPE_ICE       , ":/walls/2.jpg");
    ShowWalls(OBJ_NAME_RED_WALL  , OBJ_TYPE_RED_WALL  , ":/walls/3.jpg");
    ShowWalls(OBJ_NAME_GRASS     , OBJ_TYPE_GRASS     , ":/walls/4.png");
    ShowWalls(OBJ_NAME_WHITE_WALL, OBJ_TYPE_WHITE_WALL, ":/walls/5.jpg");
   // ShowWalls(OBJ_NAME_BASE      , OBJ_TYPE_BASE      , ":/Explosion/base.png");
    ShowStatistic();

    QObject::connect(map, SIGNAL(signalGameOver(int,int)), this, SLOT(slotClose(int,int)));

    QObject::connect(map, SIGNAL(signalKillBotForStatistic()), this, SLOT(slotKillBotStatistic()));

    QObject::connect(map, SIGNAL(signalKillTankForStatistic()), this, SLOT(slotKillTankStatistic()));

    QObject::connect(map->timerShowNextLevel, SIGNAL(timeout()), this, SLOT(slotLoadNextLevel()));

}

BattleCityView::~BattleCityView()
{
    map->~BattleCityMap();
}

void BattleCityView::ShowWalls(const QString &strTypeWall,
                               int numberTypeWall,
                               const QString &pathToImage)
{
    if (
        map->_deleteBase &&
        numberTypeWall == OBJ_TYPE_BASE
       )
    {
        return;
    }

    for (int i = 0; i < CNT_ROWS_MAP; i++)
        for (int j = 0; j < CNT_COLS_MAP; j++)
            if (map->n_Map[i][j] == numberTypeWall)
            {
                QGraphicsItem *p_MyImage = new RedWall(pathToImage);

                p_MyImage->setPos(SIZE_WALL*j, SIZE_WALL*i);
                p_MyImage->setData(0, strTypeWall);

                if (strTypeWall == OBJ_NAME_GRASS)
                    p_MyImage->setZValue(1.0);

                if (
                    (   i >= 28  )  && ( i < 32  ) &&   // строки
                    ( ( j == 14  )  || ( j == 19 ) )    // столбцы
                   )
                    if (!map->_deleteBase)
                    {
                        map->listObjectAtBase.push_back(p_MyImage);
                    }
                    else
                    {
                        continue;
                    }
                if (
                     ( j >= 14 ) && ( j < 19 ) &&      // столбцы
                     ( i == 28 )                       // строки
                   )
                {
                    if (!map->_deleteBase)
                    {
                        map->listObjectAtBase.push_back(p_MyImage);
                    }
                    else
                    {
                        continue;
                    }
                }

                map->addItem(p_MyImage);
            }
}

void BattleCityView::ShowStatistic()
{
    QGraphicsRectItem* fieldStatistic = new QGraphicsRectItem();

    fieldStatistic->setRect(512, 0, 100, 514);

    QBrush brush(Qt::SolidPattern);

    brush.setColor(Qt::darkGray);
    fieldStatistic->setBrush(brush);
    fieldStatistic->setZValue(1.0);

    map->addItem(fieldStatistic);

    int x;
    int y = 78;

    for (int j(0); j < 3; j++)
    {
        x = 496;
        y += 22;
        for (int i(0); i < 3; i++)
        {
            x += 28;
            QGraphicsPixmapItem* imageTank = new QGraphicsPixmapItem();
            imageTank->setPixmap(QPixmap(":/statistic/tank.png"));
            imageTank->setPos(x, y);
            imageTank->setData(0, "tankStatistic");
            imageTank->setZValue(1.0);
            listTank.append(imageTank);
            map->addItem(imageTank);
        }
    }

    QGraphicsPixmapItem* level = new QGraphicsPixmapItem();
    level->setPixmap(QPixmap(":/statistic/level.png"));
    level->setPos(540, 420);
    level->setData(0, "level");
    level->setZValue(1.0);
    map->addItem(level);

    m_txtLevel->setPlainText("1");
    m_txtLevel->setFont(QFont("Serif", 15, QFont::Bold));
    m_txtLevel->setDefaultTextColor(Qt::black);
    m_txtLevel->setPos(555, 440);
    m_txtLevel->setZValue(1.0);
    map->addItem(m_txtLevel);

    QGraphicsPixmapItem* countLife = new QGraphicsPixmapItem();
    countLife->setPixmap(QPixmap(":/statistic/countLife.png"));
    countLife->setPos(540, 330);
    countLife->setData(0, "countLife");
    countLife->setZValue(1.0);
    map->addItem(countLife);

    QGraphicsPixmapItem* countLifeTank = new QGraphicsPixmapItem();
    countLifeTank->setPixmap(QPixmap(":/statistic/tank.png"));
    countLifeTank->setPos(540, 365);
    countLifeTank->setData(0, "countLife");
    countLifeTank->setZValue(1.0);
    map->addItem(countLifeTank);

    m_txtCountLife->setPlainText("3");
    m_txtCountLife->setFont(QFont("Serif", 15, QFont::Bold));
    m_txtCountLife->setDefaultTextColor(Qt::black);
    m_txtCountLife->setPos(558, 358);
    m_txtCountLife->setZValue(1.0);
    map->addItem(m_txtCountLife);
}

void BattleCityView::slotClose(int numberKillsOnePlayer, int numberKillsTwoPlayer)
{
    int fontSize = 12;                                             // Размер шрифта для надписей(Player, PTS, etc);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 512, 512);

    QGraphicsView *view = new QGraphicsView();
    view->setFixedSize(512, 512);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // Убираем горизонтальные и
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);      // вертикальные полосы прокрутки

    QString hiscoreValue = "34100";
    QGraphicsWidget *lblScore = scene->addWidget(new QLabel("<center>HI-SCORE " + hiscoreValue + "</center>"));

    QPalette palette = lblScore->palette();                        // Палитра которую применим к надписи
    palette.setColor(QPalette::Background, QColor(Qt::black));     // Задний фон палитри - черного цвета, а
    palette.setColor(QPalette::Foreground, QColor(Qt::red));       // передний красного
    lblScore->setPalette(palette);                                 // Установка палитры
    lblScore->setFont(QFont("M10_BATTLE CITIES", fontSize));       // Установка шрифта фона и размера

    QString stageValue = "1";
    QGraphicsWidget *lblStage = scene->addWidget(new QLabel("<center>STAGE " + stageValue + "</center>"));
    palette = lblStage->palette();
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));
    lblStage->setPalette(palette);
    lblStage->setFont(lblScore->font());

    // Player 1
    QGraphicsWidget *lblPlayer1 = scene->addWidget(new QLabel("PLAYER 1"));
    lblPlayer1->setPalette(lblScore->palette());
    lblPlayer1->setFont(lblScore->font());

    QGraphicsWidget *lblPlayer2 = scene->addWidget(new QLabel("<p align='left'>PLAYER 2</p>"));
    lblPlayer2->setPalette(lblScore->palette());
    lblPlayer2->setFont(lblScore->font());

    // Количество очков Player1 за убитые танки
    QGraphicsWidget *lblCntScore = scene->addWidget(new QLabel("200"));
    lblCntScore->setPalette(lblScore->palette());
    lblCntScore->setFont(lblScore->font());

    QGraphicsWidget *lblCntScore2 = scene->addWidget(new QLabel("<p align='right'>200</p>"));
    lblCntScore2->setPalette(lblScore->palette());
    lblCntScore2->setFont(lblScore->font());

    // PTS 1
    // Для Player 1
    QGraphicsWidget *lblPTS1 = scene->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS1->setPalette(palette);
    lblPTS1->setFont(lblScore->font());

    // Количество очков за убитые танки "простой танк":
    QGraphicsWidget *iPTS1 = scene->addWidget(new QLabel("<p align='right'>100</p>"));
    iPTS1->setPalette(palette);
    iPTS1->setFont(lblScore->font());
    iPTS1->setMaximumWidth(75);

    // Количество убитых танков типа "простой танк":
    QGraphicsWidget *iCntKilledTanks1 = scene->addWidget(new QLabel("<p align='right'>2</p>"));
    iCntKilledTanks1->setPalette(palette);
    iCntKilledTanks1->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *lblPTS12 = scene->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS12->setPalette(palette);
    lblPTS12->setFont(lblScore->font());

    QGraphicsWidget *iPTS12 = scene->addWidget(new QLabel("<p align='right'>100</p>"));
    iPTS12->setPalette(palette);
    iPTS12->setFont(lblScore->font());
    iPTS12->setMaximumWidth(75);

    QGraphicsWidget *iCntKilledTanks12 = scene->addWidget(new QLabel("2"));
    iCntKilledTanks12->setPalette(palette);
    iCntKilledTanks12->setFont(lblScore->font());

    // PTS 2
    QGraphicsWidget *iPTS2 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS2->setPalette(palette);
    iPTS2->setFont(lblScore->font());
    iPTS2->setMaximumWidth(75);

    QGraphicsWidget *lblPTS2 = scene->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS2->setPalette(palette);
    lblPTS2->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks2 = scene->addWidget(new QLabel("<p align='right'>2</p>"));
    iCntKilledTanks2->setPalette(palette);
    iCntKilledTanks2->setFont(lblScore->font());
    // Player 2
    QGraphicsWidget *iPTS22 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS22->setPalette(palette);
    iPTS22->setFont(lblScore->font());
    iPTS22->setMaximumWidth(75);

    QGraphicsWidget *lblPTS22 = scene->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS22->setPalette(palette);
    lblPTS22->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks22 = scene->addWidget(new QLabel("2"));
    iCntKilledTanks22->setPalette(palette);
    iCntKilledTanks22->setFont(lblScore->font());

    // PTS 3
    // Player 1
    QGraphicsWidget *iPTS3 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS3->setPalette(palette);
    iPTS3->setFont(lblScore->font());
    iPTS3->setMaximumWidth(75);

    QGraphicsWidget *lblPTS3 = scene->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS3->setPalette(palette);
    lblPTS3->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks3 = scene->addWidget(new QLabel("<p align='right'>2</p>"));
    iCntKilledTanks3->setPalette(palette);
    iCntKilledTanks3->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *iPTS32 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS32->setPalette(palette);
    iPTS32->setFont(lblScore->font());
    iPTS32->setMaximumWidth(75);

    QGraphicsWidget *lblPTS32 = scene->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS32->setPalette(palette);
    lblPTS32->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks32 = scene->addWidget(new QLabel("2"));
    iCntKilledTanks32->setPalette(palette);
    iCntKilledTanks32->setFont(lblScore->font());

    // PTS 4
    // Player 1
    QGraphicsWidget *iPTS4 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS4->setPalette(palette);
    iPTS4->setFont(lblScore->font());
    iPTS4->setMaximumWidth(75);
    QGraphicsWidget *lblPTS4 = scene->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS4->setPalette(palette);
    lblPTS4->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks4 = scene->addWidget(new QLabel("<p align='right'>2</p>"));
    iCntKilledTanks4->setPalette(palette);
    iCntKilledTanks4->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *iPTS42 = scene->addWidget(new QLabel("<p align='right'>1</p>"));
    iPTS42->setPalette(palette);
    iPTS42->setFont(lblScore->font());
    iPTS42->setMaximumWidth(75);
    // PTS 4
    QGraphicsWidget *lblPTS42 = scene->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS42->setPalette(palette);
    lblPTS42->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks42 = scene->addWidget(new QLabel("2"));
    iCntKilledTanks42->setPalette(palette);
    iCntKilledTanks42->setFont(lblScore->font());

    QGraphicsWidget *lblTotal = scene->addWidget(new QLabel("<p align='right'>Total</p>"));
    lblTotal->setPalette(palette);
    lblTotal->setFont(lblScore->font());

    QGraphicsWidget *lblTotalVal1 = scene->addWidget(new QLabel("<p align='right'>2</p>"));
    lblTotalVal1->setPalette(palette);
    lblTotalVal1->setFont(lblScore->font());

    QGraphicsWidget *lblTotalVal2 = scene->addWidget(new QLabel("<p align='left'>2</p>"));
    lblTotalVal2->setPalette(palette);
    lblTotalVal2->setFont(lblScore->font());

    // Виды танков
    QLabel *lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/tanksForStatistic/easy.png"));
    QGraphicsWidget *imgTankEasy = scene->addWidget(lbl);       // "простой танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/tanksForStatistic/speed.png"));
    QGraphicsWidget *imgTankSpeed = scene->addWidget(lbl);      // "быстрый танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/tanksForStatistic/middle.png"));
    QGraphicsWidget *imgTankMiddle = scene->addWidget(lbl);     // "средний танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/tanksForStatistic/hard.png"));
    QGraphicsWidget *imgTankHard = scene->addWidget(lbl);       // "тяжолый танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/additionalImgs/whiteLine.png"));
    QGraphicsWidget *imgWhiteLine = scene->addWidget(lbl);      // Белая линия которая
                                                                // отображается в конце таблицы

    QGraphicsGridLayout *layoutGrid = new QGraphicsGridLayout();
    for (int i = 0; i < 5; i++) {
        layoutGrid->setRowSpacing(i, 15);                       // Отступ между строкой
    }
    layoutGrid->setRowSpacing(5, 5);

    layoutGrid->setContentsMargins(0, 0, 10, 0);
    // Player 1
    layoutGrid->addItem(lblPlayer1 , 0, 0, 1, 2);               // Добавляем объект lblPlayer1 в 0 строку, 0 столбец,
                                                                // и соеденяем столбец 0 и 1 в единое целое
    layoutGrid->addItem(lblCntScore, 1, 1);

    layoutGrid->addItem(iPTS1  , 2, 0);
    layoutGrid->addItem(lblPTS1, 2, 1);
    layoutGrid->addItem(iCntKilledTanks1, 2, 2);

    layoutGrid->addItem(iPTS2  , 3, 0);
    layoutGrid->addItem(lblPTS2, 3, 1);
    layoutGrid->addItem(iCntKilledTanks2, 3, 2);

    layoutGrid->addItem(iPTS3  , 4, 0);
    layoutGrid->addItem(lblPTS3, 4, 1);
    layoutGrid->addItem(iCntKilledTanks3, 4, 2);

    layoutGrid->addItem(iPTS4  , 5, 0);
    layoutGrid->addItem(lblPTS4, 5, 1);
    layoutGrid->addItem(iCntKilledTanks4, 5, 2);

    // imgs
    layoutGrid->addItem(imgTankEasy  , 2, 3);
    layoutGrid->addItem(imgTankMiddle, 3, 3);
    layoutGrid->addItem(imgTankSpeed , 4, 3);
    layoutGrid->addItem(imgTankHard  , 5, 3);

    // Player 2
    layoutGrid->addItem(lblPlayer2,   0, 5, 1, 2);
    layoutGrid->addItem(lblCntScore2, 1, 6);
    layoutGrid->addItem(iCntKilledTanks12, 2, 4);

    layoutGrid->addItem(iPTS12,   2, 5);
    layoutGrid->addItem(lblPTS12, 2, 6);
    layoutGrid->addItem(iCntKilledTanks22, 3, 4);

    layoutGrid->addItem(iPTS22,   3, 5);
    layoutGrid->addItem(lblPTS22, 3, 6);
    layoutGrid->addItem(iCntKilledTanks32, 4, 4);

    layoutGrid->addItem(iPTS32,   4, 5);
    layoutGrid->addItem(lblPTS32, 4, 6);
    layoutGrid->addItem(iCntKilledTanks42, 5, 4);

    layoutGrid->addItem(iPTS42,   5, 5);
    layoutGrid->addItem(lblPTS42, 5, 6);

    layoutGrid->addItem(imgWhiteLine, 6, 2, 1, 2);  // Белая линия

    layoutGrid->addItem(lblTotal, 7, 0, 1, 2);      // Надпись "Тотал"
    layoutGrid->addItem(lblTotalVal1, 7, 2);        // Общее количество убитых танков для Игрока 1
    layoutGrid->addItem(lblTotalVal2, 7, 4);        // Общее количество убитых танков для Игрока 2

    layoutGrid->setColumnFixedWidth(0, 70);         // Установка ширины равной 70 пикс для колонки с номером 0
    layoutGrid->setColumnFixedWidth(1, 30);
    layoutGrid->setColumnFixedWidth(2, 40);
    layoutGrid->setColumnFixedWidth(3, 40);
    layoutGrid->setColumnFixedWidth(4, 30);
    layoutGrid->setColumnFixedWidth(5, 60);
    layoutGrid->setColumnFixedWidth(6, 60);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->setSpacing(15);                         // Установка отступов между объектами
                                                    // в вертикальном компоновщике
    layout->setMinimumWidth(400);                   // Минимальная ширина компоновщика
    layout->setContentsMargins(40, 100, 0, 0);      // Отступы от границы
    layout->addItem(lblScore);                      // Добавление обьекта
    layout->addItem(lblStage);
    layout->addItem(layoutGrid);

    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(layout);
    scene->addItem(form);

    scene->setBackgroundBrush(QBrush("Black"));     // Закраска сцены в чёрный цвет
    view->setScene(scene);

    this->close();
    view->show();
}

void BattleCityView::slotKillBotStatistic()
{
    listTank[listTank.size()-1]->~QGraphicsPixmapItem();
    listTank.removeLast();
}

void BattleCityView::slotKillTankStatistic()
{
    if (m_txtCountLife->toPlainText() == "3")
    {
        m_txtCountLife->setPlainText("2");
    }
    else if (m_txtCountLife->toPlainText() == "2")
    {
        m_txtCountLife->setPlainText("1");
    }
    else
    {
        m_txtCountLife->setPlainText("0");
    }
}

void BattleCityView::slotLoadNextLevel()
{   
    map->timerShowNextLevel->stop();

    foreach (QGraphicsItem *item, map->items()) {
        if (!item->parentItem() //&& item != map->bot && item != map->bot_2 && item != map->bot_3 && item != map->bot_4
                /*&& item != map->TankForPlay1*/)
            map->removeItem(item);
    }

    if (map->m_iCountLevel == 1)
    {
         map->p_ReadFromFile->ParsTextFile(":/map/level_2.txt", map->n_Map, false);   // Завантаження карти з файлу
         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");

         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_2.txt");
    }
    else if (map->m_iCountLevel == 2)
    {
         map->p_ReadFromFile->ParsTextFile(":/map/level_3.txt", map->n_Map, false);   // Завантаження карти з файлу
         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");

         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_3.txt");
    }
    else if (map->m_iCountLevel == 3)
    {
         map->p_ReadFromFile->ParsTextFile(":/map/level_4.txt", map->n_Map, false);   // Завантаження карти з файлу
         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");

         map->bot->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_2->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_3->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
         map->bot_4->algorithmSearchWay->SetPathToMap(":/map/level_4.txt");
    }

    ShowWalls(OBJ_NAME_WATER     , OBJ_TYPE_WATER     , ":/walls/1.jpg");
    ShowWalls(OBJ_NAME_ICE       , OBJ_TYPE_ICE       , ":/walls/2.jpg");
    ShowWalls(OBJ_NAME_RED_WALL  , OBJ_TYPE_RED_WALL  , ":/walls/3.jpg");
    ShowWalls(OBJ_NAME_GRASS     , OBJ_TYPE_GRASS     , ":/walls/4.png");
    ShowWalls(OBJ_NAME_WHITE_WALL, OBJ_TYPE_WHITE_WALL, ":/walls/5.jpg");
   // ShowWalls(OBJ_NAME_BASE      , OBJ_TYPE_BASE      , ":/Explosion/base.png");
    ShowStatistic();

    ++map->bot->m_iCountLevel;
    ++map->bot_2->m_iCountLevel;
    ++map->bot_3->m_iCountLevel;
    ++map->bot_4->m_iCountLevel;

    emit map->signalShowLevel();
}
