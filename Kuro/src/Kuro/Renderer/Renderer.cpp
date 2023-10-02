#include "engineph.h"
#include "Renderer.h"

namespace Kuro
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		KURO_CORE_INFO("Renderer::Init");
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
		KURO_CORE_INFO("Renderer::Shutdown");
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		//KURO_CORE_INFO("Renderer::Submit");
		//KURO_CORE_INFO("Renderer::Submit transform : {0}", transform);
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
