#pragma once

#include "engineph.h"

#include "engine/Core.h"
#include "engine/event/Event.h"

namespace Kuro
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(
			const std::string& title = "Kuro Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title(title), Width(width), Height(height)
		{
		}
	};

	class KURO_API Window
	{
	public:
		virtual ~Window();

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual void IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}