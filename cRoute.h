#pragma once

#include "cPosition.h"
#include <vector>

class cRoute {
public:
    cRoute(cPosition pos);
    ~cRoute();
    void Add(cPosition pos);
    cPosition Start();
    cPosition End();

private:
    std::vector<cPosition> myCells;
};
