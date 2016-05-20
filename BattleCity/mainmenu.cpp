#include "mainmenu.h"
#include <QGraphicsLinearLayout>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QGraphicsGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QListWidget>
#include "udpclient.h"
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QFontComboBox>

mainMenu::mainMenu(): id_elementOfMenu(1) {
    scene = new QGraphicsScene();

    _friend = false;

    scene->setSceneRect(0, 0, 512, 512);
    this->setFixedSize(512, 512);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    showMainMenu();

    this->setScene(scene);
    this->move(400,0);
    this->show();

    btnServer = new QPushButton("create server");
    btnClient = new QPushButton("create client");

    btnConnect   = new QPushButton("connect");
    btnStartGame = new QPushButton("start");
    btnUpdate    = new QPushButton("update");

    btnChooiseServer = new QPushButton("server");
    btnChooiseClient = new QPushButton("client");

    QObject::connect(btnChooiseServer, SIGNAL(clicked(bool)), this, SLOT(slotCreateServer()));
    QObject::connect(btnChooiseClient, SIGNAL(clicked(bool)), this, SLOT(slotCreateClient()));

    QObject::connect(btnServer, SIGNAL(clicked(bool)), this, SLOT(slotRunServer()));
    QObject::connect(btnClient, SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer()));

    QObject::connect(btnUpdate, SIGNAL(clicked(bool)), this, SLOT(slotSendMessageConnectToServer()));   // послать сообщения серверу

    QObject::connect(btnConnect,   SIGNAL(clicked(bool)), this, SLOT(slotStartGameClient()));
    QObject::connect(btnStartGame, SIGNAL(clicked(bool)), this, SLOT(slotStartGameServer()));
}

mainMenu::~mainMenu() {}

void mainMenu::keyPressEvent(QKeyEvent *event) {
    if (id_elementOfMenu == 4)
        QGraphicsView::keyPressEvent(event);

    switch (event->key()) {
        case Qt::Key_Up: {
                if (id_elementOfMenu == 1 || id_elementOfMenu == 6)
                    return;
                --id_elementOfMenu;
                lblImgGraph->setY(lblImgGraph->y() - 26);
            break;
        }

        case Qt::Key_Down: {
            if (id_elementOfMenu == 5 || id_elementOfMenu == 7)
                return;
            ++id_elementOfMenu;
            lblImgGraph->setY(lblImgGraph->y() + 26);
            break;
        }

        case Qt::Key_Space: {
                if (id_elementOfMenu < 6) {             // Если находимся в главном меню
                    switch (id_elementOfMenu) {         // тогда выбор среди 5 элементов
                        case 1: // 1 Player
                                playOnePlayer();
                            break;
                        case 2: // 2 Player
                                playTwoPlayers();
                            break;
                        case 3: // Multiply
                                showMultiply();
                            break;
                        case 4: // Options
                                showOptions();
                            break;
                        case 5: // Exit
                               this->close();
                            break;
                    }
                } else if (id_elementOfMenu < 8) {      // Под меню для пункта Multiply
                    switch (id_elementOfMenu) {
                        case 6:
                                qDebug() << "LAN loading...";
                                // lan();
                                Lan();
                            break;
                        case 7:
                                qDebug() << "Network loading...";
                                // network();
                            break;
                    }
                }
            break;
        }
        case Qt::Key_Escape:
                showMainMenu();
            break;
    }
}

void mainMenu::Lan()
{
    chooiseClientOrServer = new QGraphicsView;
    QVBoxLayout   *vLayout = new QVBoxLayout;

    vLayout->addWidget(btnChooiseServer);
    vLayout->addWidget(btnChooiseClient);
    chooiseClientOrServer->setLayout(vLayout);

    this->close();
    chooiseClientOrServer->setFixedSize(150, 100);
    chooiseClientOrServer->setWindowTitle("chooise");
    chooiseClientOrServer->show();
}

void mainMenu::playOnePlayer() {
    // Передать количества игроков
    ShowGame(1);
}

void mainMenu::ShowGame(int regimeGame)
{
    UdpClient *udp = new UdpClient("", "", "");

    view = new BattleCityView(regimeGame, true, udp);
    this->close();
    view->move(400,0);
    view->show();
}

void mainMenu::playTwoPlayers()
{    // Передать количества игроков
    viewRunTwoPlayer = new QGraphicsView;

    QPushButton* btnFriend  = new QPushButton("friend");
    QPushButton* btnBattle  = new QPushButton("battle");
    QVBoxLayout* headLayout = new QVBoxLayout;

    headLayout->addWidget(btnFriend);
    headLayout->addWidget(btnBattle);

    viewRunTwoPlayer->setLayout(headLayout);

    viewRunTwoPlayer->setFixedSize(200, 100);
    viewRunTwoPlayer->show();

    QObject::connect( btnFriend, SIGNAL( clicked(bool) ), this, SLOT( slotRunGameFriend() ));
    QObject::connect( btnBattle, SIGNAL( clicked(bool) ), this, SLOT( slotRunGameBattle() ));

   // ShowGame(2);
}

void mainMenu::showMultiply() {
    id_elementOfMenu = 6;
    scene->clear();
    QGraphicsLinearLayout *pLinearLayout = new QGraphicsLinearLayout(Qt::Vertical);

    QGraphicsWidget *lblLAN   = scene->addWidget(new QLabel("LAN"));
    QGraphicsWidget *lblNetwork  = scene->addWidget(new QLabel("Network"));

    QPalette palette = lblLAN->palette();
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));

    const int fontSize = 12;
    lblLAN->setPalette(palette);
    lblLAN->setFont(QFont("M10_BATTLE CITIES", fontSize));

    QLabel *lblImg = new QLabel();
    lblImg->setPixmap(QPixmap(":/img/tank.png"));

    lblImgGraph = scene->addWidget(lblImg);             // Добавленния виджета на сцену
    lblImgGraph->setPalette(palette);                   // Установка чёрного фона картинки

    lblNetwork->setPalette(lblLAN->palette());
    lblNetwork->setFont(lblLAN->font());

    pLinearLayout->addItem(lblLAN);                     // Добавление объектов на вертикальный layout
    pLinearLayout->addItem(lblNetwork);

    pLinearLayout->setSpacing(10);                      // Отступ между объектами в layout

    scene->setBackgroundBrush(QBrush(QPixmap(":/img/background.png"))); // Установка фона сцены

    pLinearLayout->setContentsMargins(180, 270, 0, 0);  // Установка отступов
    lblImgGraph->setPos(130, 262);                      // Установка позиции желтого танка

    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(pLinearLayout);
    scene->addItem(form);
}

void mainMenu::showOptions() {
    scene->clear();
    scene->setBackgroundBrush(QBrush(QColor(Qt::black)));

    QGraphicsGridLayout *grid = new QGraphicsGridLayout();
    grid->setSpacing(10);

    QGraphicsWidget *lblPlayer1 = scene->addWidget(new QLabel("Name of Player1"));
    QGraphicsWidget *lblPlayer2 = scene->addWidget(new QLabel("Name of Player2"));
    QGraphicsWidget *lblNamePlayer1 = scene->addWidget(new QLineEdit("Player1"));
    QGraphicsWidget *lblNamePlayer2 = scene->addWidget(new QLineEdit("Player2"));

    const int fontSize = 12;
    lblNamePlayer1->setMinimumWidth(200);
    lblNamePlayer2->setMinimumWidth(200);

    lblNamePlayer1->setFont(QFont("M10_BATTLE CITIES", fontSize));
    lblNamePlayer2->setFont(QFont("M10_BATTLE CITIES", fontSize));

    QPalette palette = lblPlayer1->palette();
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));


    lblPlayer1->setPalette(palette);
    lblPlayer1->setFont(QFont("M10_BATTLE CITIES", fontSize));
    lblPlayer2->setPalette(palette);
    lblPlayer2->setFont(QFont("M10_BATTLE CITIES", fontSize));

    grid->addItem(lblPlayer1    , 0, 0);
    grid->addItem(lblNamePlayer1, 0, 1);
    grid->addItem(lblPlayer2    , 1, 0);
    grid->addItem(lblNamePlayer2, 1, 1);

    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(grid);
    scene->addItem(form);
}

void mainMenu::showMainMenu() {
    scene->clear();
    id_elementOfMenu = 1;

    QGraphicsLinearLayout *pLinearLayout = new QGraphicsLinearLayout(Qt::Vertical);
    // Пункты меню главного меню
    QGraphicsWidget *lblOnePlayer   = scene->addWidget(new QLabel("1 Player"));
    QGraphicsWidget *lblTwoPlayers  = scene->addWidget(new QLabel("2 Players"));
    QGraphicsWidget *lblNetwork     = scene->addWidget(new QLabel("Multiplayer"));
    QGraphicsWidget *lblOptions     = scene->addWidget(new QLabel("Options"));
    QGraphicsWidget *lblExit        = scene->addWidget(new QLabel("Exit"));

    QPalette palette = lblOnePlayer->palette();
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));

    const int fontSize = 12;
    lblOnePlayer->setPalette(palette);
    lblOnePlayer->setFont(QFont("M10_BATTLE CITIES", fontSize));

    QLabel *lblImg = new QLabel();
    lblImg->setPixmap(QPixmap(":/img/tank.png"));

    lblImgGraph = scene->addWidget(lblImg);             // Добавленния виджета на сцену
    lblImgGraph->setPalette(palette);                   // Установка чёрного фона картинки

    lblTwoPlayers->setPalette(lblOnePlayer->palette());
    lblTwoPlayers->setFont(lblOnePlayer->font());

    lblNetwork->setPalette(lblOnePlayer->palette());
    lblNetwork->setFont(lblOnePlayer->font());

    lblOptions->setPalette(lblOnePlayer->palette());
    lblOptions->setFont(lblOnePlayer->font());

    lblExit->setPalette(lblOnePlayer->palette());
    lblExit->setFont(lblOnePlayer->font());

    pLinearLayout->addItem(lblOnePlayer);               // Добавление объектов на вертикальный layout
    pLinearLayout->addItem(lblTwoPlayers);
    pLinearLayout->addItem(lblNetwork);
    pLinearLayout->addItem(lblOptions);
    pLinearLayout->addItem(lblExit);

    pLinearLayout->setSpacing(10);                      // Отступ между объектами в layout

    scene->setBackgroundBrush(QBrush(QPixmap(":/img/background.png"))); // Установка фона сцены

    pLinearLayout->setContentsMargins(180, 270, 0, 0);  // Установка отступов
    lblImgGraph->setPos(130, 262);                      // Установка позиции желтого танка

    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(pLinearLayout);
    scene->addItem(form);

//    this->setFocus();
}

void mainMenu::slotCreateServer()
{
    viewServer = new QGraphicsView;
    QLabel *lblNameServer = new QLabel("name server");
    QLabel *lblIpServer   = new QLabel("ip server");
    cmbFriendGame = new QComboBox;
    cmbFriendGame->addItem("friend");
    cmbFriendGame->addItem("battle");

    editNameServer = new QLineEdit;

    QRegExp rex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
    QValidator *validator = new QRegExpValidator(rex, this);
    editIpServer   = new QLineEdit;
    editIpServer->setValidator(validator);

    QVBoxLayout *headLayout        = new QVBoxLayout;
    QHBoxLayout *hLayoutNameServer = new QHBoxLayout;
    QHBoxLayout *hLayoutIpServer   = new QHBoxLayout;

    hLayoutNameServer->addWidget(lblNameServer);
    hLayoutNameServer->addWidget(editNameServer);

    hLayoutIpServer->addWidget(lblIpServer);
    hLayoutIpServer->addSpacing(25);
    hLayoutIpServer->addWidget(editIpServer);

    headLayout->addLayout(hLayoutNameServer);
    headLayout->addLayout(hLayoutIpServer);
    headLayout->addWidget(cmbFriendGame);
    headLayout->addWidget(btnServer);

    viewServer->setWindowTitle("creating server");
    viewServer->setLayout(headLayout);

    chooiseClientOrServer->close();
    viewServer->show();
}

void mainMenu::slotCreateClient()
{
    viewClient = new QGraphicsView;
    QLabel *lblIpServer = new QLabel("ip server");
    QLabel *lblIpClient = new QLabel("ip client");

    QRegExp rex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
    QValidator *validator = new QRegExpValidator(rex, this);

    editIpServer = new QLineEdit;
    editIpServer->setValidator(validator);

    editIpClient = new QLineEdit;
    editIpClient->setValidator(validator);

    QVBoxLayout *headLayout = new QVBoxLayout;
    QHBoxLayout *hLayoutIpServer = new QHBoxLayout;
    QHBoxLayout *hLayoutIpClient   = new QHBoxLayout;

    hLayoutIpServer->addWidget(lblIpServer);
    hLayoutIpServer->addSpacing(20);
    hLayoutIpServer->addWidget(editIpServer);

    hLayoutIpClient->addWidget(lblIpClient);
    hLayoutIpClient->addSpacing(25);
    hLayoutIpClient->addWidget(editIpClient);

    headLayout->addLayout(hLayoutIpServer);
    headLayout->addLayout(hLayoutIpClient);
    headLayout->addWidget(btnClient);

    viewClient->setWindowTitle("creating client");
    viewClient->setLayout(headLayout);

    chooiseClientOrServer->close();
    viewClient->show();
}

void mainMenu::slotRunServer()
{
    if (editIpServer->text() == "" || editNameServer->text() == "")
    {
        QMessageBox::critical(0, "error", "not correct value");
        return;
    }

    if (cmbFriendGame->currentText() == "friend")
    {
        _friend = true;
    }

    QString ipServer;
    QString nameServer;

    ipServer = editIpServer->text();
    nameServer = editNameServer->text();

    server = new UdpClient(nameServer, ipServer, "");
    server->server = true;

    list   = new QListWidget;

    viewRunServer = new QGraphicsView;
    QHBoxLayout   *headLayout    = new QHBoxLayout;

    list->addItem(nameServer);
    list->setFixedSize(100, 100);
    headLayout->addWidget(list);
    headLayout->addWidget(btnStartGame);

    viewRunServer->setLayout(headLayout);
    viewRunServer->setFixedSize(250, 120);
    viewRunServer->setWindowTitle("server");

    viewServer->close();
    viewRunServer->show();
}

void mainMenu::slotConnectToServer()
{
    if (editIpServer->text() == "" || editIpClient->text() == "")
    {
        QMessageBox::critical(0, "error", "not correct value");
        return;
    }

    QString strIpServer;
    QString strIpClient;

    strIpServer = editIpServer->text();
    strIpClient = editIpClient->text();

    client = new UdpClient("", strIpClient, strIpServer);
    client->server = false;

    list = new QListWidget;

    viewConnectToServer = new QGraphicsView;
    QHBoxLayout   *headLayout          = new QHBoxLayout;
    QVBoxLayout   *vLayout             = new QVBoxLayout;

    list->setFixedSize(100, 100);
    headLayout->addWidget(list);

    vLayout->addWidget(btnUpdate);
    vLayout->addWidget(btnConnect);

    headLayout->addLayout(vLayout);

    viewConnectToServer->setLayout(headLayout);
    viewConnectToServer->setFixedSize(250, 120);
    viewConnectToServer->setWindowTitle("client");

    viewClient->close();
    viewConnectToServer->show();

    QObject::connect(client, SIGNAL(signalConnectExecute(QString)), this, SLOT(slotReadNameServer(QString)));
}

void mainMenu::slotSendMessageConnectToServer()
{
    client->SendIpClient();
}

void mainMenu::slotReadNameServer(QString nameServer)
{
    list->addItem(nameServer);
}

void mainMenu::slotStartGameClient()
{
    if (list->count() == 0)
    {
        QMessageBox::critical(0, "error", "server not found");
        return;
    }

    view = new BattleCityView(4, _friend, client);
    viewConnectToServer->close();
    view->move(400,0);

    view->show();
}

void mainMenu::slotRunGameBattle()
{
    UdpClient *udp = new UdpClient("", "", "");

    view = new BattleCityView(2, false, udp);
    this->close();
    view->move(400,0);
    viewRunTwoPlayer->close();
    view->show();
}

void mainMenu::slotRunGameFriend()
{
    ShowGame(2);
    viewRunTwoPlayer->close();
}

void mainMenu::slotStartGameServer()
{
    if (server->_strIpForSend == "")
    {
        QMessageBox::critical(this, "error", "not found client \n"
                                             "please connect and again");
        return;
    }

    view = new BattleCityView(3, _friend, server);
    viewRunServer->close();
    view->move(400,0);

    if (!_friend)
    {
        view->rotate(180);
    }

    view->show();
}
