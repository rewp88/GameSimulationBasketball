#include "match.h"

Match::Match(int id, BasketballTeam* home, BasketballTeam* away, QDateTime date, QObject* parent)
    : QObject(parent), m_id(id), m_homeTeam(home), m_awayTeam(away), m_date(date), m_isFinished(false)
{
}

int Match::getId() const {

    return m_id;
}
BasketballTeam* Match::getHomeTeam() const {

    return m_homeTeam;
}
BasketballTeam* Match::getAwayTeam() const {

    return m_awayTeam;
}
QDateTime Match::getDate() const {

    return m_date;
}

bool Match::isFinished() const {

    return m_isFinished;
}
void Match::setFinished(bool finished) {
    m_isFinished = finished;
    if (finished) emit matchFinished(this);
}

int Match::getHomeScore() const {

    return m_score.homePoints;
}
int Match::getAwayScore() const {

    return m_score.awayPoints;
}
void Match::setScore(int home, int away) {
    m_score.homePoints = home;
    m_score.awayPoints = away;
}
Score Match::getScore() const {

    return m_score;
}
