#ifndef DIRECTIONS
#define DIRECTIONS

#include <stdlib.h>

namespace Direction {

enum class eAbsolute {
    West = 0,
    North = 1,
    East = 2,
    South = 3,
    None = 100
};

enum class eRelative {
    Left = -1,
    Straight = 0,
    Right = 1,
    Back = 2
};

eAbsolute Rotate(eAbsolute side, eRelative dir);

eRelative GetDirection(eAbsolute myDirection, eAbsolute newDirection);
}

#endif // DIRECTIONS
