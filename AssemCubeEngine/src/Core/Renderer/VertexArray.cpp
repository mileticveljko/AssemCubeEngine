#include "acpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Core/Platform/OpenGL/OpenGLVertexArray.h"

namespace ac {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();  return new OpenGLVertexArray();
		}

		AC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}