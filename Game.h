#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "GameBoard.h"
#include "Player.h"
#include "Score.h"
#include "GameSettings.h"
#include "Cell.h"
#include "GameObject.h"

class Game {
private:
    std::unique_ptr<GameBoard> board; // Уникальный указатель на игровое поле
    std::shared_ptr<Player> player; // Разделяемый указатель на игрока
    Score score; // Счет
    GameSettings settings; // Настройки игры
    bool isGameOver; // Флаг окончания игры
    std::default_random_engine random; // Генератор случайных чисел

    // Генерация случайной буквы
    GameObject* generateRandomLetter() {
        char letter = 'A' + (rand() % 7); // Генерация случайной буквы от A до G
        return new GameObject(0, 0, letter);
    }

    void initializeBoard() {
        // Заполнение поля случайными буквами
        for (int i = 0; i < settings.getHeight(); i++) {
            for (int j = 0; j < settings.getWidth(); j++) {
                board->setCell(i, j, generateRandomLetter());
            }
        }
    }

    bool checkForTrio() {
        // Проверка на наличие трио
        bool foundTrio = false;

        // Проверка по горизонтали
        for (int i = 0; i < settings.getHeight(); i++) {
            for (int j = 0; j < settings.getWidth() - 2; j++) {
                GameObject first = board->getCell(i, j);
                GameObject second = board->getCell(i, j + 1);
                GameObject third = board->getCell(i, j + 2);
                if (first.getType() == second.getType() && first.getType() == third.getType() && first.getType() != '.') {
                    foundTrio = true;
                    // Удаляем трио
                    board->setCell(i, j, GameObject(i, j, '.'));
                    board->setCell(i, j + 1, GameObject(i, j + 1, '.'));
                    board->setCell(i, j + 2, GameObject(i, j + 2, '.'));
                }
            }
        }

        // Проверка по вертикали
        for (int j = 0; j < settings.getWidth(); j++) {
            for (int i = 0; i < settings.getHeight() - 2; i++) {
                GameObject first = board->getCell(i, j);
                GameObject second = board->getCell(i + 1, j);
                GameObject third = board->getCell(i + 2, j);
                if (first.getType() == second.getType() && first.getType() == third.getType() && first.getType() != '.') {
                    foundTrio = true;
                    // Удаляем трио
                    board->setCell(i, j, GameObject(i, j, '.'));
                    board->setCell(i + 1, j, GameObject(i + 1, j, '.'));
                    board->setCell(i + 2, j, GameObject(i + 2, j, '.'));
                }
            }
        }

        return foundTrio;
    }

    void generateNewLetters() {
        // Обновляем поле, чтобы буквы падали вниз
        for (int j = 0; j < settings.getWidth(); j++) {
            for (int i = settings.getHeight() - 1; i >= 0; i--) {
                if (board->getCell(i, j).getType() == '.') {
                    // Сдвигаем буквы вниз
                    for (int k = i - 1; k >= 0; k--) {
                        GameObject letter = board->getCell(k, j);
                        if (letter.getType() != '.') {
                            board->setCell(i, j, letter); // Перемещаем букву вниз
                            board->setCell(k, j, GameObject(k, j, '.')); // Освобождаем старую позицию
                            break;
                        }
                    }
                    // Генерация новых букв для пустых клеток
                    if (board->getCell(i, j).getType() == '.') {
                        board->setCell(i, j, generateRandomLetter());
                    }
                }
            }
        }
        
        // Проверяем наличие трио после генерации новых букв
        if (checkForTrio()) {
            score.updateScore(1); // Обновляем счет, если нашли трио
            generateNewLetters(); // Рекурсивно вызываем, если снова есть трио
        }
    }

public:
    // Конструктор игры
    Game(const GameSettings& settings, const std::string& playerName) 
        : settings(settings), isGameOver(false),
          board(std::make_unique<GameBoard>(settings.getWidth(), settings.getHeight())),
          player(std::make_shared<Player>(playerName)) {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализация генератора случайных чисел
        initializeBoard(); // Инициализация игрового поля
    }

    // Отображение информации об игре
    void display() {
        std::cout << "Игрок: " << player->getName() << std::endl;
        std::cout << "Счет: " << score.getCurrentScore() << std::endl;
        std::cout << "Количество ходов: " << score.getMoveCount() << std::endl;
        std::cout << "Игровое поле:" << std::endl;
        board->displayBoard(); // Отображение игрового поля
    }

    // Выполнение хода
    void makeMove(const Cell& from, const Cell& to) {
        // Логика перемещения
        if (board->isValidMove(from, to)) {
            GameObject movingObject = board->getCell(from.getX(), from.getY());
            board->setCell(to.getX(), to.getY(), movingObject); // Перемещаем объект
            board->setCell(from.getX(), from.getY(), GameObject(from.getX(), from.getY(), '.')); // Освобождаем старую позицию
            score.incrementMoveCount(); // Увеличиваем счетчик ходов
            generateNewLetters(); // Генерируем новые буквы после хода
        } else {
            std::cout << "Ошибка: недопустимый ход!" << std::endl;
        }
    }

    // Проверка на победу
    bool checkWin() {
        return score.getCurrentScore() >= settings.getWinCondition();
    }

    // Основной цикл игры
    void play() {
        while (!isGameOver) {
            display(); // Отображаем информацию об игре
            
            // Логика ввода координат и выполнения ходов
            int fromX, fromY, toX, toY;
            std::cout << "Введите координаты клетки, откуда хотите переместить (x y): ";
            std::cin >> fromX >> fromY;
            std::cout << "Введите координаты клетки, куда хотите переместить (x y): ";
            std::cin >> toX >> toY;

            // Создаем объекты Cell для перемещения
            Cell from(fromX, fromY);
            Cell to(toX, toY);

            // Выполняем ход
            makeMove(from, to);

            // Проверяем на победу
            if (checkWin()) {
                std::cout << "Поздравляем! Вы выиграли!" << std::endl;
                isGameOver = true; // Завершаем игру
            }

            // Проверка на окончание игры
            if (score.getMoveCount() >= settings.getMaxMoves()) {
                std::cout << "Игра окончена! Вы исчерпали все ходы." << std::endl;
                isGameOver = true; // Завершаем игру
            }
        }
    }
};

#endif // GAME_H
