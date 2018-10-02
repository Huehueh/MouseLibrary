#include "Main.h"

#include <Data/cMouse.h>

extern "C" {
cMouse* CreateInstance() { return new cMouse(); }

void DestroyInstance(cMouse* mouse) { delete mouse; }

int InitLabirynth(cMouse* mouse, int width, int height)
{
    auto status = mouse->CreateLabirynt(width, height);
    return static_cast<int>(status);
}

int ResearchNextStep(cMouse* mouse, bool left, bool right, bool front)
{
    auto result = mouse->ResearchNextStep(left, right, front);
    return result;
}

int GoFrom(cMouse* mouse, int x, int y, bool recalculate) { return 0; }
}
