#pragma once

class cRoute;

#include "cLabirynt.h"
#include "cPosition.h"
#include "cRouteMap.h"

#include <memory>
#include <vector>

enum class eDecision {
    STAY = 0,
    GO_STRAIGHT = 1,
    GO_LEFT = 2,
    GO_RIGHT = 3,
    GO_BACK = 4
};

class cMouse {
public:
    cMouse();
    ~cMouse();

    bool CreateLabirynt(int width, int height);
    int ResearchNextStep(bool leftWall, bool rightWall, bool frontWall);
    int GoFrom(cMouse* mouse, int x, int y, bool recalculate);

    inline cPosition Position() { return myPosition; };
    inline eDirection Direction() { return myDirection; };

private:
    void ManageRoute();
    eDecision MakeDecision();
    void SetPosDir(eDecision decision);

    cRouteMap map;
    std::unique_ptr<cLabirynt> myLabirynth;
    cPosition myPosition;
    std::shared_ptr<cRoute> currentRoute;
    eDirection myDirection;
};
