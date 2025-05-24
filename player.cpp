#include "player.h"

Player::Player(int id, const QString& name, float speed, float accuracy, float stamina)
    : m_id(id), m_name(name), m_speed(speed), m_accuracy(accuracy), m_stamina(stamina)
{

}

QString Player::getName() const {
    return m_name;
}

float Player::getSpeed() const {
    return m_speed;
}

float Player::getAccuracy() const {
    return m_accuracy;
}

float Player::getStamina() const {
    return m_stamina;
}
