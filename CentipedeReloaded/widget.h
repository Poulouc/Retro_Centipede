#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "game.h"
#include "qpainter.h"
#include "qimage.h"

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
    void paintEvent(QPaintEvent *event);

    void drawCentipede(QPainter & painter);

    void drawPlayer(QPainter & painter);

    void drawBullet(QPainter & painter);

    void drawMushrooms(QPainter & painter);


private slots:
    void movePlayer(QKeyEvent * event);
    void moveCentipede();
    void moveBullet();
    void startGame();

private:
    Ui::Widget *ui;
    QTimer * itsDisplayTimer;
    QTimer * itsCentipedeTimer;
    QTimer * itsBulletTimer;
    QTimer * itsPlayerTimer;
    Game * itsGame;
    QImage itsCentiHead;
    QImage itsCentiBody;
    QImage itsAvatar;
    QImage itsMushrooms;
    bool isGameStarted;
};
#endif // WIDGET_H
