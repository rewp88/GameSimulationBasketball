#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class BasketballTeam;
class Match;
class Standings;
class StandingsObserver;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

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

    int m_currentMatchIndex = 0;
};

#endif // MAINWINDOW_H
