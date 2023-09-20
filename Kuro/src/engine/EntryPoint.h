#pragma once

#ifdef KURO_PLATFORM_WINDOWS

extern Kuro::Application* Kuro::CreateApplication();

int main(int argc, char** argv)
{
	Kuro::Log::Init();
	KURO_CORE_INFO("EntryPoint.h TEST Initialize Log!");
	int a = 5;
	KURO_CORE_INFO("EntryPoint.h TEST a : {0}", a);

	auto app = Kuro::CreateApplication();
	app->Run();
	delete app;
}
#endif // KURO_PLATFORM_WINDOWS
