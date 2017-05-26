#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
namespace std{
class player
{
public:
    player();
    player(string id);
    string playerId;
    int score=0;
    int totalTime=0;

};
}
#endif // PLAYER_H






