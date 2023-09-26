#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_VertexArray = Kuro::VertexArray::Create();

	float vertices[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Kuro::Ref<Kuro::VertexBuffer> vertexBuffer = Kuro::VertexBuffer::Create(vertices, sizeof(vertices));
	Kuro::BufferLayout layout =
	{
		{Kuro::ShaderDataType::Float3, "a_Position"},
		{Kuro::ShaderDataType::Float4, "a_Color"}
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);


}

void ExampleLayer::OnUpdate(Kuro::Timestep ts)
{	
}

void ExampleLayer::OnEvent(Kuro::Event& event)
{
}
