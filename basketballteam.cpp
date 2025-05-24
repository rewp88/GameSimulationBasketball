#include "basketballteam.h"

BasketballTeam::BasketballTeam(int id, const QString& name, float morale, float offense, float defense)
    : m_id(id), m_name(name), m_morale(morale), m_offense(offense), m_defense(defense)
{
}

BasketballTeam::~BasketballTeam()
{
    qDeleteAll(m_players);
    m_players.clear();
}

QString BasketballTeam::getName() const {
    return m_name;
}
float BasketballTeam::getMorale() const {
    return m_morale;
}
float BasketballTeam::getOffense() const {
    return m_offense;
}
float BasketballTeam::getDefense() const {
    return m_defense;
}

void BasketballTeam::addPlayer(Player* player)
{
    if (player)
        m_players.append(player);
}

QVector<Player*> BasketballTeam::getPlayers() const
{
    return m_players;
}
