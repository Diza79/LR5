#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int currentScore;
    int highScore;
    int moveCount;

public:
    Score() : currentScore(0), highScore(0), moveCount(0) {}

    void updateScore(int score) {
        currentScore += score;
        if (currentScore > highScore) {
            highScore = currentScore;
        }
    }

    int getCurrentScore() const { return currentScore; }
    int getHighScore() const { return highScore; }
    void incrementMoveCount() { moveCount++; }
    int getMoveCount() const { return moveCount; }
};

#endif // SCORE_H
