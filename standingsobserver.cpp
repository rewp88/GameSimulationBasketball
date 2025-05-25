#include "standingsobserver.h"

StandingsObserver::StandingsObserver(Standings* standings, QObject* parent)
    : QObject(parent), m_standings(standings)
{
}

void StandingsObserver::onMatchFinished(Match* match)
{
    m_standings->updateStandings(match);
}
