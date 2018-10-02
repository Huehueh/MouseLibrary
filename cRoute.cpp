#include "cRoute.h"

cRoute::cRoute(cPosition pos)
{
    Add(pos);
}

cRoute::~cRoute() {}

void cRoute::Add(cPosition pos)
{
    myCells.push_back(pos);
}

cPosition cRoute::Start()
{
    return myCells.at(0);
}

cPosition cRoute::End()
{
    return myCells.back();
}

std::shared_ptr<cRoute> cRoute::Reversed()
{
    std::shared_ptr<cRoute> reversedRoute;
    for (auto it = myCells.rbegin(); it != myCells.rend(); ++it) {
        reversedRoute->Add(*it);
    }
    return reversedRoute;
}

cPosition cRoute::FromStart(int number) const
{
    if (number > 0 && number < myCells.size()) {
        return myCells.at(number);
    } else {
        return cPosition();
    }
}

cPosition cRoute::FromEnd(int number) const
{
    if (number > 0 && number < myCells.size()) {
        return myCells.at(myCells.size() - number - 1);
    } else {
        return cPosition();
    }
}
