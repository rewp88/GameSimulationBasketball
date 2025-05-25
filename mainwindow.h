#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include "basketballteam.h"
#include "match.h"
#include "standings.h"
#include "standingsobserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTeam();
    void onAddPlayer();
    void onSimulateMatch();
    void onTeamSelectionChanged(const QModelIndex& current, const QModelIndex& previous);

private:
    Ui::MainWindow *ui;

    QStandardItemModel* m_teamsModel;
    QStandardItemModel* m_playersModel;
    QStandardItemModel* m_matchesModel;
    QStandardItemModel* m_standingsModel;

    QVector<BasketballTeam*> m_teams;
    QVector<Match*> m_matches;

    Standings* m_standings;
    StandingsObserver* m_standingsObserver;

    void updateTeamsView();
    void updatePlayersView(BasketballTeam* team);
    void updateMatchesView();
    void updateStandingsView();
    void createMatches();
    int m_currentMatchIndex = 0;
};

#endif // MAINWINDOW_H
