#include "acpch.h"
#include "RenderCommand.h"

#include "Core/Platform/OpenGL/OpenGLRendererAPI.h"

namespace ac {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}