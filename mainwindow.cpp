#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerfactory.h"
#include "gamesimulator.h"
#include "matchlogdialog.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_standingsObserver(nullptr)
{
    ui->setupUi(this);
    m_teamsModel = new QStandardItemModel(this);
    m_teamsModel->setHorizontalHeaderLabels({"Команды"});
    ui->teamsList->setModel(m_teamsModel);

    m_playersModel = new QStandardItemModel(this);
    m_playersModel->setHorizontalHeaderLabels({"Имя", "Скорость", "Точность", "Выносливость"});
    ui->playersTable->setModel(m_playersModel);

    m_matchesModel = new QStandardItemModel(this);
    m_matchesModel->setHorizontalHeaderLabels({"Матч", "Счёт"});
    ui->matchesTable->setModel(m_matchesModel);

    m_standingsModel = new QStandardItemModel(this);
    m_standingsModel->setHorizontalHeaderLabels({"Команда", "Игры", "Победы", "Поражения", "Очки", "Пропущено"});
    ui->standingsTable->setModel(m_standingsModel);

    m_standingsObserver = new StandingsObserver(&m_standings, this);

    connect(ui->addTeamButton, &QPushButton::clicked, this, &MainWindow::onAddTeam);
    connect(ui->addPlayerButton, &QPushButton::clicked, this, &MainWindow::onAddPlayer);
    connect(ui->simulateMatchButton, &QPushButton::clicked, this, &MainWindow::onSimulateMatch);

    connect(ui->teamsList->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::onTeamSelectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_teams);
    qDeleteAll(m_matches);
}
