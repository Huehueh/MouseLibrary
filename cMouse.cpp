#include "cMouse.h"
#include "cRoute.h"

#include <iostream>

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
    return true;
}

int cMouse::ResearchNextStep(bool leftWall, bool rightWall, bool frontWall)
{
    //uzupelnienie info w labiryncie

    myLabirynth->Set(myPosition, myDirection, leftWall, rightWall, frontWall);

    //stworzenie wlasnej mapy wektorowej
    //ManageRoute();

    //decyzja gdzie iœæ
    auto decision = MakeDecision();
    //std::cout << "Decyzja " << static_cast<int>(decision) << std::endl;

    // nowa pozycja
    SetPosDir(decision);

    return static_cast<int>(decision);
}

void cMouse::SetPosDir(eDecision decision)
{
    // new direction
    switch (myDirection) {
    case eDirection::N: {
        switch (decision) {
        case eDecision::GO_LEFT:
            myDirection = eDirection::W;
            break;

        case eDecision::GO_RIGHT:
            myDirection = eDirection::E;
            break;
        case eDecision::GO_BACK:
            myDirection = eDirection::S;
            break;
        default:
            break;
        }
        break;
    }

    case eDirection::S: {
        switch (decision) {
        case eDecision::GO_LEFT:
            myDirection = eDirection::E;
            break;

        case eDecision::GO_RIGHT:
            myDirection = eDirection::W;
            break;
        case eDecision::GO_BACK:
            myDirection = eDirection::N;
            break;
        default:
            break;
        }
        break;
    }
    case eDirection::E: {
        switch (decision) {
        case eDecision::GO_LEFT:
            myDirection = eDirection::N;
            break;

        case eDecision::GO_RIGHT:
            myDirection = eDirection::S;
            break;
        case eDecision::GO_BACK:
            myDirection = eDirection::W;
            break;
        default:
            break;
        }
        break;
    }
    case eDirection::W: {
        switch (decision) {
        case eDecision::GO_LEFT:
            myDirection = eDirection::S;
            break;

        case eDecision::GO_RIGHT:
            myDirection = eDirection::N;
            break;
        case eDecision::GO_BACK:
            myDirection = eDirection::E;
            break;
        default:
            break;
        }
        break;
    }
    }

    //new position
    myPosition = myPosition.Neighbour(myDirection);
}

eDecision cMouse::MakeDecision()
{
    if (myLabirynth->IsCenter(myPosition)) {
        return eDecision::STAY;
    }

    //if any free places
    if (myLabirynth->Left() == eState::FreeToGo) {
        return eDecision::GO_LEFT;
    }
    if (myLabirynth->Right() == eState::FreeToGo) {
        return eDecision::GO_RIGHT;
    }
    if (myLabirynth->Front() == eState::FreeToGo) {
        return eDecision::GO_STRAIGHT;
    }

    //if any already visited places
    if (myLabirynth->Left() == eState::AlreadyVisited) {
        return eDecision::GO_LEFT;
    }
    if (myLabirynth->Right() == eState::AlreadyVisited) {
        return eDecision::GO_RIGHT;
    }
    if (myLabirynth->Front() == eState::AlreadyVisited) {
        return eDecision::GO_STRAIGHT;
    }

    return eDecision::GO_BACK;
}

void cMouse::ManageRoute()
{
    if (myPosition.Initial()) {
        currentRoute = std::make_shared<cRoute>(myPosition);
    } else {
        currentRoute->Add(myPosition);
    }

    if (myLabirynth->IsNode(myPosition)) {
        map.Add(currentRoute);
        currentRoute = std::make_shared<cRoute>(myPosition);
    }
}

int cMouse::GoFrom(cMouse* /*mouse*/, int /* x*/, int /*y*/, bool /*recalculate*/)
{
    return 0;
}
