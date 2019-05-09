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

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}