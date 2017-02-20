#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    MainWindow window(QSize(3, 3));
    window.show();
    return a.exec();
}
