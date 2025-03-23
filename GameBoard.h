#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "GameObject.h"

class GameBoard {
private:
    int width;
    int height;
    std::vector<std::vector<GameObject*>> board;

public:
    GameBoard(int width, int height) : width(width), height(height) {
        board.resize(height, std::vector<GameObject*>(width, nullptr));
    }

    ~GameBoard() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete board[i][j]; // Освобождаем память
            }
        }
    }

    void setCell(int x, int y, GameObject* obj) {
        board[x][y] = obj;
    }

    GameObject* getCell(int x, int y) {
        return board[x][y];
    }

    bool isValidMove(const Cell& from, const Cell& to) {
        // Проверка, что координаты находятся в пределах игрового поля
        if (from.getX() < 0 || from.getX() >= height || from.getY() < 0 || from.getY() >= width ||
            to.getX() < 0 || to.getX() >= height || to.getY() < 0 || to.getY() >= width) {
            return false;
        }
        // Проверка, что клетка назначения пуста
        return board[to.getX()][to.getY()] == nullptr;
    }

    void displayBoard() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (board[i][j]) {
                    std::cout << board[i][j]->getType() << " "; // Отображаем тип объекта
                } else {
                    std::cout << ". "; // Пустая клетка
                }
            }
            std::cout << std::endl;
        }
    }
};

#endif // GAMEBOARD_H
