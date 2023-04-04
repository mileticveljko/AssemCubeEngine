#pragma once

#include "Core/Renderer/Shader.h"

#include "glm/glm.hpp"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace ac
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader::OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int i);
		void UploadUniformInt2(const std::string& name, const glm::vec2& vec);
		void UploadUniformInt3(const std::string& name, const glm::vec3& vec);
		void UploadUniformInt4(const std::string& name, const glm::vec4& vec);

		void UploadUniformInt2(const std::string& name, int v1, int v2);
		void UploadUniformInt3(const std::string& name, int v1, int v2, int v3);
		void UploadUniformInt4(const std::string& name, int v1, int v2, int v3, int v4);

		void UploadUniformUInt(const std::string& name, unsigned int i);
		void UploadUniformUInt2(const std::string& name, const glm::vec2& vec);
		void UploadUniformUInt3(const std::string& name, const glm::vec3& vec);
		void UploadUniformUInt4(const std::string& name, const glm::vec4& vec);

		void UploadUniformUInt2(const std::string& name, unsigned int v1, unsigned int v2);
		void UploadUniformUInt3(const std::string& name, unsigned int v1, unsigned int v2, unsigned int v3);
		void UploadUniformUInt4(const std::string& name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

		void UploadUniformFloat(const std::string& name, float f);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

		void UploadUniformFloat2(const std::string& name, float v1, float v2);
		void UploadUniformFloat3(const std::string& name, float v1, float v2, float v3);
		void UploadUniformFloat4(const std::string& name, float v1, float v2, float v3, float v4);

		void UploadUniformMat2(const std::string& name, const glm::mat2& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat2x3(const std::string& name, const glm::mat2x3& matrix);
		void UploadUniformMat3x2(const std::string& name, const glm::mat3x2& matrix);
		void UploadUniformMat2x4(const std::string& name, const glm::mat2x4& matrix);
		void UploadUniformMat4x2(const std::string& name, const glm::mat4x2& matrix);
		void UploadUniformMat3x4(const std::string& name, const glm::mat3x4& matrix);
		void UploadUniformMat4x3(const std::string& name, const glm::mat4x3& matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
