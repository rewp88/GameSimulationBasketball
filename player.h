#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    Player(int id, const QString& name, float speed, float accuracy, float stamina);

    QString getName() const;
    float getSpeed() const;
    float getAccuracy() const;
    float getStamina() const;

private:
    int m_id;
    QString m_name;
    float m_speed;
    float m_accuracy;
    float m_stamina;
};

#endif // PLAYER_H
