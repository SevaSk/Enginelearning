#include "App.h"

App::App():
	wnd(800,600, "SK Engine")
{}

int App::Go()
{
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DoFrame();
	}
	// check if gResult failed
	if (gResult == -1)
	{
		throw WND_LAST_EXCEPT();
	}
	return msg.wParam;
}

void App::DoFrame()
{

}