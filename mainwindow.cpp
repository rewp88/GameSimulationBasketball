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

    ui->teamsList->verticalHeader()->hide();
    ui->playersTable->verticalHeader()->hide();
    ui->matchesTable->verticalHeader()->hide();
    ui->standingsTable->verticalHeader()->hide();

    ui->teamsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->playersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->matchesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->standingsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->standingsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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

void MainWindow::onAddTeam()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, "Добавить команду", "Название команды:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;

    BasketballTeam* team = new BasketballTeam(m_teams.size(), name, 50, 50, 50);
    m_teams.append(team);

    updateTeamsView();
    createMatches();
}

void MainWindow::onAddPlayer()
{
    if (m_teams.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Добавьте команду прежде, чем добавлять игроков");
        return;
    }

    bool ok = false;
    QString name = QInputDialog::getText(this, "Добавить игрока", "Имя игрока:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;

    QStringList roles = {"Guard", "Forward", "Center"};
    QString role = QInputDialog::getItem(this, "Выберите роль", "Роль:", roles, 0, false, &ok);
    if (!ok || role.isEmpty())
        return;

    QModelIndex currentIndex = ui->teamsList->currentIndex();
    if (!currentIndex.isValid())
    {
        QMessageBox::warning(this, "Ошибка", "Выберите команду для добавления игрока");
        return;
    }
    BasketballTeam* team = m_teams[currentIndex.row()];

    Player* player = PlayerFactory::createPlayer(team->getPlayers().size(), name, role);
    if (!player)
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать игрока");
        return;
    }

    team->addPlayer(player);

    updatePlayersView(team);
}

void MainWindow::onTeamSelectionChanged(const QModelIndex& current, const QModelIndex& /*previous*/)
{
    if (!current.isValid())
    {
        m_playersModel->clear();
        return;
    }

    BasketballTeam* team = m_teams[current.row()];
    updatePlayersView(team);
}

void MainWindow::updateTeamsView()
{
    m_teamsModel->removeRows(0, m_teamsModel->rowCount());
    for (BasketballTeam* team : m_teams)
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(team->getName());
        m_teamsModel->appendRow(row);
    }
}

void MainWindow::updatePlayersView(BasketballTeam* team)
{
    m_playersModel->clear();
    m_playersModel->setHorizontalHeaderLabels({"Имя", "Скорость", "Точность", "Выносливость"});

    if (!team) return;

    for (Player* p : team->getPlayers())
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(p->getName())
            << new QStandardItem(QString::number(p->getSpeed()))
            << new QStandardItem(QString::number(p->getAccuracy()))
            << new QStandardItem(QString::number(p->getStamina()));
        m_playersModel->appendRow(row);
    }
}

void MainWindow::createMatches()
{
    qDeleteAll(m_matches);
    m_matches.clear();

    for (int i = 0; i < m_teams.size(); ++i)
    {
        for (int j = i + 1; j < m_teams.size(); ++j)
        {
            Match* match = new Match(m_matches.size(), m_teams[i], m_teams[j], QDateTime::currentDateTime(), this);
            connect(match, &Match::matchFinished, m_standingsObserver, &StandingsObserver::onMatchFinished);
            m_matches.append(match);
        }
    }

    updateMatchesView();
    updateStandingsView();
}

void MainWindow::updateMatchesView()
{
    m_matchesModel->removeRows(0, m_matchesModel->rowCount());
    for (Match* match : m_matches)
    {
        QList<QStandardItem*> row;
        QString matchName = QString("%1 vs %2").arg(match->getHomeTeam()->getName(), match->getAwayTeam()->getName());
        QString score = match->isFinished() ? match->getScore().getScoreString() : "Ожидает";
        row << new QStandardItem(matchName) << new QStandardItem(score);
        m_matchesModel->appendRow(row);
    }
}

void MainWindow::updateStandingsView()
{
    m_standingsModel->removeRows(0, m_standingsModel->rowCount());
    auto records = m_standings.getSortedRecords();
    for (auto record : records)
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(record->team->getName())
            << new QStandardItem(QString::number(record->gamesPlayed))
            << new QStandardItem(QString::number(record->wins))
            << new QStandardItem(QString::number(record->losses))
            << new QStandardItem(QString::number(record->pointsScored))
            << new QStandardItem(QString::number(record->pointsConceded));
        m_standingsModel->appendRow(row);
    }
}

void MainWindow::onSimulateMatch()
{
    if (m_matches.isEmpty())
    {
        QMessageBox::information(this, "Информация", "Нет матчей для симуляции");
        return;
    }

    if (m_currentMatchIndex >= m_matches.size())
    {
        QMessageBox::information(this, "Информация", "Все матчи уже симулированы");
        return;
    }

    Match* match = m_matches[m_currentMatchIndex];

    MatchLogDialog* logDialog = new MatchLogDialog(this);
    GameSimulator* simulator = new GameSimulator(match);

    connect(simulator, &GameSimulator::matchFinished, this, [this, simulator, logDialog]() {
        updateMatchesView();
        updateStandingsView();

        simulator->deleteLater();
        logDialog->accept();

        m_currentMatchIndex++; // некст матч

        if (m_currentMatchIndex < m_matches.size())
        {
            onSimulateMatch();
        }
        else
        {
            QMessageBox::information(this, "Информация", "Все матчи симулированы");
        }
    });

    simulator->simulateMatchWithLog(logDialog);
    logDialog->exec();
}

