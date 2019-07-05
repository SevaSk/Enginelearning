#include "App.h"
#include <sstream>
#include <iomanip>
#include <memory>
#include "Math.h"
#include "ComputeShaderGraph.h"

App::App():
	wnd(800,600, "SK Engine")
{
	
	drawables.push_back(std::make_unique<ComputeShaderGraph>(wnd.Gfx()));
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}


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

App::~App()
{}

void App::DoFrame()
{
	float dt = timer.Mark();
	float fps = 1 / dt;
	std::ostringstream oss;
	oss << fps;
	wnd.SetTitle(oss.str());
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	cam.Update(dt,
		wnd.kbd,
		wnd.mouse
	);
	wnd.Gfx().SetCamera(cam.GetMatrix());

	for (auto& b : drawables)
	{
		b->Update(wnd.kbd.KeyIsPressed(VK_CONTROL) ? 0.0f : dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}