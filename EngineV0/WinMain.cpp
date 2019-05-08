#include "App.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpcmdLine,
	int       nCmdShow
)
{
	try
	{
		return App{}.Go();
	}
}