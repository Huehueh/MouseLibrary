#pragma once

class cRoute;

#include "cLabirynt.h"
#include "cPosition.h"

#include <memory>
#include <vector>

class cMouse {
public:
    cMouse();
    ~cMouse();

    bool CreateLabirynt(int width, int height);
    int ResearchNextStep(bool leftWall, bool rightWall, bool frontWall);
    int GoFrom(cMouse* mouse, int x, int y, bool recalculate);

    inline cPosition Position() { return myPosition; };
    inline Direction::eAbsolute Direction() { return myDirection; };

private:
    void ManageRoute();
    Direction::eRelative MakeDecision(bool leftWall, bool rightWall, bool frontWall);
    void SetPosDir(Direction::eRelative decision);
    Direction::eRelative ResearchForNewWay(bool leftWall, bool rightWall, bool frontWall);
    Direction::eRelative ChooseWisely(std::vector<sCell*>& possibilities);

    std::unique_ptr<cLabirynt> myLabirynth;
    cPosition myPosition;
    std::shared_ptr<cRoute> currentRoute;
    Direction::eAbsolute myDirection;
    bool goingBackMode;
    int goingBackPosition;
};
