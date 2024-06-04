#include "widget.h"
#include "ui_widget.h"

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

    //initialize direction
    itsPlayerDirection = {0, 0};

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
        //drawCentipede(painter);
        drawPlayer(painter);
        //drawBullet(painter);
        //drawMushrooms(painter);
    }
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    // Handle key press events for left and right arrow keys
    if (event->key() == Qt::Key_Z)
    {
        itsPlayerDirection.dirY = -1;
    }
    if (event->key() == Qt::Key_Q)
    {
        itsPlayerDirection.dirX = -1;
    }
    if (event->key() == Qt::Key_S)
    {
        itsPlayerDirection.dirY = 1;
    }
    if (event->key() == Qt::Key_D)
    {
        itsPlayerDirection.dirX = 1;
    }
    if (event->key() == Qt::Key_Space)
    {
        itsGame->shoot();
    }
}

void Widget::keyReleaseEvent(QKeyEvent * event)
{
    // Handle key press events for left and right arrow keys
    if (event->key() == Qt::Key_Z)
    {
        itsPlayerDirection.dirY = 0;
    }
    if (event->key() == Qt::Key_Q)
    {
        itsPlayerDirection.dirX = 0;
    }
    if (event->key() == Qt::Key_S)
    {
        itsPlayerDirection.dirY = 0;
    }
    if (event->key() == Qt::Key_D)
    {
        itsPlayerDirection.dirX = 0;
    }
}

void Widget::drawPlayer(QPainter & painter)
{
    //à compléter avec le liens
    //painter.drawImage(itsGame->getItsPlayer()->getItsHitBox(), itsAvatar);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(itsGame->getItsPlayer()->getItsHitBox());
}

void Widget::drawMushrooms(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for(auto it = itsGame->getItsMushrooms()->begin(); it !=  itsGame->getItsMushrooms()->end(); ++it)
    {
        //painter.drawImage((*it)->getItsHitBox(), itsMushrooms);
        painter.setPen(Qt::red);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect((*it)->getItsHitBox());
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
                //painter.drawImage(currentPart->getItsHitBox(), itsCentiBody);
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::SolidPattern);
                painter.drawRect(currentPart->getItsHitBox());
            }
            else
            {
                //display the head
                //painter.drawImage(currentPart->getItsHitBox(), itsCentiHead);
                painter.setPen(Qt::blue);
                painter.setBrush(Qt::SolidPattern);
                painter.drawRect(currentPart->getItsHitBox());
            }
            currentPart = currentPart->getItsChild();
        }
        delete currentPart;
    }
}

void Widget::drawBullet(QPainter & painter)
{
    //painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
    painter.setPen(Qt::green);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
}

void Widget::moveBullet()
{
    itsGame->getItsBullet()->updatePos();
}

void Widget::movePlayer()
{
    itsGame->getItsPlayer()->updatePos(itsPlayerDirection);
}

void Widget::startGame()
{
    ui->stackedWidget->setCurrentIndex(3); // j'ai mis 0 mais jsp trop lequel c'est
    itsGame = new Game();
    isGameStarted = true;
    itsDisplayTimer->start(16); // Update every 16 equal approximatly to 60fps
    //itsBulletTimer->start(1); // set the speed of it
    //itsCentipedeTimer->start(1); // set the speed of it
    itsPlayerTimer->start(16); // set the speed of it
    setFixedSize(this->width(), this->height()); // set the size of the window
}

void Widget::moveCentipede()
{

}
