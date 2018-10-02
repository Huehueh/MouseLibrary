#pragma once

#include "cPosition.h"
#include <memory>
#include <vector>

class cRoute {
public:
    cRoute(cPosition pos);
    ~cRoute();
    void Add(cPosition pos);
    cPosition Start();
    cPosition End();
    cPosition FromStart(int number) const;
    cPosition FromEnd(int number) const;
    inline int Size() const { return static_cast<int>(myCells.size()); }
    std::shared_ptr<cRoute> Reversed();

private:
    std::vector<cPosition> myCells;
};
