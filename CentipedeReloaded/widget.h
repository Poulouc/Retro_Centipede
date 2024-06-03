#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

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
    void paintEvent();

private slots:
    void keySpace();
    void keyZ();
    void keyQ();
    void keyS();
    void keyD();

private:
    Ui::Widget *ui;
    QTimer itsDisplayTimer;
    QTimer itsCentipedeTimer;
    QTimer itsBulletTimer;
    QTimer itsPlayerTimer;
};
#endif // WIDGET_H
