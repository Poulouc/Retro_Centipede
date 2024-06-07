#include "widget.h"
#include "ui_widget.h"


using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), isGameStarted(false)
{
    ui->setupUi(this);

    // Change title of the window
    setWindowTitle("Centipede Reloaded - v1.0");

    // Change background color of the widget
    QPalette bgColor = QPalette();
    bgColor.setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(bgColor);

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

    // Connect buttons to their method
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->back_button, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->back_button_2, SIGNAL(clicked()), this, SLOT(backToMenu()));

    // Connect timers to their method
    connect(itsDisplayTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(itsPlayerTimer, SIGNAL(timeout()), this, SLOT(movePlayer()));
    connect(itsBulletTimer, SIGNAL(timeout()), this, SLOT(moveBullet()));
    connect(itsCentipedeTimer, SIGNAL(timeout()), this, SLOT(moveCentipede()));
}

Widget::~Widget()
{
    // Delete all pointers
    delete ui;
    delete itsBulletTimer;
    delete itsCentipedeTimer;
    delete itsDisplayTimer;
    delete itsPlayerTimer;
    delete itsGame;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // Avoid warnings of unused variable of Qt
    Q_UNUSED(event);
    if (isGameStarted)
    {
        QPainter painter(this);

        // Paint in light gray the area of the game board
        painter.fillRect(itsGameBoard, QBrush(Qt::lightGray, Qt::SolidPattern));

        // Draw each entities of the game
        drawCentipede(painter);
        drawPlayer(painter);
        drawBullet(painter);
        drawMushrooms(painter);
        drawHeadUpDisplay(painter);

        // Check if the game has ended
        endGame();
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    // Avoid warnings of unused variable of Qt
    Q_UNUSED(event);
    if (itsGame != nullptr)
    {
        // Calculate the size of itsBoard with the smallest dimension of the window
        int boardHeight = height() * 95 / 100;
        int boardWidth = boardHeight / BOARD_WIDTH * BOARD_HEIGHT;
        int boardX = width() / 2 - boardWidth / 2;
        int boardY = height() * 5 / 100;
        itsGameBoard = { boardX, boardY, boardWidth, boardHeight };

        itsGame->setBoard(QRect(boardX, boardY, boardWidth, boardHeight));
        // Adjust timers with the window size
        itsBulletTimer->start(4000 / boardHeight);
        itsPlayerTimer->start(2500 / boardWidth);
    }
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    // Handle key press events for Z, Q, S, D and Space keys
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
    // Handle key release events for Z, Q, S and D keys
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
    // Draw the player at his position
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
        painter.setBrush(Qt::SolidPattern);
        if(mushroom->getItsState() == 4)
        {
            painter.setPen(Qt::red);
            painter.drawRect(mushroom->getItsHitBox());
        }
        else if(mushroom->getItsState() == 3)
        {
            painter.setPen(Qt::magenta);
            painter.drawRect(mushroom->getItsHitBox());
        }
        else if(mushroom->getItsState() == 2)
        {
            painter.setPen(Qt::yellow);
            painter.drawRect(mushroom->getItsHitBox());
        }
        else if(mushroom->getItsState() == 1)
        {
            painter.setPen(Qt::green);
            painter.drawRect(mushroom->getItsHitBox());
        }
    }
}

void Widget::drawCentipede(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for (vector<Centipede *>::iterator it = itsGame->getItsCentipedes()->begin(); it != itsGame->getItsCentipedes()->end(); ++it) {
        BodyPart * currentPart = (*it)->getItsHead();

        // displays the tail
        painter.setPen(Qt::darkGreen);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect((*it)->getItsTail()->getItsHitBox());

        // displays the head
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect((*it)->getItsHead()->getItsHitBox());
        while(currentPart->getItsChild() != nullptr)
        {
            if(currentPart != (*it)->getItsHead())
            {
                //displays the bodyparts
                //painter.drawImage(currentPart->getItsHitBox(), itsCentiBody);
                painter.setPen(Qt::cyan);
                painter.setBrush(Qt::SolidPattern);
                painter.drawRect(currentPart->getItsHitBox());
            }
            currentPart = currentPart->getItsChild();
        }
    }
}

void Widget::drawBullet(QPainter & painter)
{
    // Check if the bullet exists
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

    // ---- EXPERIMENTAL ----
    itsGame->checkCollisions();
    // ----------------------
}

void Widget::movePlayer()
{
    itsGame->movePlayer(itsPlayerDirection);
}

void Widget::startGame()
{
    // Set the stacked widget on an empty widget
    ui->stackedWidget->setCurrentIndex(3);

    // Calculate game board
    int boardHeight = height() * 95 / 100;
    int boardWidth = boardHeight / BOARD_WIDTH * BOARD_HEIGHT;
    int boardX = width() / 2 - boardWidth / 2;
    int boardY = height() * 5 / 100;
    itsGameBoard = { boardX, boardY, boardWidth, boardHeight };

    itsGame = new Game({ boardX, boardY, boardWidth, boardHeight });
    isGameStarted = true;
    itsDisplayTimer->start(16); // Update every 16 equal approximatly to 60fps
    itsBulletTimer->start(16); // set the speed of it
    itsCentipedeTimer->start(16); // set the speed of it
    itsPlayerTimer->start(3); // set the speed of it
    //setFixedSize(this->width(), this->height()); // set the size of the window
}

void Widget::endGame()
{
    if (itsGame->isGameWon())
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (itsGame->isGameLosed())
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else return;

    itsDisplayTimer->stop();
    itsBulletTimer->stop();
    itsCentipedeTimer->stop();
    itsPlayerTimer->stop();

    isGameStarted = false;

    // ---- EXPERIMENTAL ----
    QPalette bgColor = QPalette();
    bgColor.setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(bgColor);
    // ----------------------
}

void Widget::backToMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::moveCentipede()
{
    itsGame->moveCentipede();
}

