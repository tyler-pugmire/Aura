#pragma once

#include <string>
#include <functional>
#include <unordered_map>

namespace
{
	struct WindowImpl;
}

union SDL_event;

namespace Aura
{
	class Event;
	class RenderContext;
	enum class WindowMode
	{
		Windowed,
		Fullscreen,
		BorderlessWindowed
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window();
		~Window() {}

		void Init();
		void ProcessEvents();
		void SwapBuffer();

		void SetEventCallback(EventCallbackFn const& fn) { eventCallback = fn; }

		void* GetNativeWindow();

		void Maximize();

		static Window* Create(std::string const& title,uint32_t width, uint32_t height);
	private:
		WindowImpl* window;
		EventCallbackFn eventCallback;
		RenderContext* renderContext;
	};
}