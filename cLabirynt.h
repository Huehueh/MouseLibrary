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

enum class eState {
    Wall,
    AlreadyVisited,
    EndOfRoute,
    FreeToGo,
    Unknown
};

class cLabirynt {
public:
    cLabirynt(int width, int height);
    ~cLabirynt();

    static bool CheckSize(int size);
    bool IsCenter(const cPosition& position) const;
    inline eState Right() const
    {
        return rightState;
    }
    eState Left() const
    {
        return leftState;
    }
    eState Front() const
    {
        return frontState;
    }

    void Set(const cPosition& position, eDirection mouseDirection, bool left, bool right, bool front);
    //void WhereToGo(const cPosition& position, bool& goLeft, bool& goRight, bool& goFront);
    bool IsNode(const cPosition& position);

private:
    void SetState(const cPosition& nPos, eState& state, bool wall) const;

    sCell** myCells;
    int mWidth;
    int mHeight;

    eState rightState = eState::Unknown;
    eState leftState = eState::Unknown;
    eState frontState = eState::Unknown;
};
