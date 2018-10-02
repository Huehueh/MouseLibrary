#include "Directions.h"

namespace Direction {

eAbsolute Rotate(eAbsolute side, eRelative dir)
{
    auto newSide = static_cast<int>(side) + static_cast<int>(dir);
    if (newSide < 0)
        newSide += 4;
    if (newSide > 3)
        newSide -= 4;
    return static_cast<eAbsolute>(newSide);
}

eRelative GetDirection(eAbsolute myDirection, eAbsolute newDirection)
{
    auto diffrence = static_cast<int>(newDirection) - static_cast<int>(myDirection);
    return static_cast<eRelative>(diffrence);
}
}
