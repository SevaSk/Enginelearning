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
	bool spin = wnd.kbd.KeyIsPressed(0x5A);
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle(-timer.Peek(), 0, 0);
	wnd.Gfx().DrawTestTriangle(timer.Peek(),wnd.mouse.GetPosX()/400.0f - 1.0f,-wnd.mouse.GetPosY()/300.0f + 1.0f);
	wnd.Gfx().EndFrame();
}
	