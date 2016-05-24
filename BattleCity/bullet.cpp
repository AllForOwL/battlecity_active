#include "bullet.h"
#include <QGraphicsScene>
#include "constants.h"
#include <QDebug>
#include "tankforplayer.h"
#include "redwall.h"
#include "sprite.h"
#include <QMessageBox>
#include <QException>
#include <signal.h>

Bullet::Bullet(int tempPowerTank, QPointF start, int angle, QObject *parent):  QObject(parent),
                                                            QGraphicsItem()
{
    powerTank = tempPowerTank;
    _speed = -2;                                                    // Швидкість руху пулі
    this->setRotation(angle);                                       // Сторона польоту
    this->setPos(start);                                            // Початкова позиції пулі
    timerBullet = new QTimer();
    connect(timerBullet, SIGNAL(timeout()), SLOT(slotTimerBullet()));   // Таймер, який переміщує пулю
    timerBullet->start(1);                                         // Швидкість обновлення таймеру. 15 млсек.
                                                                    // 1 сек == 1000 млсек
}

Bullet::Bullet(int tempPowerTank, QPointF start, int angle, int speed, QObject *parent):  QObject(parent),
                                                            QGraphicsItem()
{
    powerTank = tempPowerTank;
    _speed = speed * (-1);                                                    // Швидкість руху пулі
    this->setRotation(angle);                                       // Сторона польоту
    this->setPos(start);                                            // Початкова позиції пулі
    timerBullet = new QTimer();
    connect(timerBullet, SIGNAL(timeout()), SLOT(slotTimerBullet()));   // Таймер, який переміщує пулю
    timerBullet->start(1);                                         // Швидкість обновлення таймеру. 15 млсек.
                                                                    // 1 сек == 1000 млсек
}

Bullet::~Bullet() {
    emit signalDestroy();
    delete timerBullet;
}

void Bullet::SetSpeed(const int &speed)
{
    _speed = speed;
}

QRectF Bullet::boundingRect() const {                               // Повертаємо прямокутник(квадрат) пулі, для того, щоб
    return QRectF(0, 0, 6, 6);                                      // можна було обробити зіткнення з іншими об’єктами
}

void Bullet::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    painter->setPen(Qt::black);                                     // Контур пулі - Чорний
    painter->setBrush(Qt::gray);                                    // Фон пулі - Сірий
    painter->drawRect(0, 0, 6, 6);                                  // Розміри пулі - 6х6

    Q_UNUSED(option);                                               // Позначаємо не використовуванні змінні
    Q_UNUSED(widget);
}

void Bullet::slotTimerBullet() {
    setPos(mapToParent(0, _speed));                                 // Переміщуємо пулю. _speed - швидкість пулі

    int x = this->x();
    int y = this->y();

    QList<QGraphicsItem *> array = scene()->collidingItems(this);   // В array містяться об’єкти


        // з якими зіткнулася пуля
    QPointF point(x, y);
    QRectF  tankExplosionF  (-25, -25, 50, 50);
    QRectF  baseExplosionF  (-20, -20, 40, 40);
    QRectF  bigExplosionF   (-16, -16, 32, 32);
    QRectF  smallExplosionF (-10, -10, 20, 20);
    Sprite  *explosion;


    if(!array.isEmpty()) {
        foreach (QGraphicsItem *it, array) {
            if ( it->data(0) == OBJ_NAME_GRASS ||                   // Перераховуємо назви об’єктів
                 it->data(0) == OBJ_NAME_ICE   ||                   // повз яких пуля пролітає і не
                 it->data(0) == OBJ_NAME_STAR                       // наносить збиток
            ) {
                continue;
            }
                qDebug() << it->data(0);
            if (it->data(0) == OBJ_NAME_BULLET) {                   // Якщо пуля попадає в пулю, тоді їх потрібно знищити
                Bullet *rw = dynamic_cast<Bullet *>(it);            // Перетворюємо в Bullet,
                rw->deleteLater();                                  // щоб викликати деструктор
                this->deleteLater();

                return;
            }
            else if (
                     (it->data(0) == OBJ_NAME_RED_WALL)
                    )
            {                                                       // Якщо пуля попадає в "Червону стіну"
                RedWall *rw = dynamic_cast<RedWall *>(it);          // тоді нам потрібно зчитати напрям пулі
                rw->directShot = this->rotation();                  // для того, щоб нанести збиток відповідній стороні стіни.
                if (rw->checkForRemove) {                           // Якщо об’єкт знищений візуально, тоді нам потрібно
                    scene()->removeItem(it);                        // його видалити зі сцени
                }

                if (array.size() == 2)
                {
                    explosion = new Sprite(point, PATH_TO_BIG_EXPLOSION, bigExplosionF);
                } else
                {
                    explosion = new Sprite(point, PATH_TO_SMALL_EXPLOSION, smallExplosionF);
                }
                scene()->addItem(explosion);

                this->deleteLater();
                continue;                                           // Продовжуємо обробляти інші об’єкти
                                                                    // з якими зіткнулась пуля
            }
            else if (
                     (it->data(0) == OBJ_NAME_WHITE_WALL) &&
                     (powerTank <= 3)
                    )
            {
                                                                     // Якщо пуля зіткнулася з "Білою стіною"
                if (array.size() == 2)
                {
                    explosion = new Sprite(point, PATH_TO_MINI_EXPLOSION, bigExplosionF);

                } else
                {
                    explosion = new Sprite(point, PATH_TO_SMALL_MINI__EXPLOSION, smallExplosionF);
                }
                scene()->addItem(explosion);

                this->deleteLater();
                continue;
                                                            // і продовжити обробку інших об’єктів з якими зіткнулася пуля
            } else if (
                       (it->data(0) == OBJ_NAME_WHITE_WALL) &&
                       (powerTank >= 3)                     &&
                       ((nameObjectSender == OBJ_NAME_PLAYER_1) ||
                        (nameObjectSender == OBJ_NAME_PLAYER_2))

                      )
            {
                RedWall *rw = dynamic_cast<RedWall *>(it);          // тоді нам потрібно зчитати напрям пулі
                rw->directShot = this->rotation();                  // для того, щоб нанести збиток відповідній стороні стіни.
                if (rw->checkForRemove) {                           // Якщо об’єкт знищений візуально, тоді нам потрібно
                    scene()->removeItem(it);                        // його видалити зі сцени
                }

                if (array.size() == 2)
                {
                    explosion = new Sprite(point, PATH_TO_MINI_EXPLOSION, bigExplosionF);
                } else
                {
                    explosion = new Sprite(point, PATH_TO_SMALL_MINI__EXPLOSION, smallExplosionF);
                }
                scene()->addItem(explosion);

                this->deleteLater();
                continue;                                           // Продовжуємо обробляти інші об’єкти
            } else if (
                       (it->data(0) == OBJ_NAME_PLAYER_1) ||
                       (it->data(0) == OBJ_NAME_PLAYER_2)
                      )
            {
                explosion = new Sprite(point, PATH_TO_TANK_EXPLOSION, tankExplosionF);
                scene()->addItem(explosion);

                this->deleteLater();
                TankForPlayer *rw = dynamic_cast<TankForPlayer *>(it);

                if (rw->getNumberLife() != 0)
                {qDebug() << "set begin position";
                    rw->setNumberLife();
                    rw->setInBeginPosition();
                }
                else
                {qDebug() << "game ove";
                    rw->signalGameOver();
                    rw->~TankForPlayer();
                }
                break;
            } else if (it->data(0) == OBJ_NAME_BASE)
            {
                explosion = new Sprite(point, PATH_TO_BASE_EXPLOSION, baseExplosionF);
                scene()->addItem(explosion);

                QGraphicsItem *tempPixmap = scene()->addPixmap(QPixmap(":/Explosion/destroyedBase.png"));
                tempPixmap->setPos(this->x(), this->y() - 10);

                emit signalGameOver();

                this->deleteLater();
                scene()->removeItem(it);
                continue;

            } else if (
                       (
                        ( it->data(0) == OBJ_NAME_BOT_1 ) ||
                        ( it->data(0) == OBJ_NAME_BOT_2 ) ||
                        ( it->data(0) == OBJ_NAME_BOT_3 ) ||
                        ( it->data(0) == OBJ_NAME_BOT_4 )
                       ) && (nameObjectSender == OBJ_NAME_PLAYER_1)
                      )
            {

                explosion = new Sprite(point, PATH_TO_TANK_EXPLOSION, tankExplosionF);
                scene()->addItem(explosion);

                emit signalKillBot();

                this->deleteLater();
                TankBot *rw = dynamic_cast<TankBot *>(it);
                rw->setPos(-32, 0);
                rw->destroyed();

                break;
            }

}

    }
    else if (
            x < 0   || x > WINDOW_WIDTH ||  // Якщо поля виходить
            y < 0   || y > WINDOW_HEIGHT    // за межі вікна,
    ) {
        this->deleteLater();                // тоді її потрібно знищити.
    }
}



