#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

class GameSettings {
private:
    int width;
    int height;
    int winCondition;

public:
    GameSettings(int width, int height, int winCondition) 
        : width(width), height(height), winCondition(winCondition) {}

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getWinCondition() const { return winCondition; }
};

#endif // GAMESETTINGS_H
