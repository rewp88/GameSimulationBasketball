#include "gamesimulator.h"

GameSimulator::GameSimulator(Match* match, QObject* parent)
    : QObject(parent), m_match(match)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameSimulator::simulateMatchWithLog(MatchLogDialog* logDialog)
{
    BasketballTeam* home = m_match->getHomeTeam();
    BasketballTeam* away = m_match->getAwayTeam();

    logDialog->appendLog(QString("Матч %1 vs %2 начинается").arg(home->getName(), away->getName()));

    int homeScore = 0;
    int awayScore = 0;

    for (int quarter = 1; quarter <= 4; ++quarter)
    {
        logDialog->appendLog(QString("Четверть %1").arg(quarter));

        int eventsCount = 10 + (std::rand() % 11);
