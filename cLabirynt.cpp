#include "cLabirynt.h"

cLabirynt::cLabirynt(int width, int height)
    : mWidth(width)
    , mHeight(height)
{
    myCells = new sCell*[mWidth];
    for (int i = 0; i < mWidth; i++) {
        myCells[i] = new sCell[mHeight];
    }
}

cLabirynt::~cLabirynt() {}

bool cLabirynt::CheckSize(int size)
{
    if (size > MAX_SIZE || size < MIN_SIZE) {

        return false;
    }
    if (size % 2 != 0) {
        return false;
    }
    return true;
}

bool cLabirynt::IsCenter(const cPosition& position)
{
    if (position.X() != static_cast<int>(mWidth / 2) || position.X() != static_cast<int>(mWidth / 2) - 1)
        return false;
    if (position.Y() != static_cast<int>(mHeight / 2) || position.Y() != static_cast<int>(mHeight / 2) - 1)
        return true;
    return false;
}

void cLabirynt::Set(const cPosition& position, eDirection mouseDirection, bool left, bool right, bool front)
{
    auto x = position.X();
    auto y = position.Y();
    myCells[x][y].visited++;

    switch (mouseDirection) {
    case eDirection::N: {
        myCells[x][y].w = static_cast<int>(left);
        myCells[x][y].n = static_cast<int>(front);
        myCells[x][y].e = static_cast<int>(right);
        if (position.Initial() == false) {
            myCells[x][y].s = 0; // nie bylo sciany skad przyszlam, chyba ze to pierwsza komorka
        } else {
            myCells[x][y].s = 1;
        }
        break;
    }
    case eDirection::S: {
        myCells[x][y].e = static_cast<int>(left);
        myCells[x][y].s = static_cast<int>(front);
        myCells[x][y].w = static_cast<int>(right);
        if (position.Initial() == false) {
            myCells[x][y].n = 0; // nie bylo sciany skad przyszlam, chyba ze to pierwsza komorka
        } else {
            myCells[x][y].n = 1;
        }
        break;
    }
    case eDirection::W: {
        myCells[x][y].s = static_cast<int>(left);
        myCells[x][y].w = static_cast<int>(front);
        myCells[x][y].n = static_cast<int>(right);
        if (position.Initial() == false) {
            myCells[x][y].e = 0; // nie bylo sciany skad przyszlam, chyba ze to pierwsza komorka
        } else {
            myCells[x][y].e = 1;
        }
        break;
    }
    case eDirection::E: {
        myCells[x][y].n = static_cast<int>(left);
        myCells[x][y].e = static_cast<int>(front);
        myCells[x][y].s = static_cast<int>(right);
        if (position.Initial() == false) {
            myCells[x][y].w = 0; // nie bylo sciany skad przyszlam, chyba ze to pierwsza komorka
        } else {
            myCells[x][y].w = 1;
        }
        break;
    }
    }

    myCells[x][y].exits = static_cast<int>(left) + static_cast<int>(right) + static_cast<int>(front);
    if (myCells[x][y].exits > 1) {
        myCells[x][y].willComeBack = true;
    } else if (myCells[x][y].exits == 0) {
        myCells[x][y].endOfRoute = true;
    }
}

//void cLabirynt::WhereToGo(const cPosition& position, bool& goLeft, bool& goRight, bool goFront)
//{
//
//}

bool cLabirynt::IsNode(const cPosition& position)
{
    auto x = position.X();
    auto y = position.Y();
    if (myCells[x][y].endOfRoute || myCells[x][y].endOfRoute || position.Initial()) {
        return true;
    }
    return false;
}
