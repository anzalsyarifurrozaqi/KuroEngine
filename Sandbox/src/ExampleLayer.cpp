#include "ExampleLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() 
	: Layer("Example"), 
	m_CameraController(1280.0f / 720.0f), 
	m_FirstPersonCamera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	m_Camera(m_FirstPersonCamera)
{
	//m_VertexArray = Kuro::VertexArray::Create();

	//float vertices[3 * 3] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f,
	//};

	//vertexBuffer = Kuro::VertexBuffer::Create(vertices, sizeof(vertices));
	//Kuro::BufferLayout layout =
	//{
	//	{ Kuro::ShaderDataType::Float3, "a_Position" },
	//	{ Kuro::ShaderDataType::Float3, "a_Color" }
	//};
	//vertexBuffer->SetLayout(layout);
	//m_VertexArray->AddVertexBuffer(vertexBuffer);

	//uint32_t indices[3] = { 0,1,2 };
	//Kuro::Ref<Kuro::IndexBuffer> indexBuffer = Kuro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	//m_VertexArray->SetIndexBuffer(indexBuffer);	

	// shader
	//auto vertexSrc = m_ShaderLibrary.Load("assets/shaders/SampleVertexShader.glsl");
	//auto fragmentSrc = m_ShaderLibrary.Load("assets/shaders/SampleFragmentShader.glsl");
	//vertexSrc->Bind();
	//fragmentSrc->Bind();

	//m_FlatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

}

void ExampleLayer::OnUpdate(Kuro::Timestep ts)
{	
	seconds += ts * 1.0f;

	// Update
	m_CameraController.OnUpdate(ts);
	m_FirstPersonCamera.OnUpdate(ts);

	// Renderer
	Kuro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Kuro::RenderCommand::Clear();	

	Kuro::Renderer::BeginScene(m_FirstPersonCamera);
	//Kuro::Renderer::DrawQuad({ 0.0f, 0.5f }, { 0.5f, 0.5f }, m_Color);
	//Kuro::Renderer::DrawRotateQuad({ 0.0f, -0.5f }, { 0.5f, 0.5f }, seconds, m_Color);

	// EROR : Only Draw 1 box, maybe wrong when set indices
	Kuro::Renderer::DrawBox({ 0.0f, 0.0f }, glm::vec3(0.5f), m_Color);
	//Kuro::Renderer::DrawRotateBox({ 0.0f, 0.0f }, glm::vec3(0.5f), seconds, m_Color);

	//Triangle
	//m_FlatColorShader->Bind();
	//m_FlatColorShader->SetFloat3("u_Color", m_Color);
	//Kuro::Renderer::Submit(m_FlatColorShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Kuro::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Kuro::Event& e)
{
	m_CameraController.OnEvent(e);
	m_FirstPersonCamera.OnEvent(e);
}
