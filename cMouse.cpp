#include "cMouse.h"
#include "Directions.h"
#include "cRoute.h"

#include <algorithm>
#include <iostream>

cMouse::cMouse()
    : myDirection(Direction::eAbsolute::North)
    , goingBackMode(false)
    , goingBackPosition(0)
{
}

cMouse::~cMouse() {}

bool cMouse::CreateLabirynt(int width, int height)
{
    myLabirynth = std::make_unique<cLabirynt>(width, height);
    currentRoute = std::make_shared<cRoute>(myPosition);
    return true;
}

int cMouse::ResearchNextStep(bool leftWall, bool rightWall, bool frontWall)
{
    //uzupelnienie info w labiryncie
    myLabirynth->Set(myPosition, myDirection, leftWall, rightWall, frontWall);

    //zarzadzanie marszrutami
    ManageRoute();

    //decyzja gdzie iœæ
    auto decision = MakeDecision(leftWall, rightWall, frontWall);

    //ustawienie nowej pozycji
    SetPosDir(decision);

    switch (decision) {
    case Direction::eRelative::Left:
        return 2;
    case Direction::eRelative::Right:
        return 3;
    case Direction::eRelative::Straight:
        return 1;
    case Direction::eRelative::Back:
        return 4;
    }
    return 0;
}

void cMouse::SetPosDir(Direction::eRelative decision)
{
    myDirection = Direction::Rotate(myDirection, decision);
    myPosition = myPosition.Neighbour(myDirection);
}

Direction::eRelative cMouse::MakeDecision(bool leftWall, bool rightWall, bool frontWall)
{
    if (myLabirynth->EndOfRoute(myPosition)) {
        std::cout << "end of route";
        goingBackMode = true;
        goingBackPosition = 0;
    }

    if (goingBackMode) {
        goingBackPosition++;
        if (goingBackPosition < currentRoute->Size()) {
            auto newDirection = myPosition.DirectionOf(currentRoute->FromEnd(goingBackPosition));
            return Direction::GetDirection(myDirection, newDirection);
        } else {
            goingBackMode = false; //koniec wracania, trzeba jednakpodj¹æ decyzje
        }
    }

    // if not coming back
    return ResearchForNewWay(leftWall, rightWall, frontWall);
}

Direction::eRelative cMouse::ResearchForNewWay(bool leftWall, bool rightWall, bool frontWall)
{
    std::vector<sCell*> visited;
    std::vector<sCell*> notVisited;

    auto setVisitedCells = [&](bool wall, Direction::eRelative direction) {
        sCell* cell = nullptr;
        if (wall == false) {
            cell = myLabirynth->GetCell(myPosition, myDirection, direction);
            if (cell) {
                if (cell->visited > 0) {
                    visited.push_back(cell);
                } else {
                    notVisited.push_back(cell);
                }
            }
        }
        return cell;
    };
    auto left = setVisitedCells(leftWall, Direction::eRelative::Left);
    auto right = setVisitedCells(rightWall, Direction::eRelative::Right);
    auto front = setVisitedCells(frontWall, Direction::eRelative::Straight);

    if (notVisited.size() == 1) {
        if (left && left->visited == 0)
            return Direction::eRelative::Left;
        if (right && right->visited == 0)
            return Direction::eRelative::Right;
        if (front && front->visited == 0)
            return Direction::eRelative::Straight;
    }

    if (notVisited.size() == 0) {
        return ChooseWisely(visited);
    }
    // not visited >=2
    return ChooseWisely(notVisited);
}

Direction::eRelative cMouse::ChooseWisely(std::vector<sCell*>& possibilities)
{
    std::sort(possibilities.begin(), possibilities.end(), [](sCell* c1, sCell* c2) { return (c1->distFromCenter < c2->distFromCenter); });

    for (auto n : possibilities) {
        if (n->endOfRoute == false) {
            auto result = myPosition.DirectionOf(n->pos);
            auto dir = Direction::GetDirection(myDirection, result);
            return dir;
        }
    }
    return Direction::eRelative::Back;
}

void cMouse::ManageRoute()
{
    if (myPosition.Initial()) {
        currentRoute = std::make_shared<cRoute>(myPosition);
    } else {
        currentRoute->Add(myPosition);
    }

    if (myLabirynth->IsNode(myPosition)) {
        myLabirynth->Add(currentRoute);
        if (myLabirynth->EndOfRoute(myPosition) == false || goingBackMode == false) {
            currentRoute = std::make_shared<cRoute>(myPosition);
        }
    }
}

int cMouse::GoFrom(cMouse* /*mouse*/, int /* x*/, int /*y*/, bool /*recalculate*/)
{
    return 0;
}
