#include "engineph.h"
#include "RenderCommand.h"

namespace Kuro
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
