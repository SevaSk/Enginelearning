	#pragma once
#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include "ComputeShader.h"

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
	std::unique_ptr<class ComputeShader> testCompute;
	std::vector<std::unique_ptr<class Fractal>> fractals;
	Camera cam;
	static constexpr size_t nDrawables = 180;
};

