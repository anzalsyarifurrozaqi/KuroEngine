#pragma once

#include "Kuro.h"

class ExampleLayer : public Kuro::Layer {
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(Kuro::Timestep ts) override;
	void OnEvent(Kuro::Event& event) override;

private:
	Kuro::Ref<Kuro::VertexArray> m_VertexArray;
};
