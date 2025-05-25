#ifndef GAMESIMULATOR_H
#define GAMESIMULATOR_H

#include <QObject>
#include "match.h"
#include "matchlogdialog.h"
#include <cstdlib>
#include <ctime>

class GameSimulator : public QObject {
    Q_OBJECT
public:
    explicit GameSimulator(Match* match, QObject* parent = nullptr);
    void simulateMatchWithLog(MatchLogDialog* logDialog);

signals:
    void matchFinished(Match* match);

private:
    Match* m_match;
};

#endif // GAMESIMULATOR_H
