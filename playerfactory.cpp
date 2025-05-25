#include "playerfactory.h"

Player* PlayerFactory::createPlayer(int id, const QString& name, const QString& role)
{
    if (role == "Guard")
        return new Player(id, name, 90.0f, 85.0f, 80.0f);
    if (role == "Forward")
        return new Player(id, name, 80.0f, 80.0f, 85.0f);
    if (role == "Center")
        return new Player(id, name, 70.0f, 75.0f, 90.0f);
    return nullptr;
}
