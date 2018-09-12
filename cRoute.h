#pragma once

#include "cPosition.h"
#include <vector>

class cRoute {
public:
    cRoute(cPosition pos);
    ~cRoute();
    void Add(cPosition pos);

private:
    std::vector<cPosition> myCells;
};
