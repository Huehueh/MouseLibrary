#pragma once
// Main.h

class cMouse;

#ifdef MAINDLL_EXPORT
#define MAINDLL_API __declspec(dllexport) 
#else
#define MAINDLL_API __declspec(dllimport) 
#endif

extern "C" {
	MAINDLL_API cMouse* CreateInstance();
	MAINDLL_API void DestroyInstance(cMouse* mouse);
	MAINDLL_API int InitLabirynth(cMouse* mouse, int width, int height);
	MAINDLL_API int ResearchNextStep(cMouse* mouse, bool left, bool right, bool front); // badanie labiryntu
	MAINDLL_API int GoFrom(cMouse* mouse, int x, int y, bool recalculate);
}



