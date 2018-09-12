#include "cMouse.h"
#include "cRoute.h"

//Directions
// N - north
//

cMouse::cMouse()
    : myLabirynth(nullptr)
    , myDirection(eDirection::N)
{
}

cMouse::~cMouse() {}

bool cMouse::CreateLabirynt(int width, int height)
{
    if (cLabirynt::CheckSize(width) == false || cLabirynt::CheckSize(height) == false) {

        return false;
    }
    myLabirynth = std::make_unique<cLabirynt>(width, height);
    currentRoute = std::make_shared<cRoute>(myPosition);
}

int cMouse::ResearchNextStep(bool left, bool right, bool front)
{
    //uzupelnienie info w labiryncie
    if (myLabirynth) {
        myLabirynth->Set(myPosition, myDirection, left, right, front);
    }
    ManageRoute();

    //decyzja gdzie iœæ

    if (myLabirynth->IsCenter(myPosition)) {
        return 0;
    } else if (front) {
        return 0;
    } else if (left) {
        return 2;
    } else if (right) {
        return 3;
    } else {
        return 4;
    }
}

void cMouse::ManageRoute()
{
    if (myPosition.Initial()) {
        currentRoute = std::make_shared<cRoute>(myPosition);
    } else {
        currentRoute->Add(myPosition);
    }

    if (myLabirynth->IsNode(myPosition)) {
        myRoutes.push_back(currentRoute);
        currentRoute = std::make_shared<cRoute>(myPosition);
    }
}

int cMouse::GoFrom(cMouse* mouse, int x, int y, bool recalculate)
{
}
