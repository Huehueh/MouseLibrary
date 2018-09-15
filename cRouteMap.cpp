#include "cRouteMap.h"

cRouteMap::cRouteMap()
{
}

cRouteMap::~cRouteMap()
{
}

void cRouteMap::Add(std::shared_ptr<cRoute> route)
{
    myRoutes.push_back(route);
    //myNodes.insert(route->Start());
    //myNodes.insert(route->End());
}
