#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    // Create a QApplication object, which manages the GUI application's control flow and main settings.
    QApplication a(argc, argv);

    // Create an instance of the Widget class, which represents the main window of the application.
    Widget w;

    // Show the main window.
    w.show();

    // Start the event loop of the application. This function will return when the application exits.
    return a.exec();
}
