#include "App.h"
#include <sstream>
#include <iomanip>

App::App():
	wnd(800,600, "SK Engine")
{}

int App::Go()
{
	while (true)
	{
		//process messages return ecode if there is one (exite code))
		if (const auto ecode = Window::ProcessMessage()) 
		{
			return *ecode;
		}
		DoFrame();
	}
}

std::vector<float> campos{ 0.0f, 0.0f,0.0f};

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;


	if (wnd.kbd.KeyIsPressed('W'))
	{

		campos[1] -= 0.1f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		campos[1] += 0.1f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		campos[0] += 0.1f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		campos[0] -= 0.1f;
	}
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle(campos);
	wnd.Gfx().EndFrame();
}
	