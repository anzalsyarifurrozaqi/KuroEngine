#include "engineph.h"
#include "Renderer.h"
#include "Model.h"

namespace Kuro
{
	struct Instance
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

		// Editor-only
		int EntityID;
	};

	struct RendererData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		/////////////////////////
		// GLOBAL DATA /////////
		///////////////////////
		Ref<Texture2D> WhiteTexture;

		////////////////////////
		// MODEL-DEFAULT CUBE /
		//////////////////////
		std::vector<VertexData> CubeVertices;
		std::vector<unsigned int> CubeIndices;

		uint32_t MaxCubeVertices = 0;
		uint32_t MaxCubeIndices = 0;

		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;
		Ref<Shader> CubeShader;

		uint32_t CubeIndexCount = 0;
		Instance* CubeVertexBufferBase = nullptr;
		Instance* CubeVertexBufferPtr = nullptr;		

		////////////////////////
		// TEXTURE ////////////
		//////////////////////
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		////////////////////////
		// CAMERA /////////////
		//////////////////////
		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	static RendererData s_Data;

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		KURO_CORE_INFO("Renderer::Init");

		RenderCommand::Init();

		////////////////////////
		// MODEL-DEFAULT CUBE /
		//////////////////////
		s_Data.CubeVertexArray = VertexArray::Create();

		// Model
		Model* cubeModel = new Model("assets/objects/Cube_2x2x2m.glb");
		
		std::vector<VertexData> vertices = cubeModel->GetMesh()->GetVertices();
		std::vector<uint32_t> indicies = cubeModel->GetMesh()->GetIndices();
		
		s_Data.CubeVertices = vertices;
		s_Data.CubeIndices = indicies;

		s_Data.MaxCubeVertices = vertices.size();
		s_Data.MaxCubeIndices = indicies.size();

		KURO_CORE_TRACE(s_Data.MaxCubeVertices);
		KURO_CORE_INFO(s_Data.MaxCubeIndices);

		s_Data.CubeVertexBuffer = VertexBuffer::Create(&(vertices[0]), s_Data.MaxCubeVertices * sizeof(VertexData));
		s_Data.CubeVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"		},
			{ ShaderDataType::Float4,	"a_Color"			},
			{ ShaderDataType::Float2,	"a_TexCoord"		},
			{ ShaderDataType::Float,	"a_TexIndex"		},
			{ ShaderDataType::Float,	"a_TilingFactor"	},
			{ ShaderDataType::Int,		"a_EntityID"		}
		});
		s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

		s_Data.CubeVertexBufferBase = new Instance[s_Data.MaxCubeVertices];

		Ref<IndexBuffer> boxIB = IndexBuffer::Create(&(indicies[0]), s_Data.MaxCubeIndices);
		s_Data.CubeVertexArray->SetIndexBuffer(boxIB);
		//delete[] boxIB; // EROR

		// Texture
		//s_Data.WhiteTexture = Texture2D::Create(TextureSpecification());
		//uint32_t whiteTextureData = 0xffffffff;
		//s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		s_Data.WhiteTexture = Texture2D::Create("assets/textures/Checkerboard.png");

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		// Set first texture slot to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		// Shader		
		//s_Data.CubeShader = Shader::Create("assets/shaders/Box.glsl");		
		s_Data.CubeShader = Shader::Create("assets/shaders/Cube.glsl");		

		// Camera buffer
		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererData::CameraData), 0);
	}

	void Renderer::Shutdown()
	{
		KURO_CORE_INFO("Renderer::Shutdown");		

		delete[] s_Data.CubeVertexBufferBase;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{		
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererData::CameraData));
		
		StartBatch();
	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererData::CameraData));

		StartBatch();
	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{		
		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);		
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererData::CameraData));

		StartBatch();
	}

	void Renderer::EndScene()
	{
		Flush();
	}

	void Renderer::Flush()
	{
		////////////////////////
		// MODEL //////////////
		//////////////////////
		if (s_Data.CubeIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.CubeVertexBufferPtr - (uint8_t*)s_Data.CubeVertexBufferBase);
			s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, dataSize);

			// Bind Texture			
			for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
				s_Data.TextureSlots[i]->Bind(i);

			s_Data.CubeShader->Bind();
			//RenderCommand::SetPolygonMode(PolygonMode::LINE); // INFO : Temporary to draw wireframe
			RenderCommand::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount);
		}
	}

	void Renderer::DrawBox(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color)
	{		
		DrawBox({ position.x, position.y, 0.0f }, size, color);		
	}

	void Renderer::DrawBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z });
		
		DrawBox(transform, color);
	}

	void Renderer::DrawRotateBox(const glm::vec2& position, const glm::vec3& size, float rotation, const glm::vec4& color)
	{
		DrawRotateBox({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer::DrawRotateBox(const glm::vec3& position, const glm::vec3& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 1.0f, 1.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z });

		DrawBox(transform, color);
	}

	void Renderer::DrawBox(const glm::mat4& transform, const glm::vec4& color, int entiryID)
	{		
		size_t boxVertexCount = s_Data.MaxCubeVertices;		
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.CubeIndexCount >= s_Data.MaxCubeIndices)
			NextBatch();

		for (size_t i = 0; i < boxVertexCount; i++)
		{
			const glm::vec4 Position = { s_Data.CubeVertices[i].Position, 1.0f };
			const glm::vec2 TexCoord = s_Data.CubeVertices[i].TexCoords;
			
			s_Data.CubeVertexBufferPtr->Position = transform * Position;
			s_Data.CubeVertexBufferPtr->Color = color;
			s_Data.CubeVertexBufferPtr->TexCoord = TexCoord;
			s_Data.CubeVertexBufferPtr->TexIndex = textureIndex;
			s_Data.CubeVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.CubeVertexBufferPtr->EntityID = entiryID;
			s_Data.CubeVertexBufferPtr++;
		}

		s_Data.CubeIndexCount += s_Data.MaxCubeIndices;
	}

	void Renderer::StartBatch()
	{		
		s_Data.CubeIndexCount = 0;
		s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
	}
	
	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}
}
