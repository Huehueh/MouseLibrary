#pragma once
// Main.h

#ifdef MAINDLL_EXPORT
#define MAINDLL_API __declspec(dllexport) 
#else
#define MAINDLL_API __declspec(dllimport) 
#endif

extern "C" {
	MAINDLL_API void CreateInstance();
	MAINDLL_API void DestroyInstance();
	MAINDLL_API int InitLabirynth(int width, int height);
	MAINDLL_API int ResearchNextStep(bool left, bool right, bool front); // badanie labiryntu
	MAINDLL_API int GoFrom(int x, int y, bool recalculate);

}
