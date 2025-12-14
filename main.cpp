#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
        "QRadioButton {"
        "   spacing: 10px;"
        "   font-size: 16px;"
        "}"
        "QPushButton {"
        "   background-color: transparent;"
        "   border: transparent;"
        "}"

        "QPushButton:hover {"
        "   background-color: transparent;"
        "}"

        "QRadioButton::indicator:unchecked {"
        "   border: 2px solid #3498db;"
        "   background-color: transparent;"
        "   border-radius: 10px;"
        "}"
        "QRadioButton::indicator:checked {"
        "   background-color: #3498db;"
        "   border: 2px solid #3498db;"
        "   border-radius: 10px;"
        "}"
        );
    w.showFullScreen();

    return a.exec();
}
