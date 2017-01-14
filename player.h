#ifndef PLAYER_H
#define PLAYER_H

#include <QStringList>
#include <QString>
#include <QDebug>
#include <parser.h>

class Player
{
public:
    int hp;
    int money;
    int force;
    int oratory;
    int pointer;

    Player();

    void saveProgress();
    void loadProgress();
};

#endif // PLAYER_H
