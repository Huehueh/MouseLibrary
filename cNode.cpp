#include "cNode.h"

cNode::cNode(cPosition position)
    : myPosition(position)
{
}

cNode::~cNode()
{
}

void cNode::Add(std::shared_ptr<cRoute> route)
{
    if (route->Start() == myPosition) {
        myRoutes.push_back(route);
    } else if (route->End() == myPosition) {
        myRoutes.push_back(route->Reversed());
    }
}

bool cNode::operator==(const cNode& node)
{
    if (this->Pos() == node.Pos()) {
        return true;
    }
    return false;
}
