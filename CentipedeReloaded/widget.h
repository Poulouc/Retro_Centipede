/**
 * @file widget.h
 * @brief Defines the Widget class, which represents the main game widget.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <QFontMetrics>
#include <QResizeEvent>
#include "game.h"
#include "typeDef.h"
#include "leaderboard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

/**
 * @class Widget
 * @brief Class representing the main game widget.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Widget class.
     * @param parent The parent widget.
     */
    Widget(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Widget class.
     */
    ~Widget();

protected:
    /**
     * @brief Overrides the paint event to draw the Widget components.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Overrides the key press event to handle user input.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent * event) override;

    /**
     * @brief Overrides the key release event to handle user input.
     * @param event The key event.
     */
    void keyReleaseEvent(QKeyEvent * event) override;

    /**
     * @brief Overrides the resize event to handle widget resizing.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Draws the centipede on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawCentipede(QPainter & painter);

    /**
     * @brief Draws the player on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawPlayer(QPainter & painter);

    /**
     * @brief Draws the bullet on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawBullet(QPainter & painter);

    /**
     * @brief Draws the mushrooms on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawMushrooms(QPainter & painter);

    /**
     * @brief Draws the powerups on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawPowerUps(QPainter & painter);

    /**
     * @brief Draws the heads-up display on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawHeadUpDisplay(QPainter & painter);

    /**
     * @brief Draws the spider display on the widget using QPainter.
     * @param painter The QPainter object used for drawing.
     */
    void drawSpider(QPainter & painter);
    /**
     * @brief Pauses the game and its timers.
     */
    void pauseGame();

private slots:
    /**
     * @brief Moves the player.
     */
    void movePlayer();

    /**
     * @brief Moves the centipede.
     */
    void moveCentipede();

    /**
     * @brief Moves the bullet.
     */
    void moveBullet();

    /**
     * @brief Moves powerups.
     */
    void movePowerUps();

    /**
     * @brief Starts the game.
     */
    void startGame(int level = 1);

    /**
     * @brief Resumes the game.
     */
    void resumeGame();

    /**
     * @brief Ends the game and performs cleanup.
     */
    void endGame();

    /**
     * @brief Returns to the main menu.
     */
    void backToMenu();

    /**
     * @brief Displays the leaderboard.
     */
    void displayLeaderboard();

    /**
     * @brief Processes the new score and updates the leaderboard if needed.
     */
    void processNewScore();

    /**
     * @brief Displays the 'How to play' page.
     */
    void goToHowToPlay();

    /**
     * @brief Used to shoot during the 'rafale' powerup.
     */
    void rafaleShot();

    /**
     * @brief Called when the 'piercing' powerup ends.
     */
    void piercingEnd();


    void moveSpider();


    void spiderAppear();

private:
    Ui::Widget *ui; /**< The UI object */
    QTimer * itsDisplayTimer = nullptr; /**< Timer for updating the display */
    QTimer * itsCentipedeTimer = nullptr; /**< Timer for moving the centipede */
    QTimer * itsBulletTimer = nullptr; /**< Timer for moving the bullet */
    QTimer * itsPlayerTimer = nullptr; /**< Timer for moving the player */
    QTimer * itsPowerUpMovementTimer = nullptr; /**< Timer for moving powerups */
    QTimer * itsRafaleTimer = nullptr; /**< Timer for the powerup 'Rafale' */
    QTimer * itsPiercingTimer = nullptr; /**< Timer for the powerup 'Piercing' */
    QTimer * itsSpiderAppearTimer = nullptr;
    QTimer * itsSpiderTimer = nullptr;
    Game * itsGame = nullptr; /**< Pointer to the game object */
    Leaderboard * itsLeaderboard = nullptr;
    QImage itsCentiHeadImg; /**< Image of the centipede head */
    QImage itsCentiBodyImg; /**< Image of the centipede body */
    QImage itsCentiTailImg;
    QImage itsPlayerImg; /**< Image of the player */
    QImage itsMushState1Img; /**< Image of the mushrooms */
    QImage itsMushState2Img;
    QImage itsMushState3Img;
    QImage itsMushState4Img;
    QImage itsSpiderImg;
    QImage itsBulletImg;
    QImage itsRafalePuImg;
    QImage itsTranspercantPuImg;
    QImage itsHerbicidePuImg;
    QImage itsGrassTexture;
    QImage itsDarkGrassTexture;
    Direction itsPlayerDirection; /**< Direction of the player */
    QRect itsGameBoard; /**< Rectangle representing the game board */
    bool isGameStarted = false; /**< Flag indicating whether the game has started */
    bool isGamePaused = false; /**< Flag indicating wether the game is paused */
    int remainingRafaleShots; /**< Number of shots remaining for the rafale powerup */
    int itsElapsedTime;
    int itsSpiderAppearProbability;
};

#endif // WIDGET_H
