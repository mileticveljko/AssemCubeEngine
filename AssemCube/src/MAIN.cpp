#include "AssemCube.h"

#include "Core/Platform/OpenGL/OpenGLShader.h"

#include "imguiV/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public ac::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f)	{
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

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		ac::Ref<ac::VertexBuffer> squareVB;
		squareVB.reset(ac::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ac::ShaderDataType::Float3, "a_Position" }
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

		m_Shader.reset(ac::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform *vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color , 1.0f);
			}
		)";

		m_flatColorShader.reset(ac::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

	}

	void OnUpdate(ac::Timestep ts) override
	{
		if (ac::Input::IsKeyPressed(AC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (ac::Input::IsKeyPressed(AC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		
		if (ac::Input::IsKeyPressed(AC_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		ac::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ac::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ac::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ac::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<ac::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color",m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ac::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
			}
		}

		ac::Renderer::Submit(m_Shader, m_VertexArray);

		ac::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(ac::Event& event) override
	{
	}

private:
	ac::Ref<ac::Shader> m_Shader;
	ac::Ref<ac::VertexArray> m_VertexArray;

	ac::Ref<ac::Shader> m_flatColorShader;
	ac::Ref<ac::VertexArray> m_SquareVA;

	ac::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 100.0f;

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