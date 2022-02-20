#include "Window.h"
#include "Renderer.h"
int main(int _argc, const char* const* _argv)
{
	Window window;
	window.InitWindow(1920, 1080, "SoftRenderer");
	window.ShowWindow();
	bool isExit = false;


	window.SetOnWindowCloseCallback([&](void)->void
		{
			isExit = true;
		});
	Renderer renderer;
	renderer.Init(&window);
	auto lastTime = GetTickCount64();
	while (!isExit) {
		auto thisTime = GetTickCount64();
		renderer.Tick((thisTime - lastTime) / 1000.0);
		lastTime = thisTime;
		renderer.Render();
		window.MessageProcess();
	}

}