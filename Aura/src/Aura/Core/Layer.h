#pragma once

#include <string>
#include "Events/Event.h"

namespace Aura
{
    class Layer
    {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void Begin() {}
		virtual void End() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
    };
}