#ifndef STANDINGSOBSERVER_H
#define STANDINGSOBSERVER_H

#include <QObject>
#include "standings.h"
#include "match.h"

class StandingsObserver : public QObject {
    Q_OBJECT
public:
    explicit StandingsObserver(Standings* standings, QObject* parent = nullptr);

public slots:
    void onMatchFinished(Match* match);

private:
    Standings* m_standings;
};

#endif // STANDINGSOBSERVER_H
