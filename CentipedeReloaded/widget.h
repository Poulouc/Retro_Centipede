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
 *
 * This class manages the game mechanics and drawing on the widget. It handles
 * player movement, centipede movement, bullet firing, powerups, and display updates.
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
     *
     * This method pauses all active timers and stops the game from updating.
     */
    void pauseGame();

private slots:
    /**
     * @brief Moves the player.
     *
     * This slot is connected to a timer that moves the player character.
     */
    void movePlayer();

    /**
     * @brief Moves the centipede.
     *
     * This slot is connected to a timer that moves the centipede enemies.
     */
    void moveCentipede();

    /**
     * @brief Moves the bullet.
     *
     * This slot is connected to a timer that moves the player's bullets.
     */
    void moveBullet();

    /**
     * @brief Moves powerups.
     *
     * This slot is connected to a timer that moves active powerups on the screen.
     */
    void movePowerUps();

    /**
     * @brief Starts the game.
     *
     * @param level The starting level of the game.
     *
     * This slot initializes the game state, including timers and game objects,
     * and starts the game loop.
     */
    void startGame(int level = 1);

    /**
     * @brief Resumes the game.
     *
     * This slot resumes the game after it has been paused.
     */
    void resumeGame();

    /**
     * @brief Ends the game and performs cleanup.
     *
     * This slot ends the current game session, stopping all timers and cleaning up
     * game objects.
     */
    void endGame();

    /**
     * @brief Returns to the main menu.
     *
     * This slot returns the player to the main menu.
     */
    void backToMenu();

    /**
     * @brief Displays the leaderboard.
     *
     * This slot shows the leaderboard screen.
     */
    void displayLeaderboard();

    /**
     * @brief Processes the new score and updates the leaderboard if needed.
     *
     * This slot updates the leaderboard with the player's new score.
     */
    void processNewScore();

    /**
     * @brief Displays the 'How to play' page.
     *
     * This slot displays instructions on how to play the game.
     */
    void goToHowToPlay();

    /**
     * @brief Used to shoot during the 'rafale' powerup.
     *
     * This slot allows rapid shooting when the 'rafale' powerup is active.
     */
    void rafaleShot();

    /**
     * @brief Called when the 'piercing' powerup ends.
     *
     * This slot handles the end of the 'piercing' powerup effect.
     */
    void piercingEnd();

    /**
     * @brief Moves the spider.
     *
     * This slot moves the spider enemy.
     */
    void moveSpider();

    /**
     * @brief Makes the spider appear.
     *
     * This slot triggers the appearance of the spider enemy.
     */
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
    QTimer * itsSpiderAppearTimer = nullptr; /**< Timer for spider appearance */
    QTimer * itsSpiderTimer = nullptr; /**< Timer for moving the spider */
    Game * itsGame = nullptr; /**< Pointer to the game object */
    Leaderboard * itsLeaderboard = nullptr; /**< Pointer to the leaderboard */
    QImage itsCentiHeadImg; /**< Image of the centipede head */
    QImage itsCentiBodyImg; /**< Image of the centipede body */
    QImage itsCentiTailImg; /**< Image of the centipede tail */
    QImage itsPlayerImg; /**< Image of the player character */
    QImage itsMushState1Img; /**< Image of the mushrooms (state 1) */
    QImage itsMushState2Img; /**< Image of the mushrooms (state 2) */
    QImage itsMushState3Img; /**< Image of the mushrooms (state 3) */
    QImage itsMushState4Img; /**< Image of the mushrooms (state 4) */
    QImage itsSpiderImg; /**< Image of the spider enemy */
    QImage itsBulletImg; /**< Image of the bullet */
    QImage itsRafalePuImg; /**< Image of the 'Rafale' powerup */
    QImage itsTranspercantPuImg; /**< Image of the 'Transpercant' powerup */
    QImage itsHerbicidePuImg; /**< Image of the 'Herbicide' powerup */
    QImage itsGrassTexture; /**< Texture image for grass */
    QImage itsDarkGrassTexture; /**< Texture image for dark grass */
    Direction itsPlayerDirection; /**< Direction of the player */
    bool isGameStarted = false; /**< Flag indicating whether the game has started */
    bool isGamePaused = false; /**< Flag indicating whether the game is paused */
    int remainingRafaleShots; /**< Number of remaining shots for 'Rafale' powerup */
    int itsElapsedTime; /**< Elapsed time of the current game session */
    int itsSpiderAppearProbability; /**< Probability of spider appearing */
    int itsCentiImgState = 1; /**< State that determine which image of the centiped is actually used */
};

#endif // WIDGET_H
