#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtWidgets>

class MainMenu : public QWidget {
    Q_OBJECT
public:
    MainMenu(QWidget *parent = 0);
private slots:
    void disable();
    void enable();
};

#endif // MAINMENU_H
