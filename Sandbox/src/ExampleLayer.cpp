#include "ExampleLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() 
	: Layer("Example"), 
	m_CameraController(1280.0f / 720.0f),
	m_EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f)
{
	Kuro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	opaqueBuffer = Kuro::FrameBuffer::Create(Kuro::ImageFormat::RGBA16F, Kuro::ImageFormat::DEPTH_COMPONENT24);

	//shaderGridVert = Kuro::Shader::Create("assets/shaders/grid.vert");
	//shaderGridFrag = Kuro::Shader::Create("assets/shaders/grid.frag");
}

void ExampleLayer::OnUpdate(Kuro::Timestep ts)
{	
	seconds += ts * 1.0f;

	// Update
	m_CameraController.OnUpdate(ts);
	m_EditorCamera.OnUpdate(ts);

	// Renderer Scene
	Kuro::RenderCommand::Clear();

	//opaqueBuffer->Bind();
	//opaqueBuffer->SetData();
	Kuro::Renderer::BeginScene(m_EditorCamera);
	Kuro::Renderer::DrawCube({ 1.15f, 0.0f, 1.0f }, glm::vec3(0.5f), m_Color);
	Kuro::Renderer::DrawCube({ -1.0f, 0.0f }, glm::vec3(0.5f), m_Color);
	Kuro::Renderer::DrawCube({ 0.25f, 0.0f, -1.0f }, glm::vec3(0.5f), m_Color);
	Kuro::Renderer::DrawRotatePlane({ 0.0f, -0.6f }, glm::vec3(1.0f), 90.0f, m_Color);
	Kuro::Renderer::EndScene();

	//shaderGridVert->Bind();
	//shaderGridFrag->Bind();
	//opaqueBuffer->UnBind();
	//opaqueBuffer->BindTexture();
}

void ExampleLayer::OnEvent(Kuro::Event& e)
{
	m_CameraController.OnEvent(e);
	m_EditorCamera.OnEvent(e);
}
