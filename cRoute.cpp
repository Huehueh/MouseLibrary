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
