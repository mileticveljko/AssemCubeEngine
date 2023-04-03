#include "AssemCube.h"

#include "imguiV/imgui.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class ExampleLayer : public ac::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_Angle(0.0f)
	{
		m_VertexArray.reset(ac::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<ac::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ac::VertexBuffer::Create(vertices, sizeof(vertices)));
		ac::BufferLayout layout = {
			{ ac::ShaderDataType::Float3, "a_Position" },
			{ ac::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ac::IndexBuffer> indexBuffer;
		indexBuffer.reset(ac::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(ac::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ac::VertexBuffer> squareVB;
		squareVB.reset(ac::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ac::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ac::IndexBuffer> squareIB;
		squareIB.reset(ac::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Pos;
			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Pos,1.0f);
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

		m_Shader.reset(new ac::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new ac::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	void OnUpdate(ac::Timestep ts) override
	{
		if (ac::Input::IsKeyPressed(AC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraPositionSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraPositionSpeed * ts;
		if (ac::Input::IsKeyPressed(AC_KEY_UP))
			m_CameraPosition.y += m_CameraPositionSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraPositionSpeed * ts;
		
		if (ac::Input::IsKeyPressed(AC_KEY_Q))
			m_Angle += m_CameraRotationSpeed * ts;
		else if (ac::Input::IsKeyPressed(AC_KEY_E))
			m_Angle -= m_CameraRotationSpeed * ts;

		ac::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ac::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_Angle);

		ac::Renderer::BeginScene(m_Camera);

		ac::Renderer::Submit(m_BlueShader, m_SquareVA);
		ac::Renderer::Submit(m_Shader, m_VertexArray);

		ac::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(ac::Event& event) override
	{
	}

private:
	std::shared_ptr<ac::Shader> m_Shader;
	std::shared_ptr<ac::VertexArray> m_VertexArray;

	std::shared_ptr<ac::Shader> m_BlueShader;
	std::shared_ptr<ac::VertexArray> m_SquareVA;

	ac::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_Angle;

	float m_CameraPositionSpeed = 5.0f;
	float m_CameraRotationSpeed = 30.0f;
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