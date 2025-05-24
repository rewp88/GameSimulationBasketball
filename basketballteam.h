#ifndef BASKETBALLTEAM_H
#define BASKETBALLTEAM_H

#include <QString>
#include <QVector>
#include "player.h"

class BasketballTeam {
public:
    BasketballTeam(int id, const QString& name, float morale, float offense, float defense);
    ~BasketballTeam();

    QString getName() const;
    float getMorale() const;
    float getOffense() const;
    float getDefense() const;

    void addPlayer(Player* player);
    QVector<Player*> getPlayers() const;

private:
    int m_id;
    QString m_name;
    float m_morale;
    float m_offense;
    float m_defense;
    QVector<Player*> m_players;
};

#endif // BASKETBALLTEAM_H
