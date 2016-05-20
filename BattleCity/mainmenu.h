#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>

#include "battlecityview.h"
#include "udpclient.h"

class mainMenu: public QGraphicsView
{
    Q_OBJECT
public:
    mainMenu();
    void ShowGame(int regimeGame);  // создание обьекта карты
    void Lan();                     // игра по сети
    ~mainMenu();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsScene  *scene;
    QGraphicsWidget *lblImgGraph;

    BattleCityView  *view;                  // карта игры
    QGraphicsView   *chooiseClientOrServer; // меню выбора создание клиента или сервера
    QGraphicsView   *viewServer;            // создание сервера
    QGraphicsView   *viewClient;            // создание клиента
    QGraphicsView   *viewConnectToServer;
    QGraphicsView   *viewRunServer;
    QGraphicsView   *viewRunTwoPlayer;

    QPushButton   *btnChooiseServer;
    QPushButton   *btnChooiseClient;

    QPushButton   *btnServer;
    QPushButton   *btnClient;

    QPushButton   *btnStartGame;
    QPushButton   *btnUpdate;
    QPushButton   *btnConnect;

    QLineEdit *editNameServer;
    QLineEdit *editIpServer;
    QLineEdit *editIpClient;

    QLineEdit *editIpClient2;

    QListWidget *list;                       // отображение именни сервера

    UdpClient *client;
    UdpClient *server;

    QComboBox *cmbFriendGame;
    bool _friend;

    int id_elementOfMenu;

    void playOnePlayer();
    void playTwoPlayers();
    void showMultiply();
    void showOptions();
    void showMainMenu();

public slots:
    void slotCreateServer();                        // создание сервера
    void slotCreateClient();                        // создание клиента

    void slotRunServer();                           // запуск сервера
    void slotConnectToServer();                     // соединение с сервером

    void slotSendMessageConnectToServer();          // отправка первого сообщения клиентом
    void slotReadNameServer(QString nameServer);    // чтение именни сервера

    void slotStartGameServer();                     // старт игры как сервер
    void slotStartGameClient();                     // старт игры как клиент
    void slotRunGameFriend();
    void slotRunGameBattle();
};

#endif // MAINMENU_H
