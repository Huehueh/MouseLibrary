#pragma once

#include "cNode.h"
#include "cRoute.h"

#include <memory>
#include <set>
#include <vector>

static int MAX_SIZE = 20;
static int MIN_SIZE = 6;

class cPosition;

struct sCell {
    sCell()
        : visited(0)
        , willComeBack(false)
        , endOfRoute(false)
        , walls(0)
        , n(-1)
        , s(-1)
        , w(-1)
        , e(-1)
        , distFromCenter(0.0)
        , pos()
    {
    }
    int visited;
    bool willComeBack;
    bool endOfRoute;
    int walls;
    int n, s, w, e; // czy sa sciany 1 -jest, 0 - nie ma, -1 - nie wiadomo
    double distFromCenter;
    cPosition pos;
};

class cLabirynt {
public:
    cLabirynt(int width, int height);
    ~cLabirynt();

    static bool CheckSize(int size);
    bool IsCenter(const cPosition& position) const;

    void Set(const cPosition& position, Direction::eAbsolute mouseDirection, bool left, bool right, bool front);
    //void WhereToGo(const cPosition& position, bool& goLeft, bool& goRight, bool& goFront);

    void Add(std::shared_ptr<cRoute> route);
    bool IsNode(const cPosition& position);
    bool EndOfRoute(const cPosition& position);
    sCell* GetCell(const cPosition& position, Direction::eAbsolute mouseDirection, Direction::eRelative directionn);
    cPosition GetCellPosition(const cPosition& position, Direction::eAbsolute mouseDirection, Direction::eRelative directionn);

    //Returns cells in order: from these that are the nearest from centre to the furhers from center
    std::vector<sCell> GetNeighboursNearestCenter(const cPosition& myPos, Direction::eAbsolute mouseDirection, bool takeVisited);

private:
    void SetWalls(const cPosition& pos, int n, int s, int w, int e);
    bool AreNeighbours(const cPosition& pos1, const cPosition& pos2);

    // checks how many exits from the cell were not visited earlier
    int CheckExits(const cPosition& pos);

    sCell** myCells;
    int mWidth;
    int mHeight;

    std::set<cPosition> nodeList;
    std::vector<cNode> myNodes;
    std::vector<std::shared_ptr<cRoute>> myRoutes;
};
