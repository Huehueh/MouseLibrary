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
    int ResearchNextStep(bool left, bool right, bool front);
    int GoFrom(cMouse* mouse, int x, int y, bool recalculate);

private:
    void ManageRoute();

    std::unique_ptr<cLabirynt> myLabirynth;
    cPosition myPosition;
    std::vector<std::shared_ptr<cRoute>> myRoutes;
    std::shared_ptr<cRoute> currentRoute;
    eDirection myDirection;
};
