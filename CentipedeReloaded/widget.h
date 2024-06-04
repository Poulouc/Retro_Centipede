#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <Qpainter>
#include <QKeyEvent>
#include "game.h"
#include "typeDef.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    /**
     * @brief Overrides the paint event to draw the Widget components.
     *
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Overrides the key press event to handle user input.
     *
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent * event) override;

    /**
     * @brief Overrides the key press event to handle user input.
     *
     * @param event The key event.
     */
    void keyReleaseEvent(QKeyEvent * event) override;

    void drawCentipede(QPainter & painter);

    void drawPlayer(QPainter & painter);

    void drawBullet(QPainter & painter);

    void drawMushrooms(QPainter & painter);


private slots:
    void movePlayer();
    void moveCentipede();
    void moveBullet();
    void startGame();

private:
    Ui::Widget *ui;
    QTimer * itsDisplayTimer = nullptr;
    QTimer * itsCentipedeTimer = nullptr;
    QTimer * itsBulletTimer = nullptr;
    QTimer * itsPlayerTimer = nullptr;
    Game * itsGame = nullptr;
    QImage itsCentiHead;
    QImage itsCentiBody;
    QImage itsAvatar;
    QImage itsMushrooms;
    Direction itsPlayerDirection;
    bool isGameStarted;
};
#endif // WIDGET_H
