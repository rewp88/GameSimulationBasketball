#include "standings.h"
#include <algorithm>

void Standings::clear()
{
    m_records.clear();
}

void Standings::addTeam(BasketballTeam* team)
{
    m_records.append(StandingsRecord(team));
}

StandingsRecord* Standings::findRecord(BasketballTeam* team)
{
    for (auto& record : m_records)
    {
        if (record.team == team)
            return &record;
    }
    return nullptr;
}

void Standings::updateStandings(Match* match)
{
    if (!match->isFinished())
        return;

    StandingsRecord* homeRecord = findRecord(match->getHomeTeam());
    StandingsRecord* awayRecord = findRecord(match->getAwayTeam());

    if (!homeRecord || !awayRecord)
        return;

    homeRecord->gamesPlayed++;
    awayRecord->gamesPlayed++;

    int homeScore = match->getScore().homePoints;
    int awayScore = match->getScore().awayPoints;

    homeRecord->pointsScored += homeScore;
    homeRecord->pointsConceded += awayScore;

    awayRecord->pointsScored += awayScore;
    awayRecord->pointsConceded += homeScore;

    if (homeScore > awayScore)
    {
        homeRecord->wins++;
        awayRecord->losses++;
    }
    else if (awayScore > homeScore)
    {
        awayRecord->wins++;
        homeRecord->losses++;
    }
}

QVector<StandingsRecord*> Standings::getSortedRecords() const
{
    QVector<StandingsRecord*> recordsPtrs;
    for (auto& rec : m_records)
        recordsPtrs.append(const_cast<StandingsRecord*>(&rec));

    std::sort(recordsPtrs.begin(), recordsPtrs.end(), [](StandingsRecord* a, StandingsRecord* b) {
        return a->wins > b->wins; // сортировка по победам
    });

    return recordsPtrs;
}
