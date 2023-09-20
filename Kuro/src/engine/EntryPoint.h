#pragma once

#ifdef KURO_PLATFORM_WINDOWS

extern Kuro::Application* Kuro::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Kuro::CreateApplication();
	app->Run();
	delete app;
}
#endif // KURO_PLATFORM_WINDOWS
