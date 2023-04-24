#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("QtGraphAnalyser");
    w.setWindowIcon(QIcon("Icons/MainWindow.png"));
    w.show();


    return a.exec();
}
