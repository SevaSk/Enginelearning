#pragma once

#include "Window.h"
#include "Timer.h"
#include "Camera.h"

class App
{
public:
	App();
	//master frame
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	std::vector<std::unique_ptr<class Fractal>> fractals;
	Camera cam{ wnd.mouse };
	static constexpr size_t nDrawables = 180;
};

