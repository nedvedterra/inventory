#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    //empty
}

void MainWidget::disable() {
    setDisabled(true);
}

void MainWidget::enable() {
    setEnabled(true);
}
