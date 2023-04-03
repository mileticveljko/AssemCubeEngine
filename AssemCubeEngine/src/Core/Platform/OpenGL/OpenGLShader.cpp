#include "acpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace ac
{

	OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		// Vertex OpenGLShader
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
			AC_CORE_ASSERT(false, "Vertex Shader compilation failure!");

			return;
		}


		// Fragment OpenGLShader
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
			AC_CORE_ASSERT(false, "Fragment OpenGLShader compilation failure!");

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

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}



	void OpenGLShader::UploadUniformInt1(const std::string & name, int i)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1ui(location, i);
	}

	void OpenGLShader::UploadUniformInt2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, (int)vec.x, (int)vec.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, (int)vec.x, (int)vec.y, (int)vec.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, (int)vec.x, (int)vec.y, (int)vec.z, (int)vec.w);
	}

	void OpenGLShader::UploadUniformInt2(const std::string & name, int v1, int v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, v1, v2);
	}

	void OpenGLShader::UploadUniformInt3(const std::string & name, int v1, int v2, int v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, v1, v2, v3);
	}

	void OpenGLShader::UploadUniformInt4(const std::string & name, int v1, int v2, int v3, int v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, v1, v2, v3, v4);
	}



	void OpenGLShader::UploadUniformUInt1(const std::string & name, unsigned int i)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1ui(location, i);
	}

	void OpenGLShader::UploadUniformUInt2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, (unsigned int)vec.x, (unsigned int)vec.y);
	}

	void OpenGLShader::UploadUniformUInt3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, (unsigned int)vec.x, (unsigned int)vec.y, (unsigned int)vec.z);
	}

	void OpenGLShader::UploadUniformUInt4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, (unsigned int)vec.x, (unsigned int)vec.y, (unsigned int)vec.z, (unsigned int)vec.w);
	}

	void OpenGLShader::UploadUniformUInt2(const std::string & name, unsigned int v1, unsigned int v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, v1, v2);
	}

	void OpenGLShader::UploadUniformUInt3(const std::string & name, unsigned int v1, unsigned int v2, unsigned int v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, v1, v2, v3);
	}

	void OpenGLShader::UploadUniformUInt4(const std::string & name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, v1, v2, v3, v4);
	}



	void OpenGLShader::UploadUniformFloat1(const std::string & name, float f)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, f);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string & name, const glm::vec2 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string & name, const glm::vec4 & vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string & name, float v1, float v2)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, v1, v2);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string & name, float v1, float v2, float v3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, v1, v2, v3);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string & name, float v1, float v2, float v3, float v4)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, v1, v2, v3, v4);
	}

	void OpenGLShader::UploadUniformMat2(const std::string & name, const glm::mat2 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat2x3(const std::string & name, const glm::mat2x3 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3x2(const std::string & name, const glm::mat3x2 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat2x4(const std::string & name, const glm::mat2x4 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4x2(const std::string & name, const glm::mat4x2 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3x4(const std::string & name, const glm::mat3x4 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4x3(const std::string & name, const glm::mat4x3 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}