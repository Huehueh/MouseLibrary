#pragma once

namespace Direction {
enum class eAbsolute;
enum class eRelative;
}

class cPosition {

public:
    cPosition(int x, int y, bool initial = false);
    cPosition();
    ~cPosition();
    bool operator==(const cPosition& pos);
    friend bool operator<(const cPosition& pos1, const cPosition& pos2);

    inline int X() const { return mX; }
    inline int Y() const { return mY; }
    inline bool Initial() const { return mInitial; }

    cPosition Neighbour(Direction::eAbsolute direction) const;
    Direction::eAbsolute DirectionOf(const cPosition& position) const;

private:
    int mX, mY;
    bool mInitial;
};
