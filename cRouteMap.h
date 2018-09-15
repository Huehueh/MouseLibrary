#pragma once

#include "cPosition.h"
#include "cRoute.h"

#include <memory>
#include <set>
#include <vector>

class cRouteMap {
public:
    cRouteMap();
    ~cRouteMap();

    void Add(std::shared_ptr<cRoute> route);

private:
    //std::set<cPosition> myNodes;
    std::vector<std::shared_ptr<cRoute>> myRoutes;
};
