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
	Kuro::Ref<Kuro::FrameBuffer> opaqueBuffer;
	Kuro::Ref<Kuro::Shader> shaderGridVert;
	Kuro::Ref<Kuro::Shader> shaderGridFrag;
	Kuro::ShaderLibrary m_ShaderLibrary;	

	Kuro::OrthographicCameraController m_CameraController;
	Kuro::EditorCamera m_EditorCamera;
	Kuro::Camera m_Camera;
	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	float seconds = 0.0f;
};
