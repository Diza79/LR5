#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int x; // Координата по оси X
    int y; // Координата по оси Y

public:
    Cell(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif // CELL_H
