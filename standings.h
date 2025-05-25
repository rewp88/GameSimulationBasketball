#ifndef STANDINGS_H
#define STANDINGS_H

#include <QVector>
#include "basketballteam.h"
#include "match.h"

struct StandingsRecord
{
    BasketballTeam* team;
    int gamesPlayed = 0;
    int wins = 0;
    int losses = 0;
    int pointsScored = 0;
    int pointsConceded = 0;

    StandingsRecord(BasketballTeam* t) : team(t) {}
};

class Standings
{
public:
    void clear();
    void addTeam(BasketballTeam* team);
    void updateStandings(Match* match);

    QVector<StandingsRecord*> getSortedRecords() const;

private:
    QVector<StandingsRecord> m_records;

    StandingsRecord* findRecord(BasketballTeam* team);
};

#endif // STANDINGS_H
