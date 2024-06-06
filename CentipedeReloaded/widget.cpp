#include "widget.h"
#include "ui_widget.h"


using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Centipede Reloaded - v1.0");
    isGameStarted = false;
    connect(ui->playButton , SIGNAL(clicked()), this, SLOT(startGame()));

    // Create timers for updating the GUI, the centipede, the bullet, the player
    itsDisplayTimer = new QTimer(this);
    itsCentipedeTimer = new QTimer(this);
    itsBulletTimer = new QTimer(this);
    itsPlayerTimer = new QTimer(this);

    // Loading assets
    itsCentiBody.load("../imageDoss/centibody.png");
    itsCentiHead.load("../imageDoss/centihead.png");
    itsAvatar.load("../imageDoss/avatar.png");
    itsMushrooms.load("../imageDoss/mushrooms.png");

    // Initialize the direction of the player
    itsPlayerDirection.dirX = 0;
    itsPlayerDirection.dirY = 0;

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
    //delete itsPlayerDirection;
}

void Widget::paintEvent(QPaintEvent *event)
{
    if(isGameStarted)
    {
        Q_UNUSED(event); //pour éviter les avertissements du compilateur concernant des variables non utilisées
        QPainter painter(this);
        drawCentipede(painter);
        drawPlayer(painter);
        drawBullet(painter);
        drawMushrooms(painter);
        drawHeadUpDisplay(painter);
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if (itsGame != nullptr)
    {
        // Calculer la taille du itsBoard en fonction de la plus petite dimension de la fenêtre
        int boardSize = 0.95*qMin(this->width(), height());
        int boardX = (this->width() - boardSize) / 2;
        int boardY = (0.03*boardSize)+((this->height() - boardSize) / 2);

        itsGame->setBoard(QRect(boardX, boardY, boardSize, boardSize));
        // ajuster les timers ou autres paramètres en fonction de la nouvelle taille de la fenêtre
        itsBulletTimer->start(4000 / this->height()); // Définir la vitesse du bullet
        itsPlayerTimer->start(2500 / this->width()); // Définir la vitesse du player
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
    // Handle key release events for left and right arrow keys
    if (event->key() == Qt::Key_Z && itsPlayerDirection.dirY == -1)
    {
        itsPlayerDirection.dirY = 0;
    }
    if (event->key() == Qt::Key_Q && itsPlayerDirection.dirX == -1)
    {
        itsPlayerDirection.dirX = 0;
    }
    if (event->key() == Qt::Key_S && itsPlayerDirection.dirY == 1)
    {
        itsPlayerDirection.dirY = 0;
    }
    if (event->key() == Qt::Key_D && itsPlayerDirection.dirX == 1)
    {
        itsPlayerDirection.dirX = 0;
    }
}

void Widget::drawPlayer(QPainter & painter)
{
    //à compléter avec le liens
    //painter.drawImage(itsGame->getItsPlayer()->getItsHitBox(), itsAvatar);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(itsGame->getItsPlayer()->getItsHitBox());
}

void Widget::drawMushrooms(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for(Mushroom * mushroom : *itsGame->getItsMushrooms())
    {
        //painter.drawImage((*it)->getItsHitBox(), itsMushrooms);
        painter.setPen(Qt::red);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect(mushroom->getItsHitBox());
    }
}

void Widget::drawCentipede(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for (vector<Centipede *>::iterator it = itsGame->getItsCentipedes()->begin(); it != itsGame->getItsCentipedes()->end(); ++it) {
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
    if(itsGame->getItsBullet() != nullptr)
    {
        //painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
        painter.setPen(Qt::green);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
    }
}

void Widget::drawHeadUpDisplay(QPainter & painter)
{
    // Set the font and color for the text
    QFont font("Arial", 8, QFont::Bold);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Draw the score
    painter.drawText((this->width()*0.1 - (QFontMetrics(font).boundingRect(QString("Score: %1").arg(itsGame->getItsScore())).width()/2)),
    (this->height()*0.04), QString("Score: %1").arg(itsGame->getItsScore()));

    // Draw the game name
    painter.drawText((this->width()*0.5 - (QFontMetrics(font).boundingRect(QString("Centipede Reloaded")).width()/2))
    , (this->height()*0.04), QString("Centipede Reloaded"));

    // Draw the life count
    painter.drawText((this->width()*0.9 - (QFontMetrics(font).boundingRect(QString("Life: %1").arg(itsGame->getItsPlayer()->getItsHp())).width()/2))
    , (this->height()*0.04), QString("Life: %1").arg(itsGame->getItsPlayer()->getItsHp()));

    painter.drawRect(QRect(0, this->height()*0.05 - 1, this->width(), 0));
}

void Widget::moveBullet()
{
    if(itsGame->getItsBullet() != nullptr) itsGame->moveBullet();
}

void Widget::movePlayer()
{
    itsGame->movePlayer(itsPlayerDirection);
}

void Widget::moveCentipede()
{

}

void Widget::startGame()
{
    ui->stackedWidget->setCurrentIndex(3);

    // Calculer la taille du itsBoard en fonction de la plus petite dimension de la fenêtre
    int boardSize = 0.95*qMin(width(), height());
    int boardX = (width() - boardSize) / 2;
    int boardY = (0.03*boardSize)+((height() - boardSize) / 2);

    itsGame = new Game({boardX, boardY, boardSize, boardSize});

    isGameStarted = true;
    itsDisplayTimer->start(16); // Mettre à jour toutes les 16 ms (environ 60fps)
    itsBulletTimer->start(4000 / this->height()); // Définir la vitesse du bullet
    itsPlayerTimer->start(2500 / this->width()); // Définir la vitesse du player
    //setFixedSize(this->width(), this->height()); // Définir la taille de la fenêtre
}
