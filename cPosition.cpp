#include "cPosition.h"

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

cPosition cPosition::Neighbour(eDirection direction)
{
    switch (direction) {
    case eDirection::S: {
        return cPosition(mX, mY - 1);
    }
    case eDirection::N: {
        return cPosition(mX, mY + 1);
    }
    case eDirection::W: {
        return cPosition(mX - 1, mY);
    }
    case eDirection::E:
    default: {
        return cPosition(mX + 1, mY);
    }
    }
}
