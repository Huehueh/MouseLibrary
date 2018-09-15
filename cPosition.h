#pragma once

enum class eDirection {
    N,
    W,
    E,
    S
};

class cPosition {
public:
    cPosition(int x, int y, bool initial = false);
    cPosition();
    ~cPosition();

    inline int X() const { return mX; }
    inline int Y() const { return mY; }
    inline bool Initial() const { return mInitial; }

    cPosition Neighbour(eDirection direction);

private:
    int mX, mY;
    bool mInitial;
};
