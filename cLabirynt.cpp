#include "cLabirynt.h"
#include "Directions.h"
#include "cPosition.h"
#include <algorithm>
#include <iostream>

cLabirynt::cLabirynt(int width, int height)
    : mWidth(width)
    , mHeight(height)
{
    if (cLabirynt::CheckSize(mWidth) == false) {
        mWidth = MIN_SIZE;
    }
    if (cLabirynt::CheckSize(mHeight) == false) {
        mHeight = MIN_SIZE;
    }

    myCells = new sCell*[mWidth];
    for (auto i = 0; i < mWidth; ++i) {
        myCells[i] = new sCell[mHeight];
        for (auto j = 0; j < mHeight; ++j) {
            myCells[i][j].pos = cPosition(i, j);
            myCells[i][j].distFromCenter = std::sqrt(std::pow((mWidth - 1) / 2 - j, 2) + std::pow((mHeight - 1) / 2 - i, 2));
        }
    }
}

cLabirynt::~cLabirynt()
{
    delete myCells;
}

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

bool cLabirynt::IsCenter(const cPosition& position) const
{
    if (position.X() != static_cast<int>(mWidth / 2) || position.X() != static_cast<int>(mWidth / 2) - 1)
        return false;
    if (position.Y() != static_cast<int>(mHeight / 2) || position.Y() != static_cast<int>(mHeight / 2) - 1)
        return true;
    return false;
}

void cLabirynt::SetWalls(const cPosition& pos, int n, int s, int w, int e)
{
    myCells[pos.X()][pos.Y()].w = w;
    myCells[pos.X()][pos.Y()].n = n;
    myCells[pos.X()][pos.Y()].e = e;
    myCells[pos.X()][pos.Y()].s = s;
    myCells[pos.X()][pos.Y()].walls = w + n + e + s;

    auto markNeighbourCell = [](const sCell& myCell, sCell& nCell) {
        if (myCell.visited == 1) {
            nCell.walls++;
            if (nCell.walls >= 3) {
                nCell.endOfRoute = true;
            }
        }
    };

    //neighbours
    if (pos.X() > 0 && myCells[pos.X() - 1][pos.Y()].visited == 0) {
        myCells[pos.X() - 1][pos.Y()].e = w;
        markNeighbourCell(myCells[pos.X()][pos.Y()], myCells[pos.X() - 1][pos.Y()]);
    }
    if (pos.Y() > 0) {
        myCells[pos.X()][pos.Y() - 1].n = s;
        markNeighbourCell(myCells[pos.X()][pos.Y()], myCells[pos.X()][pos.Y() - 1]);
    }
    if (pos.X() < mWidth - 1) {
        myCells[pos.X() + 1][pos.Y()].w = e;
        markNeighbourCell(myCells[pos.X()][pos.Y()], myCells[pos.X() + 1][pos.Y()]);
    }
    if (pos.Y() < mHeight - 1) {
        myCells[pos.X()][pos.Y() + 1].s = n;
        markNeighbourCell(myCells[pos.X()][pos.Y()], myCells[pos.X()][pos.Y() + 1]);
    }
}

bool cLabirynt::AreNeighbours(const cPosition& pos1, const cPosition& pos2)
{
    auto deltaX = pos1.X() - pos2.X();
    auto deltaY = pos1.Y() - pos2.Y();

    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        return false;
    }
    if (pos1.X() == pos2.X()) {
        if (deltaY == 1) {
            if (myCells[pos1.X()][pos1.Y()].s == 0) {
                return true;
            }
        } else if (deltaY == -1) {
            if (myCells[pos1.X()][pos1.Y()].n == 0) {
                return true;
            }
        }
        return false;
    } else if (pos1.Y() == pos2.Y()) {
        if (deltaX == 1) {
            if (myCells[pos1.X()][pos1.Y()].w == 0) {
                return true;
            }
        } else if (deltaY == -1) {
            if (myCells[pos1.X()][pos1.Y()].e == 0) {
                return true;
            }
        }
        return false;
    }
    return false;
}

void cLabirynt::Set(const cPosition& position, Direction::eAbsolute mouseDirection, bool left, bool right, bool front)
{
    auto x = position.X();
    auto y = position.Y();

    // cell was visited by mouse
    myCells[x][y].visited++;

    //set walls
    auto leftInt = static_cast<int>(left);
    auto rightInt = static_cast<int>(right);
    auto frontInt = static_cast<int>(front);

    switch (mouseDirection) {
    case Direction::eAbsolute::North: {
        SetWalls(position, frontInt, position.Initial() ? 1 : 0, leftInt, rightInt);
        break;
    }
    case Direction::eAbsolute::South: {
        SetWalls(position, position.Initial() ? 1 : 0, frontInt, rightInt, leftInt);
        break;
    }
    case Direction::eAbsolute::West: {
        SetWalls(position, rightInt, leftInt, frontInt, position.Initial() ? 1 : 0);
        break;
    }
    case Direction::eAbsolute::East: {
        SetWalls(position, leftInt, rightInt, position.Initial() ? 1 : 0, frontInt);
        break;
    }
    }
    // how many exits from cell
    auto exits = 3 - (static_cast<int>(left) + static_cast<int>(right) + static_cast<int>(front));

    // three walls - end of route
    if (exits == 0) {
        myCells[x][y].endOfRoute = true;
    }
    // more than one exits - check if they were visited before
    if (exits > 1) {
        auto notVisitedExits = CheckExits(position);
        if (notVisitedExits > 1) {
            myCells[x][y].willComeBack = true;
        }
    }
}

bool cLabirynt::EndOfRoute(const cPosition& position)
{
    return myCells[position.X()][position.Y()].endOfRoute;
}

int cLabirynt::CheckExits(const cPosition& pos)
{
    int counter = 0;
    if (pos.X() > 0 && myCells[pos.X()][pos.Y()].w == 0 && myCells[pos.X() - 1][pos.Y()].visited == 0) {
        counter++;
    }
    if (pos.X() < mWidth - 1 && myCells[pos.X()][pos.Y()].e == 0 && myCells[pos.X() + 1][pos.Y()].visited == 0) {
        counter++;
    }
    if (pos.Y() > 0 && myCells[pos.X()][pos.Y()].s == 0 && myCells[pos.X()][pos.Y() - 1].visited == 0) {
        counter++;
    }
    if (pos.Y() < mHeight - 1 && myCells[pos.X()][pos.Y()].n == 0 && myCells[pos.X()][pos.Y() + 1].visited == 0) {
        counter++;
    }
    return counter;
}

//void cLabirynt::WhereToGo(const cPosition& position, bool& goLeft, bool& goRight, bool goFront)
//{
//
//}

sCell* cLabirynt::GetCell(const cPosition& position, Direction::eAbsolute mouseDirection, Direction::eRelative direction)
{
    auto cellPos = GetCellPosition(position, mouseDirection, direction);
    if (cellPos < cPosition(0, 0) || cPosition(mWidth - 1, mHeight - 1) < cellPos) {
        return nullptr;
    }
    return &myCells[cellPos.X()][cellPos.Y()];
}

cPosition cLabirynt::GetCellPosition(const cPosition& position, Direction::eAbsolute mouseDirection, Direction::eRelative direction)
{
    auto rotation = Direction::Rotate(mouseDirection, direction);
    return position.Neighbour(rotation);
}

std::vector<sCell> cLabirynt::GetNeighboursNearestCenter(const cPosition& pos, Direction::eAbsolute dir, bool takeVisited)
{
    std::vector<sCell> cells;
    auto getNeighbourCellIfNotVisited = [&, pos, dir](Direction::eRelative mouseDir) {
        auto cell = GetCell(pos, dir, mouseDir);
        if (cell != nullptr) {
            bool condition;
            if (takeVisited) {
                condition = (cell->visited > 0);
            } else {
                condition = (cell->visited == 0);
            }

            if (condition && AreNeighbours(pos, cell->pos)) {
                cells.push_back(*cell);
            }
        }
    };

    getNeighbourCellIfNotVisited(Direction::eRelative::Right);
    getNeighbourCellIfNotVisited(Direction::eRelative::Straight);
    getNeighbourCellIfNotVisited(Direction::eRelative::Left);

    //sortowanie
    struct by_center {
        bool operator()(sCell const& cell1, sCell const& cell2) const
        {
            return (cell1.distFromCenter < cell2.distFromCenter);
        }
    };
    std::sort(cells.begin(), cells.end(), by_center());

    return cells;
}

bool cLabirynt::IsNode(const cPosition& position)
{
    auto x = position.X();
    auto y = position.Y();
    if (myCells[x][y].endOfRoute || myCells[x][y].visited > 1 || position.Initial()) {
        return true;
    }
    return false;
}

void cLabirynt::Add(std::shared_ptr<cRoute> route)
{
    myRoutes.push_back(route);

    if (nodeList.find(route->Start()) != nodeList.end()) {
        cNode newNode(route->Start());
        newNode.Add(route);
        myNodes.push_back(newNode);
    }

    if (nodeList.find(route->End()) != nodeList.end()) {
        cNode newNode(route->End());
        newNode.Add(route);
        myNodes.push_back(newNode);
    }
}
