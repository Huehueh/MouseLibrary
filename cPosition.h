#pragma once

class cPosition {
public:
    cPosition(int x, int y, bool initial = false);
    cPosition();
    ~cPosition();

    inline int X() const { return mX; }
    inline int Y() const { return mY; }
    inline bool Initial() const { return mInitial; }

private:
    int mX, mY;
    bool mInitial;
};
