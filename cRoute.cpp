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
