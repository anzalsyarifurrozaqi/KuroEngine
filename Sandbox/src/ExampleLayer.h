#pragma once

#include "Kuro.h"

class ExampleLayer : public Kuro::Layer {
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(Kuro::Timestep ts) override;
	void OnEvent(Kuro::Event& e) override;

private:
	Kuro::Ref<Kuro::VertexArray> m_VertexArray;
	Kuro::Ref<Kuro::VertexArray> m_SquareVA;
	Kuro::Ref<Kuro::VertexBuffer> vertexBuffer;
	Kuro::Ref<Kuro::Shader> m_Shader;
	Kuro::Ref<Kuro::Shader> m_FlatColorShader;
	Kuro::ShaderLibrary m_ShaderLibrary;	

	Kuro::OrthographicCameraController m_CameraController;
	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
};
