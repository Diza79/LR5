#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject {
private:
    int x;
    int y;
    char type;

public:
    GameObject(int x, int y, char type) : x(x), y(y), type(type) {}

    char getType() const { return type; }
    void setPosition(const Cell& cell) { x = cell.getX(); y = cell.getY(); }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
        os << obj.type;
        return os;
    }
};

#endif // GAMEOBJECT_H
