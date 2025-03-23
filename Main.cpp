#include <iostream>
#include "Game.h"
#include "GameSettings.h"

int main() {
    // Настройки игры
    GameSettings settings(10, 10, 15); // Ширина, высота, условие победы
    Game game(settings, "Игрок 1");
    game.play(); // Запуск игры
    return 0;
}
