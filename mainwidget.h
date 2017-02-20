#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
private slots:
    void disable();
    void enable();
};

#endif // MAINWIDGET_H
