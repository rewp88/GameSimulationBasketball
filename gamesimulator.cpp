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

        for (int i = 0; i < eventsCount; ++i)
        {

            BasketballTeam* attackingTeam = (std::rand() % 2) == 0 ? home : away;
            BasketballTeam* defendingTeam = (attackingTeam == home) ? away : home;

            auto players = attackingTeam->getPlayers();

            if (players.isEmpty())
            {
                logDialog->appendLog(QString("Команда %1 не имеет игроков! Пропуск события.").arg(attackingTeam->getName()));
                continue;
            }

            // случ игрока из атакующей команды
            Player* attacker = players[std::rand() % players.size()];

            int action = std::rand() % 100;
            QString eventDesc;

            if (action < 40) // шанс заколотить в колечко
            {
                // успех зависит от точности игрока и атаки команды
                bool scored = (std::rand() % 100) < (int)(attacker->getAccuracy() * 0.7 + attackingTeam->getOffense() * 0.3);
                int points = (std::rand() % 100) < 30 ? 3 : 2;

                if (scored)
                {
                    eventDesc = QString("%1 забивает %2 очка").arg(attacker->getName()).arg(points);
                    if (attackingTeam == home)
                        homeScore += points;
                    else
                        awayScore += points;
                }
                else
                {
                    eventDesc = QString("%1 промахивается с броска").arg(attacker->getName());
                }
            }
            else if (action < 60) // пас
            {
                eventDesc = QString("%1 делает пас").arg(attacker->getName());
            }
            else if (action < 75) // блок
            {
                auto defenders = defendingTeam->getPlayers();
                if (!defenders.isEmpty())
                {
                    Player* defender = defenders[std::rand() % defenders.size()];
                    eventDesc = QString("Блок от защитника %1").arg(defender->getName());
                }
                else
                {
                    eventDesc = QString("Защитников нет для блока");
                }
            }
            else if (action < 90) // потеря мяча
            {
                eventDesc = QString("%1 теряет мяч").arg(attacker->getName());
            }
            else // фол
            {
                eventDesc = QString("%1 совершает фол").arg(attacker->getName());
            }

            logDialog->appendLog(eventDesc);
        }

        logDialog->appendLog(QString("Счёт после четверти %1: %2 : %3").arg(quarter).arg(homeScore).arg(awayScore));
    }

    m_match->setScore(homeScore, awayScore);
    m_match->setFinished(true);

    logDialog->appendLog(QString("Матч завершён! Итоговый счёт: %1 : %2").arg(homeScore).arg(awayScore));

    emit matchFinished(m_match);
}
