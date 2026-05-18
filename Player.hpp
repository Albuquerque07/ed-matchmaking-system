#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
using namespace std;

class Player {

private:
    int id;
    string name;
    int score;
    int timestamp;

public:

    Player();
    Player(int id, string name, int score, int timestamp);
    ~Player();

    int getId();
    string getName();
    int getScore();
    int getTimestamp();
};

#endif