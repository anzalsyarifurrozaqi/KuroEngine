#pragma once

#include "engine/Core.h"
#include "engine/event/Event.h"

namespace Kuro
{
	class KURO_API Layer
	{
	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event &event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	
	private:
		std::string m_DebugName;
	};
}