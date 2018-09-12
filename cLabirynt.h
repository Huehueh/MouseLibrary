#pragma once

#include "cPosition.h"

static int MAX_SIZE = 20;
static int MIN_SIZE = 6;

struct sCell {
    sCell()
        : visited(0)
        , willComeBack(false)
        , exits(0)
        , n(-1)
        , s(-1)
        , w(-1)
        , e(-1)
    {
    }
    int visited;
    bool willComeBack;
    bool endOfRoute;
    int exits;
    int n, s, w, e; // czy sa sciany 1 -jest, 0 - nie ma, -1 - nie wiadomo
};

enum class eDirection {
    N,
    W,
    E,
    S
};

class cLabirynt {
public:
    cLabirynt(int width, int height);
    ~cLabirynt();

    static bool CheckSize(int size);
    bool IsCenter(const cPosition& position);

    void Set(const cPosition& position, eDirection mouseDirection, bool left, bool right, bool front);
    //void WhereToGo(const cPosition& position, bool& goLeft, bool& goRight, bool& goFront);
    bool IsNode(const cPosition& position);

private:
    sCell** myCells;
    int mWidth;
    int mHeight;
};
