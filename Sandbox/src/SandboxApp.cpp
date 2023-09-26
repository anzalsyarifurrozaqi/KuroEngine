#include "Kuro.h"
//-----------Entry Point--------------
#include "Kuro/Core/EntryPoint.h"
//------------------------------------

#include "ExampleLayer.h"

class Sandbox : public Kuro::Application
{
public:
	Sandbox() {		
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Kuro::Application* Kuro::CreateApplication()
{
	return new Sandbox();
}
