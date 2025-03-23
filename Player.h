#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& name) : name(name), score(0) {}

    std::string getName() const { return name; }
    int getScore() const { return score; }

    void updateScore(int points) {
        score += points;
    }
};

#endif // PLAYER_H
