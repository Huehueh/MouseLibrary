#include "cPosition.h"
#include "Directions.h"

cPosition::cPosition(int x, int y, bool initial)
    : mX { x }
    , mY { y }
    , mInitial(initial)
{
}

cPosition::cPosition()
    : cPosition(0, 0, true)
{
}

cPosition::~cPosition() {}

bool cPosition::operator==(const cPosition& pos)
{
    if (mX == pos.X() && mY == pos.Y()) {
        return true;
    } else {
        return false;
    }
}

bool operator<(const cPosition& pos1, const cPosition& pos2)
{
    auto deltaX = pos2.X() - pos1.X();
    auto deltaY = pos2.Y() - pos1.Y();
    if (deltaX >= 0 && deltaY >= 0 && (deltaX + deltaY) > 0) {
        return true;
    } else {
        return false;
    }

    /* if (pos1.X() * pos1.Y() < pos2.X() * pos2.Y()) {
        return true;
    } else {
        return false;
    }*/
}

cPosition cPosition::Neighbour(Direction::eAbsolute direction) const
{
    switch (direction) {
    case Direction::eAbsolute::South: {
        return cPosition(mX, mY - 1);
    }
    case Direction::eAbsolute::North: {
        return cPosition(mX, mY + 1);
    }
    case Direction::eAbsolute::West: {
        return cPosition(mX - 1, mY);
    }
    case Direction::eAbsolute::East:
    default: {
        return cPosition(mX + 1, mY);
    }
    }
}

Direction::eAbsolute cPosition::DirectionOf(const cPosition& position) const
{
    if (position.X() < mX) {
        return Direction::eAbsolute::West;
    } else if (position.X() > mX) {
        return Direction::eAbsolute::East;
    } else if (position.Y() < mY) {
        return Direction::eAbsolute::South;
    } else if (position.Y() > mY) {
        return Direction::eAbsolute::North;
    } else {
        return Direction::eAbsolute::None;
    }
}
