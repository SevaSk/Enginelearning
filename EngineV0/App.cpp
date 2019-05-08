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
		//process messages return ecode if there is one
		if (const auto ecode = Window::ProcessMessage()) 
		{
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str().c_str());
}