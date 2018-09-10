#include "Main.h"

#include "cMouse.h"


extern "C" {
	cMouse* CreateInstance()
	{
		return new cMouse();
	}

	void DestroyInstance(cMouse* mouse)
	{
		delete mouse;
	}

	 int InitLabirynth(cMouse* mouse, int width, int height)
	{
		 return 0;
	}

	int ResearchNextStep(cMouse* mouse, bool left, bool right, bool front)
	{
		return 0;
	}

	int GoFrom(cMouse* mouse, int x, int y, bool recalculate)
	{
		return 0;
	}
}
