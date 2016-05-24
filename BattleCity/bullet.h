#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(int tempPowerTank, QPointF start, int angle, QObject *parent = 0);
    explicit Bullet(int tempPowerTank, QPointF start, int angle, int speed, QObject *parent = 0);
    ~Bullet();

    void SetSpeed(const int& speed);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QTimer *timerBullet;
    int _speed;
    int powerTank;

public:
    QString nameObjectSender;

private slots:
    void slotTimerBullet(); // Слот для обработки полёта пули

signals:
    void signalDestroy();
    void signalGameOver();
    void signalKillBot();

};

#endif // BULLET_H

