#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <iostream>
#include "GameObject.h"

class GameBoard {
private:
    std::vector<std::vector<GameObject*>> board; // Используем вектор вместо массива

public:
    GameBoard(int width, int height) : board(height, std::vector<GameObject*>(width, nullptr)) {}

    void setCell(int x, int y, GameObject* obj) {
        board[x][y] = obj;
    }

    GameObject* getCell(int x, int y) {
        return board[x][y];
    }

    void displayBoard() {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                std::cout << (cell ? *cell : GameObject(0, 0, '.')) << ' '; // Используем перегруженный оператор
            }
            std::cout << std::endl;
        }
    }
};

#endif // GAMEBOARD_H
