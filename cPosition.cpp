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
