#include "AssemCube.h"

#include "Core/Platform/OpenGL/OpenGLShader.h"

#include "imguiV/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public ac::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
		{
		
		m_VertexArray.reset(ac::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		ac::Ref<ac::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ac::VertexBuffer::Create(vertices, sizeof(vertices)));
		ac::BufferLayout layout = {
			{ ac::ShaderDataType::Float3, "a_Position" },
			{ ac::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		ac::Ref<ac::IndexBuffer> indexBuffer;
		indexBuffer.reset(ac::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(ac::VertexArray::Create());

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		ac::Ref<ac::VertexBuffer> squareVB;
		squareVB.reset(ac::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ac::ShaderDataType::Float3, "a_Position" },
			{ ac::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ac::Ref<ac::IndexBuffer> squareIB;
		squareIB.reset(ac::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Pos;
			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos,1.0f);
				v_Pos = a_Pos;			
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 Color;

			in vec3 v_Pos;
			in vec4 v_Color;

			void main()
			{
				Color = vec4(v_Pos * 0.5 + 0.5 ,1.0f);
				Color = v_Color;
			}
		)";

		m_Shader = ac::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);


		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = ac::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = ac::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = ac::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<ac::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ac::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

		std::dynamic_pointer_cast<ac::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ac::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
	}

	void OnUpdate(ac::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		ac::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		ac::RenderCommand::Clear();

		ac::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ac::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ac::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ac::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		ac::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		ac::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// ac::Renderer::Submit(m_Shader, m_VertexArray);

		ac::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(ac::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	ac::ShaderLibrary m_ShaderLibrary;
	ac::Ref<ac::Shader> m_Shader;
	ac::Ref<ac::VertexArray> m_VertexArray;

	ac::Ref<ac::Shader> m_FlatColorShader;
	ac::Ref<ac::VertexArray> m_SquareVA;

	ac::Ref<ac::Texture2D> m_Texture, m_ChernoLogoTexture;

	ac::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.7f };
};

class App : public ac::Application
{
public:
	App()
	{
		PushLayer(new ExampleLayer());
	}
	~App() {}
};

ac::Application* ac::CreateApplication()
{
	return new App();
}