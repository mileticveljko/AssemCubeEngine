#include "AssemCube.h"

#include "Core/Platform/OpenGL/OpenGLShader.h"

#include "imguiV/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public ac::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		ac::RenderCommand::SetClearColor({ 0.35f, 0.35f, 0.4f, 1.0f });

		m_SmileyVA.reset(ac::VertexArray::Create());
		m_FloorVA.reset(ac::VertexArray::Create());

		float smileyVertices[] = {
			-0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
			 0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
			 0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
			-0.1f,  0.1f, 0.0f, 0.0f, 1.0f
		};

		ac::Ref<ac::VertexBuffer> smileyVB;
		smileyVB.reset(ac::VertexBuffer::Create(smileyVertices, sizeof(smileyVertices)));
		smileyVB->SetLayout({
			{ ac::ShaderDataType::Float3, "a_Position" },
			{ ac::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SmileyVA->AddVertexBuffer(smileyVB);

		float floorVertices[] = {
			-500.0f, -1.0f,	  0.0f, 0.0f, 0.0f,
			 500.0f, -1.0f,   0.0f, 2000.0f, 0.0f,
			 500.0f, -0.1f, 0.0f, 2000.0f, 1.0f,
			-500.0f, -0.1f, 0.0f, 0.0f, 1.0f
		};

		ac::Ref<ac::VertexBuffer> floorVB;
		floorVB.reset(ac::VertexBuffer::Create(floorVertices, sizeof(floorVertices)));
		floorVB->SetLayout({
			{ ac::ShaderDataType::Float3, "a_Position" },
			{ ac::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_FloorVA->AddVertexBuffer(floorVB);

		uint32_t Indices[6] = { 0, 1, 2, 2, 3, 0 };
		ac::Ref<ac::IndexBuffer> IB;
		IB.reset(ac::IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
		m_SmileyVA->SetIndexBuffer(IB);

		m_FloorVA->SetIndexBuffer(IB);
		
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_TextureSmiley = ac::Texture2D::Create("assets/textures/smiley.png");
		m_TextureFloor = ac::Texture2D::Create("assets/textures/stone.jpg");

		std::dynamic_pointer_cast<ac::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ac::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(ac::Timestep ts) override
	{
		if (ac::Input::IsKeyPressed(AC_KEY_UP) || m_JumpFlag == true)
		{
			m_JumpFlag = true;
			m_SmileyTranslation.y -= m_JumpSpeed * ts;
			if (m_SmileyTranslation.y < -0.4f)
				m_JumpFlag = false;
		}
		else if (m_SmileyTranslation.y < -0.01f)
				m_SmileyTranslation.y += m_JumpSpeed * ts;
		

		ac::RenderCommand::Clear();

		ac::Renderer::BeginScene(m_Camera);

		m_SmileyRotationAngle += m_SmileyRotationSpeed * ts;
		glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::degrees(m_SmileyRotationAngle), { 0,0,-1 });
		
		m_SmileyTranslation.x -= m_SmileyTranslationSpeed * ts;

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_TextureSmiley->Bind();
		ac::Renderer::Submit(textureShader, m_SmileyVA, transform);

		m_TextureFloor->Bind();
		ac::Renderer::Submit(textureShader, m_FloorVA, glm::translate(glm::mat4(1.0f), m_SmileyTranslation));

		ac::Renderer::EndScene();
		
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Settings");
		//ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		//ImGui::End();
	}

	void OnEvent(ac::Event& event) override
	{
	}

private:
	ac::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	ac::Ref<ac::VertexArray> m_SmileyVA, m_FloorVA;

	ac::ShaderLibrary m_ShaderLibrary;

	ac::Ref<ac::Texture2D> m_TextureSmiley, m_TextureFloor;

	float m_SmileyRotationAngle = 0.0f;
	float m_SmileyRotationSpeed = 0.1f;

	glm::vec3 m_SmileyTranslation = {0,0,0};
	float m_SmileyTranslationSpeed = 0.3f;

	float m_JumpSpeed = 1.0f;

	bool m_JumpFlag = false;
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