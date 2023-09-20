#include "Kuro.h"

class Sandbox : public Kuro::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Kuro::Application* Kuro::CreateApplication()
{
	return new Sandbox();
}

