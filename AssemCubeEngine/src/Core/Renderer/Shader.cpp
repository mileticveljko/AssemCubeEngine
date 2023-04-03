#include "acpch.h"
#include "Shader.h"

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace ac
{

	Shader::Shader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		// Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar *source = (const GLchar *)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			AC_CORE_ERROR("{0}", infoLog.data());
			AC_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}


		// Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const GLchar *)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			AC_CORE_ERROR("{0}", infoLog.data());
			AC_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;
		}

		// Program

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			AC_CORE_ERROR("{0}", infoLog.data());
			AC_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}



	void Shader::UploadUniformInt1(const std::string & name, int i)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1ui(location, i);
	}

	void Shader::UploadUniformInt2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, (int)vec.x, (int)vec.y);
	}

	void Shader::UploadUniformInt3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, (int)vec.x, (int)vec.y, (int)vec.z);
	}

	void Shader::UploadUniformInt4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, (int)vec.x, (int)vec.y, (int)vec.z, (int)vec.w);
	}

	void Shader::UploadUniformInt2(const std::string & name, int v1, int v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, v1, v2);
	}

	void Shader::UploadUniformInt3(const std::string & name, int v1, int v2, int v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, v1, v2, v3);
	}

	void Shader::UploadUniformInt4(const std::string & name, int v1, int v2, int v3, int v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, v1, v2, v3, v4);
	}



	void Shader::UploadUniformUInt1(const std::string & name, unsigned int i)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1ui(location, i);
	}

	void Shader::UploadUniformUInt2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, (unsigned int) vec.x, (unsigned int) vec.y);
	}

	void Shader::UploadUniformUInt3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, (unsigned int) vec.x, (unsigned int) vec.y, (unsigned int) vec.z);
	}

	void Shader::UploadUniformUInt4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, (unsigned int) vec.x, (unsigned int) vec.y, (unsigned int) vec.z, (unsigned int) vec.w);
	}

	void Shader::UploadUniformUInt2(const std::string & name, unsigned int v1, unsigned int v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, v1, v2);
	}

	void Shader::UploadUniformUInt3(const std::string & name, unsigned int v1, unsigned int v2, unsigned int v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, v1, v2, v3);
	}

	void Shader::UploadUniformUInt4(const std::string & name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, v1, v2, v3, v4);
	}



	void Shader::UploadUniformFloat1(const std::string & name, float f)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, f);
	}

	void Shader::UploadUniformFloat2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void Shader::UploadUniformFloat3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void Shader::UploadUniformFloat4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location,vec.x,vec.y,vec.z,vec.w);
	}

	void Shader::UploadUniformFloat2(const std::string & name, float v1, float v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, v1, v2);
	}

	void Shader::UploadUniformFloat3(const std::string & name, float v1, float v2, float v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, v1, v2, v3);
	}

	void Shader::UploadUniformFloat4(const std::string & name, float v1, float v2, float v3, float v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, v1, v2, v3, v4);
	}



	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}