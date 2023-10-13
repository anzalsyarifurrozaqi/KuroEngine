#include "ExampleLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() 
	: Layer("Example"), 
	m_CameraController(1280.0f / 720.0f),
	m_EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f)
{
}

void ExampleLayer::OnUpdate(Kuro::Timestep ts)
{	
	seconds += ts * 1.0f;

	// Update
	m_CameraController.OnUpdate(ts);
	m_EditorCamera.OnUpdate(ts);

	// Renderer
	Kuro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Kuro::RenderCommand::Clear();	

	Kuro::Renderer::BeginScene(m_EditorCamera);

	Kuro::Renderer::DrawBox({ 0.0f, 0.0f }, glm::vec3(0.5f), m_Color);	

	Kuro::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Kuro::Event& e)
{
	m_CameraController.OnEvent(e);
	m_EditorCamera.OnEvent(e);
}
