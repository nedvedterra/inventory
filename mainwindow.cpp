#include "mainwindow.h"
#include "thingslistmodel.h"
#include "inventorytableview.h"
#include "inventorytablemodel.h"
#include "backgrounddelegate.h"
#include "mainmenu.h"
#include "mainwidget.h"

#include "QtWidgets"

MainWindow::MainWindow(const QSize &inventorySize, QWidget *parent) :
    QMainWindow(parent), m_db(InventoryDb::getInstance()) {
    setupWidgets();

    size_t typesCount = m_db.getTypesCount();
    m_thingListModel = std::make_unique<ThingsListModel>(typesCount);
    m_thingList->setModel(m_thingListModel.get());
    m_inventoryTableModel = std::make_unique<InventoryTableModel>(inventorySize);
    m_inventoryTable->setModel(m_inventoryTableModel.get());

    customizeTableView(*m_thingList);
    customizeTableView(*m_inventoryTable);

    setupConnections();
}

void MainWindow::setupMenu() {
    m_mainMenu = new MainMenu();
    QHBoxLayout *menuLayout = new QHBoxLayout(m_mainMenu);

    m_startButton = new QPushButton("Start");
    m_startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    menuLayout->addWidget(m_startButton);
    m_exitButton = new QPushButton("Exit");
    m_exitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    menuLayout->addWidget(m_exitButton);
}

void MainWindow::setupMainWidget() {
    QVBoxLayout *thingListAndButton = new QVBoxLayout();

    m_thingList = new QTableView();
    thingListAndButton->addWidget(m_thingList);
    m_mainMenuButton = new QPushButton("Main Menu");
    m_mainMenuButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    thingListAndButton->addWidget(m_mainMenuButton);
    thingListAndButton->setAlignment(Qt::AlignBottom);

    m_mainWidget = new MainWidget();
    m_mainWidget->setDisabled(true);
    QHBoxLayout *mainWidgetLayout = new QHBoxLayout(m_mainWidget);

    m_inventoryTable = new InventoryTableView();
    mainWidgetLayout->addWidget(m_inventoryTable);
    mainWidgetLayout->addSpacing(50);
    mainWidgetLayout->addLayout(thingListAndButton);
}

void MainWindow::setupWidgets() {
    setupMenu();
    setupMainWidget();

    QFrame *frame = new QFrame();
    QVBoxLayout *mainWindowLayout = new QVBoxLayout(frame);
    mainWindowLayout->addWidget(m_mainMenu);
    mainWindowLayout->addWidget(m_mainWidget);

    setCentralWidget(frame);
}

void MainWindow::setupConnections() {
    QObject::connect(m_inventoryTable, SIGNAL(rightClicked(QModelIndex)),
                     m_inventoryTableModel.get(), SLOT(onRightClick(QModelIndex)));
    QObject::connect(m_startButton, SIGNAL(clicked(bool)),
                     m_mainMenu, SLOT(disable()));
    QObject::connect(m_startButton, SIGNAL(clicked(bool)),
                     m_mainWidget, SLOT(enable()));
    QObject::connect(m_mainMenuButton, SIGNAL(clicked(bool)),
                     m_mainMenu, SLOT(enable()));
    QObject::connect(m_mainMenuButton, SIGNAL(clicked(bool)),
                     m_mainWidget, SLOT(disable()));
    QObject::connect(m_exitButton, SIGNAL(clicked(bool)),
                     this, SLOT(close()));
}

void MainWindow::customizeTableView(QTableView &tableView) {
    tableView.verticalHeader()->setVisible(false);
    tableView.horizontalHeader()->setVisible(false);
    tableView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    tableView.verticalHeader()->setDefaultSectionSize(Thing::IMAGE_SIZE);
    tableView.horizontalHeader()->setDefaultSectionSize(Thing::IMAGE_SIZE);
    tableView.setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
    tableView.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    tableView.setItemDelegate(new BackgroundDelegate());
    tableView.setStyleSheet("QTableView::item { selection-color: black;"
                  "selection-background-color: rgba(128, 128, 128, 64) }");

    tableView.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    tableView.setDragEnabled(true);
    tableView.setAcceptDrops(true);
    tableView.setDropIndicatorShown(true);
}
