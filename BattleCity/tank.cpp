#include "tank.h"

#include <QPixmap>
#include <QBitmap>

#include "constants.h"
#include "redwall.h"

Tank::Tank(const QList<QString> fileNames, QObject *parent) : QObject(parent),
    QGraphicsItem()
{
    currentFrame = 0;
    _speed       = 0;
    _shot        = true;
    _power       = 1;
    _numberKills = 0;
    collision    = false;
    _friendOrBattle = false;
    _searchWayNow = false;

    int size = fileNames.size();
    for (int i = 0; i < size; ++i) {
        QPixmap pixmap;
            pixmap.load(fileNames.at(i));
        Frame frame;
            frame.pixmap = pixmap;
            frame.shape = QPainterPath();
            frame.boundingRect = pixmap.rect();
            frames << frame;
    }
    _rotate = 180;

    iArrowUp    = Qt::Key_Up;
    iArrowDown  = Qt::Key_Down;
    iArrowRight = Qt::Key_Right;
    iArrowLeft  = Qt::Key_Left;
    iKeySpace   = Qt::Key_Space;
}

Tank::~Tank() {
    actions.clear();
    deleteLater();
}
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Tank::setRotate2(int rotate)
{
    switch (rotate)
    {
        case 0:
            {
                this->currentFrame = 4;
         break;
            }
        case 90:
            {
                this->currentFrame = 6;
        break;
            }
        case 180:
            {
                this->currentFrame = 0;
        break;
            }
        case 270:
            {
                this->currentFrame = 2;
        break;
            }
    }
    this->_rotate = rotate;

    scene()->update();
}

void Tank::LoadNewFrame(const QList<QString> &fileNames)
{
    frames.clear();
    int size = fileNames.size();
    for (int i = 0; i < size; i++) {
        QPixmap pixmap;
            pixmap.load(fileNames.at(i));
        Frame frame;
            frame.pixmap = pixmap;
            frame.shape = QPainterPath();
            frame.boundingRect = pixmap.rect();
            frames << frame;
    }
}

void Tank::setRotate(int r) {
    _rotate = r;
}

QRectF Tank::boundingRect() const {
    return QRectF(0, 0, 29, 29);
}

QPainterPath Tank::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());

    return path;
}

Bullet *Tank::shot() {
    QPoint pointStart;

    int x = this->x();
    int y = this->y();

    switch (this->_rotate) {
        case 0: {
            pointStart = QPoint(x+13, y-6);
            break;
        }
        case 90: {
            pointStart = QPoint(x+38, y+13);
            break;
        }
        case 180: {
            pointStart = QPoint(x+19, y+38);
            break;
        }
        case 270: {
            pointStart = QPoint(x-6, y+19);
            break;
        }
    }

    return (new Bullet(this->_power, pointStart, _rotate));
}

void Tank::slotTankShot(QString typeObject) {
    if (this->_shot == false)
        return;

    try
    {
        Bullet *bullet = this->shot();
        bullet->nameObjectSender = typeObject;
        bullet->setData(0, OBJ_NAME_BULLET);
        this->_shot = false;

        connect( bullet, SIGNAL( signalDestroy()  )  , this, SLOT( slotAllowShot() ));
        connect( bullet, SIGNAL( signalGameOver() )  , this, SLOT( slotGameOver()  ));
        connect( bullet, SIGNAL( signalKillBot()  )  , this, SLOT( slotKillBot()   ));

        scene()->addItem(bullet);

    } catch (QString *str)
    {
        qDebug() << "Good";
    }
}

void Tank::slotAllowShot() {
    this->_shot = true;
}

void Tank::slotGameOver()
{
    emit signalGameOver2();
}

void Tank::slotKillBot()
{
    ++_numberKills;
}

void Tank::slotMoveTank() {
    if (this->activeKey.isEmpty())
    {
        return;
    }

    int x = this->x();
    int y = this->y();

    int lastKey = this->activeKey.last();

    if (this->_friendOrBattle)
    {
       if (lastKey == this->iArrowDown)
       {
           lastKey = this->iArrowUp;
       }
       else if (lastKey == this->iArrowUp)
       {
           lastKey = this->iArrowDown;
       }
       else if (lastKey == iArrowLeft)
       {
           lastKey = this->iArrowRight;
       }
       else
       {
           lastKey = this->iArrowLeft;
       }
  }

    QPointF np;
    np.setX(0);
    np.setY(0);

    _speed = 2;                                   // Швидкість по замовчуванню
    QGraphicsItem *obstacleWithIce = itemCollidesWith(this);
    if (obstacleWithIce->data(0) == OBJ_NAME_ICE)           // Якщо танк їде по льоду,
        this->_speed = 2;                                   // тоді він має "сковзатися"

    qDebug() << "lastKey = " << lastKey;
    if (lastKey == this->iArrowUp)
    {
        this->setY(y - this->_speed);
        this->currentFrame = (this->currentFrame != 4) ? 4 : 5;
        this->_rotate = 0;
        np.setY(-this->_speed);

    }
    else if (lastKey == this->iArrowDown)
    {
        this->setY(y + this->_speed);
        this->currentFrame = (this->currentFrame != 0) ? 0 : 1;
        this->_rotate = 180;
        np.setY(this->_speed);
    }
    else if (lastKey == this->iArrowRight)
    {
        this->setX(x + this->_speed);
        this->currentFrame = (this->currentFrame != 6) ? 6 : 7;
        this->_rotate = 90;
        np.setX(this->_speed);
    }
    else if (lastKey == this->iArrowLeft)
    {
        this->setX(x - this->_speed);
        this->currentFrame = (this->currentFrame != 2) ? 2 : 3;
        this->_rotate = 270;
        np.setX(-this->_speed);
    }

    x = this->x();
    y = this->y();

    if (
         (x+33)  > WINDOW_WIDTH   ||
         (y+33)  >= WINDOW_HEIGHT ||
         (x < 0) || (y < 0)
        )
    {
        this->moveBy(-np.x(), -np.y());
    }

    QList<QGraphicsItem *> obstacle = scene()->collidingItems(this);
    foreach (QGraphicsItem *it, obstacle) {
        if (it == this)
            continue;

        if (
            it->data(0)  == OBJ_NAME_BOT_1 ||
            it->data(0)  == OBJ_NAME_BOT_2 ||
            it->data(0)  == OBJ_NAME_BOT_3 ||
            it->data(0)  == OBJ_NAME_BOT_4
           )
        {
            this->moveBy(-np.x(), -np.y());
        }

        if (
            it->data(0)  == OBJ_NAME_WATER      ||
            it->data(0)  == OBJ_NAME_WHITE_WALL ||
            it->data(0)  == OBJ_NAME_PLAYER_1   ||
            it->data(0)  == OBJ_NAME_PLAYER_2

          )
         {
            this->moveBy(-np.x(), -np.y());
         }
         else if (it->data(0)  == OBJ_NAME_RED_WALL)
         {
             this->moveBy(-np.x(), -np.y());
         }

        if (it->data(0) == OBJ_NAME_STAR)
        {
            ++this->_power;
            emit signalTankTookStar();
        }
        else if (it->data(0) == OBJ_NAME_BASE_BONUS)
        {
            emit signalBuildProtectionForBase();
        }
        else if (it->data(0) == OBJ_NAME_TIME_BONUS)
        {
            emit signalStopAllBots();

        } else if (it->data(0) == OBJ_NAME_EXPLOSION_BONUS)
        {
            emit signalExplosionAllBots();
        }
    }
    scene()->update();
}

QGraphicsItem *Tank::itemCollidesWith(QGraphicsItem *item) {
    QList<QGraphicsItem *> collisions = scene()->collidingItems(item);
    foreach (QGraphicsItem *it, collisions) {
        if (it == item)
            continue;
        return it;
    }

    return NULL;
}
