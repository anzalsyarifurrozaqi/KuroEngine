#include "engineph.h"
#include "Renderer.h"

namespace Kuro
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

		// Editor-only
		int EntityID;
	};

	struct BoxVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;

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
		// QUAD ///////////////
		//////////////////////
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;		

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		glm::vec4 QuadVertexPositions[4];

		////////////////////////
		// BOX ////////////////
		//////////////////////
		Ref<VertexArray> BoxVertexArray;
		Ref<VertexBuffer> BoxVertexBuffer;
		Ref<Shader> BoxShader;		

		uint32_t BoxIndexCount = 0;
		BoxVertex* BoxVertexBufferBase = nullptr;
		BoxVertex* BoxVertexBufferPtr = nullptr;

		glm::vec4 BoxVertexPosition[8];

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
		// QUAD ///////////////
		//////////////////////
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position" },
			{ ShaderDataType::Float4,	"a_Color" },
			{ ShaderDataType::Float2,	"a_TexCoord" },
			{ ShaderDataType::Float,	"a_TexIndex" },
			{ ShaderDataType::Float,	"a_TillingFactor" },
			{ ShaderDataType::Int,		"a_EntityID" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i +=6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;			
		}

		for (uint32_t i = 0; i < 54; i += 6)
		{
			KURO_CORE_TRACE(
				"{0}, {1}, {2}, {3}, {4}, {5}", 
				quadIndices[i + 0], 
				quadIndices[i + 1], 
				quadIndices[i + 2], 
				quadIndices[i + 3], 
				quadIndices[i + 4], 
				quadIndices[i + 5]
			);
		} 

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		// Set Quad Vertex Position
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f,	0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f,	0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f,	0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f,	0.0f, 1.0f };

		////////////////////////
		// BOX ////////////////
		//////////////////////
		s_Data.BoxVertexArray = VertexArray::Create();

		s_Data.BoxVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(BoxVertex));
		s_Data.BoxVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"	},
			{ ShaderDataType::Float4,	"a_Color"		},
			{ ShaderDataType::Int,		"a_EntityID"	}
		});
		s_Data.BoxVertexArray->AddVertexBuffer(s_Data.BoxVertexBuffer);

		s_Data.BoxVertexBufferBase = new BoxVertex[s_Data.MaxVertices];

		// TODO : Setup indices untuk box

		uint32_t boxIndices[] =
		{
			0, 1, 2,  0, 2, 3, // bottom
			4, 5, 6,  4, 6, 7, // top
			0, 1, 5,  0, 5, 4, // left
			3, 2, 6,  3, 6, 7, // right
			1, 5, 6,  1, 6, 2, // front        
			0, 4, 7,  0, 7, 3, // back
		};

		Ref<IndexBuffer> boxIB = IndexBuffer::Create(boxIndices, sizeof(boxIndices));
		s_Data.BoxVertexArray->SetIndexBuffer(boxIB);
		//delete[] boxIB; // EROR

		// Set Box Vertex Position
		s_Data.BoxVertexPosition[0] = { -0.5f,  -0.5f,  0.5f, 1.0f };
		s_Data.BoxVertexPosition[1] = {  0.5f,  -0.5f,  0.5f, 1.0f };
		s_Data.BoxVertexPosition[2] = {  0.5f,   0.5f,  0.5f, 1.0f };
		s_Data.BoxVertexPosition[3] = { -0.5f,   0.5f,  0.5f, 1.0f };

		s_Data.BoxVertexPosition[4] = { -0.5f,  -0.5f, -0.5f, 1.0f };
		s_Data.BoxVertexPosition[5] = {  0.5f,  -0.5f, -0.5f, 1.0f };
		s_Data.BoxVertexPosition[6] = {  0.5f,   0.5f, -0.5f, 1.0f };
		s_Data.BoxVertexPosition[7] = { -0.5f,   0.5f, -0.5f, 1.0f };

		// Texture
		s_Data.WhiteTexture = Texture2D::Create(TextureSpecification());
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		// Set first texture slot to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		// Shader
		s_Data.QuadShader = Shader::Create("assets/shaders/Renderer2D_Quad.glsl");
		s_Data.BoxShader = Shader::Create("assets/shaders/Box.glsl");
		//s_Data.QuadShader = Shader::Create("assets/shaders/TestShader.glsl");

		// Camera buffer
		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererData::CameraData), 0);
	}

	void Renderer::Shutdown()
	{
		KURO_CORE_INFO("Renderer::Shutdown");

		delete[] s_Data.QuadVertexBufferBase;

		delete[] s_Data.BoxVertexBufferBase;
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

	void Renderer::EndScene()
	{
		Flush();
	}

	void Renderer::Flush()
	{
		////////////////////////
		// QUAD ///////////////
		//////////////////////
		if (s_Data.QuadIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);			

			// Bind Texture;
			for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
				s_Data.TextureSlots[i]->Bind(i);

			s_Data.QuadShader->Bind();
			RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		}

		////////////////////////
		// BOX ////////////////
		//////////////////////
		if (s_Data.BoxIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.BoxVertexBufferPtr - (uint8_t*)s_Data.BoxVertexBufferBase);
			s_Data.BoxVertexBuffer->SetData(s_Data.BoxVertexBufferBase, dataSize);

			s_Data.BoxShader->Bind();
			RenderCommand::SetPolygonMode(PolygonMode::LINE); // INFO : Temporary to draw wireframe
			RenderCommand::DrawIndexed(s_Data.BoxVertexArray, s_Data.BoxIndexCount);
		}
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{		
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotateQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
	{
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
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
		constexpr size_t boxVertexCount = 8;

		if (s_Data.BoxIndexCount >= RendererData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < boxVertexCount; i++)
		{
			s_Data.BoxVertexBufferPtr->Position = transform * s_Data.BoxVertexPosition[i];
			s_Data.BoxVertexBufferPtr->Color = color;
			s_Data.BoxVertexBufferPtr->EntityID = entiryID;
			s_Data.BoxVertexBufferPtr++;
		}

		s_Data.BoxIndexCount += 36;		
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

	void Renderer::StartBatch()
	{		
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;		

		s_Data.BoxIndexCount = 0;
		s_Data.BoxVertexBufferPtr = s_Data.BoxVertexBufferBase;
	}
	
	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}
}
