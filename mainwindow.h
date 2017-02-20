#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class ThingListView;
class InventoryTableView;
class MainMenu;
class MainWidget;

class QPushButton;
class QTableView;

#include "inventorytablemodel.h"
#include "thingslistmodel.h"

#include <QMainWindow>
#include <inventorydb.h>

#include <memory>

class MainWindow : public QMainWindow {
public:
    MainWindow(const QSize &inventorySize, QWidget *parent = 0);
private:
    void setupWidgets();
    void setupMenu();
    void setupMainWidget();
    void setupConnections();
    void customizeTableView(QTableView &tableView);

    QTableView *m_thingList;
    std::unique_ptr<ThingsListModel> m_thingListModel;
    InventoryTableView *m_inventoryTable;
    std::unique_ptr<InventoryTableModel> m_inventoryTableModel;

    MainMenu *m_mainMenu;
    MainWidget *m_mainWidget;

    QPushButton *m_startButton;
    QPushButton *m_exitButton;
    QPushButton *m_mainMenuButton;

    InventoryDb m_db;
};

#endif // MAINWINDOW_H
