#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    //empty
}

void MainMenu::disable() {
    /*QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(x(), y(), size().width(), size().height()));
    animation->setEndValue(QRect(x(), y(), size().width(), 0));
    animation->start();*/

    setDisabled(true);
}

void MainMenu::enable() {
    /*QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(x(), y(), size().width(), 0));
    animation->setEndValue(QRect(x(), y(), size().width(), size().height()));
    animation->start();*/

    setEnabled(true);
}
