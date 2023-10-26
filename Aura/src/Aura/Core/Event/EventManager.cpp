#include "EventManager.h"

#include <iostream>

namespace Aura
{
    namespace Core
    {

        std::unique_ptr<EventListener> EventSystem::CreateListener()
        {
            return std::make_unique<EventListener>(this);
        }

        void EventSystem::BroadcastEvent(CRC32i name)
        {
            std::scoped_lock<std::mutex> lock(m_eventLock);
            auto event = std::make_unique<Event>(name);
            m_events.push(std::move(event));
        }

        void EventSystem::Dispatch()
        {
            std::queue<std::unique_ptr<Event>> events;
            {
                std::scoped_lock<std::mutex> lock(m_eventLock);
                while (!m_events.empty())
                {
                    events.push(std::move(m_events.front()));
                    m_events.pop();
                }
            }

            while (!events.empty())
            {
                auto event = std::move(events.front());
                std::cout << event->GetName().AsU32() << "\n";
                events.pop();
                std::vector<Delegate> delegates;
                {
                    std::scoped_lock<std::mutex> lock(m_delegateLock);
                    auto range = m_delegates.equal_range(event->GetName());
                    for (auto delegate = range.first; delegate != range.second; ++delegate)
                    {
                        delegates.push_back(delegate->second);
                    }
                }

                for (auto &delegate : delegates)
                {
                    delegate.Execute(*event);
                }
            }
        }

        void EventSystem::Subscribe(CRC32i name, EventListener const *pListener, EventHandlerFn fn)
        {
            std::scoped_lock<std::mutex> lock(m_delegateLock);
            m_delegates.emplace(name, Delegate(pListener, fn));
        }

        EventListener const *EventSystem::Delegate::GetListener() const
        {
            return m_pListener;
        }

        void EventSystem::Delegate::Execute(Event const &e) const
        {
            m_fn(e);
        }

        EventListener::EventListener(EventSystem *system) : m_pSystem(system)
        {
        }

        void EventListener::Subscribe(CRC32i name, EventSystem::EventHandlerFn fn)
        {
            m_pSystem->Subscribe(name, this, fn);
        }

    } // namespace Core
} // namespace Aura
