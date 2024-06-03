#include "widget.h"
#include "ui_widget.h"
#include "qpainter.h"
#include "QKeyEvent"
#include "game.h"
#include "QRect"
#include "centipede.h"
#include "bodypart.h"
#include "typeDef.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    isGameStarted = false;
    connect(ui->playButton , SIGNAL(clicked()), this, SLOT(startGame()));
    // Create and start the timer for updating the GUI, the centipede, the bullet, the player
    itsDisplayTimer = new QTimer(this);
    itsCentipedeTimer = new QTimer(this);
    itsBulletTimer = new QTimer(this);
    itsPlayerTimer = new QTimer(this);
    //loading of the images
    itsCentiBody.load("../imageDoss/centibody.png");
    itsCentiHead.load("../imageDoss/centihead.png");
    itsAvatar.load("../imageDoss/avatar.png");
    itsMushrooms.load("../imageDoss/mushrooms.png");

    connect(itsDisplayTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(itsPlayerTimer, SIGNAL(timeout()), this, SLOT(movePlayer()));
    connect(itsBulletTimer, SIGNAL(timeout()), this, SLOT(moveBullet()));
    connect(itsCentipedeTimer, SIGNAL(timeout()), this, SLOT(moveCentipede()));
}

Widget::~Widget()
{
    delete ui;
    delete itsBulletTimer;
    delete itsCentipedeTimer;
    delete itsDisplayTimer;
    delete itsPlayerTimer;
    delete itsGame;
}

void Widget::paintEvent(QPaintEvent *event)
{
    if(isGameStarted)
    {
        Q_UNUSED(event); //pour éviter les avertissements du compilateur concernant des variables non utilisées
        QPainter painter(this);
        // Draw the Bricks and the avatar
        drawCentipede(painter);
        drawPlayer(painter);
        drawBullet(painter);
        drawMushrooms(painter);
    }
}


void Widget::drawCentipede(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for (auto it = itsGame->getItsCentipedes()->begin(); it != itsGame->getItsCentipedes()->end(); ++it) {
        BodyPart * currentPart = (*it)->getItsHead();
        while(currentPart != nullptr)
        {
            if(currentPart != (*it)->getItsHead())
            {
                //display the bodys
                painter.drawImage(currentPart->getItsHitBox(), itsCentiBody);
            }
            else
            {
                //display the head
                painter.drawImage(currentPart->getItsHitBox(), itsCentiHead);
            }
            currentPart = currentPart->getItsChild();
        }
        delete currentPart;
    }
}

void Widget::drawBullet(QPainter & painter)
{
    painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
}

void Widget::drawPlayer(QPainter & painter)
{
    //à compléter avec le liens
    painter.drawImage(itsGame->getItsPlayer()->getItsHitBox(), itsAvatar);
}

void Widget::drawMushrooms(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for(auto it = itsGame->getItsMushrooms()->begin(); it !=  itsGame->getItsMushrooms()->end(); ++it)
    {
        painter.drawImage((*it)->getItsHitBox(), itsMushrooms);
    }
}

void Widget::movePlayer(QKeyEvent * event)
{
    // Handle key press events for left and right arrow keys
    if (event->key() == Qt::Key_Z)
    {
        Direction dir;
        dir.dirX = -1;
        dir.dirY = 0;
        itsGame->getItsPlayer()->updatePos(dir);
    }
    if (event->key() == Qt::Key_Q)
    {
        Direction dir;
        dir.dirX = 0;
        dir.dirY = -1;
        itsGame->getItsPlayer()->updatePos(dir);
    }
    if (event->key() == Qt::Key_S)
    {
        Direction dir;
        dir.dirX = 1;
        dir.dirY = 0;
        itsGame->getItsPlayer()->updatePos(dir);
    }
    if (event->key() == Qt::Key_D)
    {
        Direction dir;
        dir.dirX = 0;
        dir.dirY = 1;
        itsGame->getItsPlayer()->updatePos(dir);
    }
    if (event->key() == Qt::Key_Space)
    {
        itsGame->shoot();
    }
}

void Widget::moveBullet()
{
    itsGame->getItsBullet()->updatePos();
}

void Widget::startGame()
{
    ui->stackedWidget->setCurrentIndex(0); // j'ai mis 0 mais jsp trop lequel c'est
    itsGame = new Game();
    isGameStarted = true;
    itsDisplayTimer->start(16); // Update every 16 equal approximatly to 60fps    itsAvatarTimer->start(2500/this->width());
    itsBulletTimer->start(1); // set the speed of it
    itsCentipedeTimer->start(1); // set the speed of it
    itsPlayerTimer->start(1); // set the speed of it
    setFixedSize(this->width(), this->height()); // set the size of the window
}
