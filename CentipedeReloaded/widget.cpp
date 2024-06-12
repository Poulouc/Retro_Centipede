#include "widget.h"
#include "ui_widget.h"


using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), isGameStarted(false)
{
    ui->setupUi(this);

    // Change title of the window and set minimum size of the window
    setWindowTitle("Centipede Reloaded - v1.0");
    setMinimumSize(400, 300);

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
    itsPowerUpMovementTimer = new QTimer(this);
    itsRafaleTimer = new QTimer(this);
    itsPiercingTimer = new QTimer(this);
    itsSpiderAppearTimer = new QTimer(this);
    itsSpiderTimer = new QTimer(this);

    // Loading assets
    itsCentiBody.load("../../../imageDoss/centibody.png");
    itsCentiHead.load("../../../imageDoss/centihead.png");
    itsAvatar.load("../../../imageDoss/avatar.png");
    itsMushrooms.load("../../../imageDoss/mushrooms.png");

    // Initialize the direction of the player
    itsPlayerDirection.dirX = 0;
    itsPlayerDirection.dirY = 0;

    // Connect buttons to their method
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->back_button, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->back_button_2, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->buttonHowToPlay, SIGNAL(clicked()), this, SLOT(goToHowToPlay()));
    connect(ui->backToMenuButton_2, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->resumeGameButton, SIGNAL(clicked()), this, SLOT(resumeGame()));
    connect(ui->backToMenuButton, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->leaderboardButton, SIGNAL(clicked()), this, SLOT(displayLeaderboard()));
    connect(ui->backToMenu, SIGNAL(clicked()), this, SLOT(backToMenu()));

    //Set style sheets for the ui
    //ui->HowToPlay->setStyleSheet("../../../styleSheets/styleSheetHowtoPlay");

    // Connect timers to their method
    connect(itsDisplayTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(itsPlayerTimer, SIGNAL(timeout()), this, SLOT(movePlayer()));
    connect(itsBulletTimer, SIGNAL(timeout()), this, SLOT(moveBullet()));
    connect(itsCentipedeTimer, SIGNAL(timeout()), this, SLOT(moveCentipede()));
    connect(itsPowerUpMovementTimer, SIGNAL(timeout()), this, SLOT(movePowerUps()));
    connect(itsRafaleTimer, SIGNAL(timeout()), this, SLOT(rafaleShot()));
    connect(itsPiercingTimer, SIGNAL(timeout()), this, SLOT(piercingEnd()));
    connect(itsSpiderAppearTimer, SIGNAL(timeout()), this, SLOT(spiderAppear()));
    connect(itsSpiderTimer, SIGNAL(timeout()), this, SLOT(moveSpider()));

    itsLeaderboard = new Leaderboard("../../../CentipedeReloaded/leaderboard.txt");
}

Widget::~Widget()
{
    // Delete all pointers
    delete ui;
    delete itsBulletTimer;
    delete itsCentipedeTimer;
    delete itsDisplayTimer;
    delete itsPlayerTimer;
    delete itsPowerUpMovementTimer;
    delete itsRafaleTimer;
    delete itsPiercingTimer;
    delete itsGame;
    delete itsLeaderboard;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // Avoid warnings of unused variable of Qt
    Q_UNUSED(event);
    if (isGameStarted && !isGamePaused)
    {
        QPainter painter(this);

        // Paint in light gray the area of the game board
        painter.fillRect(itsGame->getItsBoard(), QBrush(Qt::lightGray, Qt::SolidPattern));

        // Draw each entities of the game
        drawCentipede(painter);
        drawPlayer(painter);
        drawBullet(painter);
        drawMushrooms(painter);
        drawPowerUps(painter);
        drawHeadUpDisplay(painter);
        drawSpider(painter);

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
        // Calculate the size of itsBoard based on the smallest dimension of the window
        int maxHeight = height() * 95 / 100; // 95% of the window height
        int maxBoardHeight = maxHeight;

        // Find the largest multiple of BOARD_HEIGHT that fits within the available height
        int boardHeight = (maxBoardHeight / BOARD_HEIGHT) * BOARD_HEIGHT;
        int boardWidth = boardHeight * BOARD_WIDTH / BOARD_HEIGHT;
        int boardX = width() / 2 - boardWidth / 2;
        int boardY = height() * 5 / 100;


        itsCentipedeTimer->stop();
        itsGame->setBoard(QRect(boardX, boardY, boardWidth, boardHeight));

        // Adjust timers or other parameters based on the new window size
        itsCentipedeTimer->start(4000 / boardWidth); // set the speed of it
        itsBulletTimer->start(3000 / boardHeight); // Set the speed of the bullet
        itsPlayerTimer->start(2500 / boardWidth); // Set the speed of the player
        if(itsGame->getItsSpider() != nullptr)
        {
            itsSpiderTimer->start(4000 / boardWidth);
        }
    }
}


void Widget::keyPressEvent(QKeyEvent * event)
{
    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && ui->stackedWidget->currentIndex() == 7)
    {
        processNewScore();
    }

    if(!isGameStarted) return;
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
        if(!itsGame->getIsRafaleActive()) itsGame->shoot();
    }
    if (event->key() == Qt::Key_Escape)
    {
        if(isGamePaused)
        {
            resumeGame();
        }
        else
        {
            pauseGame();
        }
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
    if(SHOW_HITBOXES)
    {
        // shows the player hitbox
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::SolidPattern);
        painter.drawRect(itsGame->getItsPlayer()->getItsHitBox());
    }
    else
    {
        // Draws the player at his position
        painter.drawImage(itsGame->getItsPlayer()->getItsHitBox(), itsAvatar);
    }
}

void Widget::drawMushrooms(QPainter & painter)
{
    //painter.drawImage(0, 0, *itsBackgroundImage);
    for(Mushroom * mushroom : *itsGame->getItsMushrooms())
    {
        if(SHOW_HITBOXES)
        {
            // displays the mushroom hitbox
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
        else
        {
            // displays the mushroom image
            painter.drawImage(mushroom->getItsHitBox(), itsMushrooms);
        }
    }
}

void Widget::drawCentipede(QPainter & painter)
{
    for (vector<Centipede *>::iterator it = itsGame->getItsCentipedes()->begin(); it != itsGame->getItsCentipedes()->end(); ++it) {
        BodyPart * currentPart = (*it)->getItsHead();

        if(SHOW_HITBOXES)
        {
            // displays the tail hitbox
            painter.setPen(Qt::darkGreen);
            painter.setBrush(Qt::SolidPattern);
            painter.drawRect((*it)->getItsTail()->getItsHitBox());

            // displays the head hitbox
            painter.setPen(Qt::blue);
            painter.setBrush(Qt::SolidPattern);
            painter.drawRect((*it)->getItsHead()->getItsHitBox());
        }
        else
        {
            // displays the tail image
            painter.drawImage((*it)->getItsTail()->getItsHitBox(), itsCentiBody);
            // displays the head image
            painter.drawImage((*it)->getItsHead()->getItsHitBox(), itsCentiHead);
        }

        while(currentPart->getItsChild() != nullptr)
        {
            if(currentPart != (*it)->getItsHead())
            {
                if(SHOW_HITBOXES)
                {
                    // displays the bodypart hitbox
                    painter.setPen(Qt::cyan);
                    painter.setBrush(Qt::SolidPattern);
                    painter.drawRect(currentPart->getItsHitBox());
                }
                else
                {
                    // displays the bodypart image
                    painter.drawImage(currentPart->getItsHitBox(), itsCentiBody);
                }
            }
            currentPart = currentPart->getItsChild();
        }
    }
}

void Widget::drawBullet(QPainter & painter)
{
    // Check if the bullet exists
    for(Bullet* bullet : itsGame->getItsBullets())
    {
        if(SHOW_HITBOXES)
        {
            // displays the bullet hitbox
            painter.setPen(Qt::green);
            painter.setBrush(Qt::SolidPattern);
            painter.drawRect(bullet->getItsHitBox());
        }
        else
        {
            // displays the bullet image
            painter.drawRect(bullet->getItsHitBox());
        }
    }
}

void Widget::drawPowerUps(QPainter & painter)
{
    for(PowerUp* powerup : itsGame->getItsPowerups())
    {
        if(SHOW_HITBOXES)
        {
            switch(powerup->getItsType())
            {
            case rafale:
                painter.setPen(Qt::black);
                painter.setBrush(Qt::SolidPattern);
                break;
            case transpercant:
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::SolidPattern);
                break;
            case herbicide:
                painter.setPen(Qt::green);
                painter.setBrush(Qt::SolidPattern);
            }
            painter.drawRect(powerup->getItsHitbox());
        }
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
    painter.drawText((this->width()*0.5 - (QFontMetrics(font).boundingRect(QString("Niveau: %1").arg(itsGame->getCurrentLevel())).width()/2))
    , (this->height()*0.04), QString("Niveau: %1").arg(itsGame->getCurrentLevel()));

    // Draw the life count
    painter.drawText((this->width()*0.9 - (QFontMetrics(font).boundingRect(QString("Life: %1").arg(itsGame->getItsPlayer()->getItsHp())).width()/2))
    , (this->height()*0.04), QString("Life: %1").arg(itsGame->getItsPlayer()->getItsHp()));

    painter.drawRect(QRect(0, this->height()*0.05 - 1, this->width(), 0));
}

void Widget::moveBullet()
{
    itsGame->moveBullets();

    // ---- EXPERIMENTAL ----
    itsGame->checkCollisions();
    // ----------------------
}

void Widget::movePlayer()
{
    itsGame->movePlayer(itsPlayerDirection);
}

void Widget::movePowerUps()
{
    itsGame->movePowerUps();
    if(itsGame->getIsRafaleActive() && !itsRafaleTimer->isActive())
    {
        remainingRafaleShots = POWERUP_RAFALE_FIRERATE * POWERUP_RAFALE_DURATION;
        itsRafaleTimer->start(1000/POWERUP_RAFALE_FIRERATE);
    }
    if(itsGame->getIsPiercingActive() && !itsPiercingTimer->isActive())
    {
        itsPiercingTimer->start(1000*POWERUP_PIERCING_DURATION);
    }
}

void Widget::startGame(int level)
{
    int boardHeight = height() * 95 / 100;
    int boardWidth = boardHeight / BOARD_WIDTH * BOARD_HEIGHT;
    int baseCentipedeTimer = (4000 / boardWidth);
    itsCentipedeTimer->start(baseCentipedeTimer - level/10); // set the speed of it
    if(!isGameStarted)
    {
        // Set the stacked widget on an empty widget
        ui->stackedWidget->setCurrentIndex(3);
        this->update();

        // Calculate game board
        int boardX = width() / 2 - boardWidth / 2;
        int boardY = height() * 5 / 100;
        itsGameBoard = { boardX, boardY, boardWidth, boardHeight };

        itsGame = new Game({ boardX, boardY, boardWidth, boardHeight });
        isGameStarted = true;
        itsDisplayTimer->start(16); // Update every 16 equal approximatly to 60fps
        itsBulletTimer->start(3000 / boardHeight); // Set the speed of the bullet
        itsPlayerTimer->start(2500 / boardWidth); // Set the speed of the player
        itsPowerUpMovementTimer->start(baseCentipedeTimer - level/10);
        itsSpiderAppearTimer->start(1000); //à mettre là ou le niveau 2 demarre
        itsSpiderAppearProbability = INCREMENT_INTERVAL; //Set the minimum probability for the spider to appear
    }
    else
    {
        itsGame->spawnCentipede();
    }

}

void Widget::endGame()
{
    if (itsGame->isLevelWon())
    {
        startGame(itsGame->getCurrentLevel());
        return;
    }
    else if (itsGame->isGameLosed())
    {
        ui->stackedWidget->setCurrentIndex(7);
    }
    else return;

    itsDisplayTimer->stop();
    itsBulletTimer->stop();
    itsCentipedeTimer->stop();
    itsPlayerTimer->stop();
    itsPowerUpMovementTimer->stop();
    itsRafaleTimer->stop();
    itsPiercingTimer->stop();
    isGameStarted = false;
    this->update();
}

void Widget::pauseGame()
{
    itsDisplayTimer->stop();
    itsBulletTimer->stop();
    itsCentipedeTimer->stop();
    itsPlayerTimer->stop();
    itsPowerUpMovementTimer->stop();
    itsSpiderAppearTimer->stop();
    itsSpiderTimer->stop();

    isGamePaused = true;
    ui->stackedWidget->setCurrentIndex(4);
    this->update();
}

void Widget::resumeGame()
{
    itsDisplayTimer->start();
    itsBulletTimer->start();
    itsCentipedeTimer->start();
    itsPlayerTimer->start();
    itsPowerUpMovementTimer->start();
    itsSpiderAppearTimer->start();
    itsSpiderTimer->start();

    isGamePaused = false;
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::backToMenu()
{
    isGameStarted = false;
    isGamePaused = false;
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::displayLeaderboard()
{
    try
    {
        itsLeaderboard->extract();
        map<string,int> unsortedBestScores = itsLeaderboard->getItsBestScores();
        map<int,string> bestScores = {};
        for(pair<string,int> score : unsortedBestScores)
        {
            bestScores.insert({-score.second, score.first});
        }
        QLabel* labelList[10] = {ui->position_1, ui->position_2, ui->position_3, ui->position_4, ui->position_5, ui->position_6, ui->position_7, ui->position_8, ui->position_9, ui->position_10};
        map<int,string>::iterator it = bestScores.begin();
        for(QLabel* label : labelList)
        {
            if(it == bestScores.end()) break;
            string newText = it->second + " - " + to_string(-it->first);
            label->setText(QString::fromStdString(newText));
            ++it;
        }
    }
    catch(string & e)
    {
        qDebug() << e;
    }
    ui->stackedWidget->setCurrentIndex(6);
}

void Widget::goToHowToPlay()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Widget::moveCentipede()
{
    itsGame->moveCentipede();
}

void Widget::rafaleShot()
{
    if(remainingRafaleShots == 0)
    {
        itsGame->setIsRafaleActive(false);
        itsRafaleTimer->stop();
    }
    else
    {
        itsGame->shoot();
        remainingRafaleShots--;
    }
}

void Widget::piercingEnd()
{
    itsGame->setIsPiercingActive(false);
    itsPiercingTimer->stop();
}

void Widget::drawSpider(QPainter & painter)
{
    // Check if the spider exists
    if(itsGame->getItsSpider() != nullptr)
    {
        if(SHOW_HITBOXES)
        {
            // displays the spider hitbox
            painter.setPen(Qt::magenta);
            painter.setBrush(Qt::SolidPattern);
            painter.drawRect(itsGame->getItsSpider()->getItsHitBox());
        }
        else
        {
            // displays the spider image
            //painter.drawRect(itsGame->getItsBullet()->getItsHitBox());
        }
    }
}

void Widget::spiderAppear()
{
    if (isGameStarted && !isGamePaused && itsGame->getItsSpider() == nullptr) {
        itsElapsedTime += 1; // Augmenter le temps écoulé de 1 seconde

        if (itsElapsedTime % INCREMENT_INTERVAL == 0) {
            // Augmenter la probabilité d'apparition de 5% toutes les 5 secondes
            if (itsSpiderAppearProbability <= 100) {
                itsSpiderAppearProbability += 5;; // La probabilité ne doit pas dépasser 100%
            }
        }

        int chance = rand() % 100;
        if (chance < itsSpiderAppearProbability) {
            itsGame->createSpider();
            itsSpiderTimer->start(4000 / itsGame->getItsBoard().width());
            // Réinitialiser la probabilité et le temps écoulé
            itsSpiderAppearTimer->stop();
            itsSpiderAppearProbability = 5;
            itsElapsedTime = 0;
        }
    }
}

void Widget::moveSpider()
{
    if(itsGame->getItsSpider() != nullptr)
    {
        itsGame->moveSpider();
    }
    else
    {
        itsSpiderTimer->stop();
        itsSpiderAppearTimer->start(1000);
    }
}

void Widget::processNewScore()
{
    qDebug() << "e";
    string username = ui->usernameLineEdit->text().toStdString();
    int score = itsGame->getItsScore();
    delete itsGame;

    try
    {
        if(username != "") itsLeaderboard->addScore(score, username);
    }
    catch(string & e)
    {
        qDebug() << e;
    }

    displayLeaderboard();
}
