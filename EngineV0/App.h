#pragma once
#include "Window.h"
#include "Timer.h"
class App
{
public:
	App();
	//master frame
	int Go();

private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
};

