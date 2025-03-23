#ifndef MOVE_H
#define MOVE_H

#include "Cell.h"

class Move {
private:
    Cell from;
    Cell to;

public:
    Move(const Cell& from, const Cell& to) : from(from), to(to) {}

    Cell getFrom() const { return from; }
    Cell getTo() const { return to; }
};

#endif // MOVE_H
