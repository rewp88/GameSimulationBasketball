#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include "basketballteam.h"

struct Score {
    int homePoints = 0;
    int awayPoints = 0;

    inline Score() = default;

    inline QString getScoreString() const {
        return QString("%1 : %2").arg(homePoints).arg(awayPoints);
    }
};

class Match : public QObject {
    Q_OBJECT
public:
    explicit Match(int id,
                   BasketballTeam* home,
                   BasketballTeam* away,
                   QDateTime date = QDateTime::currentDateTime(),
                   QObject* parent = nullptr);

    int getId() const;
    BasketballTeam* getHomeTeam() const;
    BasketballTeam* getAwayTeam() const;
    QDateTime getDate() const;

    bool isFinished() const;
    void setFinished(bool finished);

    int getHomeScore() const;
    int getAwayScore() const;
    void setScore(int home, int away);
    Score getScore() const;

signals:
    void matchFinished(Match* match);

private:
    int m_id;
    BasketballTeam* m_homeTeam;
    BasketballTeam* m_awayTeam;
    QDateTime m_date;
    Score m_score;
    bool m_isFinished;
};

#endif // MATCH_H
