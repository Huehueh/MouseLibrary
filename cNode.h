#pragma once

#include "cPosition.h"
#include "cRoute.h"

#include <memory>

class cNode {
public:
    cNode(cPosition position);
    ~cNode();

    void Add(std::shared_ptr<cRoute> route);
    bool operator==(const cNode& node);
    inline cPosition Pos() const { return myPosition; }

private:
    cPosition myPosition;
    std::vector<std::shared_ptr<cRoute>> myRoutes;
};
