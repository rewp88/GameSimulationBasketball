#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "player.h"
#include <QString>

class PlayerFactory {
public:
    static Player* createPlayer(int id, const QString& name, const QString& role);
};

#endif // PLAYERFACTORY_H
