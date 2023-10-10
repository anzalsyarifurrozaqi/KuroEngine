#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "FirstPersonCamera.h"
#include "UniformBuffer.h"
#include "Texture.h"

namespace Kuro
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const FirstPersonCamera& camera);
		static void EndScene();
		static void Flush();
		
		// primitive
		
		////////////////////////////////////
		// QUAD ///////////////////////////
		//////////////////////////////////
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		////////////////////////////////////
		// QUAD ///////////////////////////
		//////////////////////////////////

		//////////////////////////////////
		// BOX //////////////////////////
		////////////////////////////////
		static void DrawBox(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color);
		static void DrawBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);

		static void DrawRotateBox(const glm::vec2& position, const glm::vec3& size, float rotation, const glm::vec4& color);
		static void DrawRotateBox(const glm::vec3& position, const glm::vec3& size, float rotation, const glm::vec4& color);

		static void DrawBox(const glm::mat4& transform, const glm::vec4& color, int entiryID = -1);

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		
		static Scope<SceneData> s_SceneData;

		static void StartBatch();
		static void NextBatch();
	};
}

// TODO : buat draw box lebih efektif
