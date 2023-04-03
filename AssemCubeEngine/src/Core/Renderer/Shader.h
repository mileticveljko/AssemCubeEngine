#pragma once

#include <string>
#include <glm/glm.hpp>

namespace ac
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformInt1(const std::string& name, int i);
		void UploadUniformInt2(const std::string& name, const glm::vec2& vec);
		void UploadUniformInt3(const std::string& name, const glm::vec3& vec);
		void UploadUniformInt4(const std::string& name, const glm::vec4& vec);

		void UploadUniformInt2(const std::string& name, int v1, int v2);
		void UploadUniformInt3(const std::string& name, int v1, int v2, int v3);
		void UploadUniformInt4(const std::string& name, int v1, int v2, int v3, int v4);

		void UploadUniformUInt1(const std::string& name, unsigned int i);
		void UploadUniformUInt2(const std::string& name, const glm::vec2& vec);
		void UploadUniformUInt3(const std::string& name, const glm::vec3& vec);
		void UploadUniformUInt4(const std::string& name, const glm::vec4& vec);

		void UploadUniformUInt2(const std::string& name, unsigned int v1, unsigned int v2);
		void UploadUniformUInt3(const std::string& name, unsigned int v1, unsigned int v2, unsigned int v3);
		void UploadUniformUInt4(const std::string& name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

		void UploadUniformFloat1(const std::string& name, float f);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

		void UploadUniformFloat2(const std::string& name, float v1, float v2);
		void UploadUniformFloat3(const std::string& name, float v1, float v2, float v3);
		void UploadUniformFloat4(const std::string& name, float v1, float v2, float v3, float v4);

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}
