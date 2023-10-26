#pragma once

#include "Aura/Core/String/CRC32.h"
#include "Event.h"
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <queue>

namespace Aura
{
    namespace Core
    {
        class EventListener;

        class EventSystem
        {
        public:
            using EventHandlerFn = std::function<void(Event const &)>;

            std::unique_ptr<EventListener> CreateListener();

            void BroadcastEvent(CRC32i name);

            template <typename T, typename... Args>
            void BroadcastEvent(CRC32i name, Args &&...args);

            void Dispatch();

        private:
            class Delegate
            {
            public:
                Delegate(EventListener const *pListener, EventHandlerFn fn) : m_pListener(pListener), m_fn(fn)
                {
                }

                EventListener const *GetListener() const;
                void Execute(Event const &e) const;

            private:
                EventListener const *m_pListener;
                EventHandlerFn m_fn;
            };

            std::mutex m_eventLock;
            std::mutex m_delegateLock;
            std::multimap<CRC32i, Delegate> m_delegates;
            std::queue<std::unique_ptr<Event>> m_events;

            void Subscribe(CRC32i name, EventListener const *pListener, EventHandlerFn fn);
            void Unsubscribe(CRC32i name);

            friend class EventListener;
        };

        class EventListener
        {
        public:
            EventListener(EventSystem *system);

            template <typename T, typename Fn>
            void Subscribe(CRC32i name, T *pInstance, Fn fn);

            void Subscribe(CRC32i name, EventSystem::EventHandlerFn fn);

            void Unsubscribe(CRC32i name);

        private:
            EventSystem *m_pSystem;
        };

        template <typename T, typename... Args>
        void EventSystem::BroadcastEvent(CRC32i name, Args &&...args)
        {
            std::scoped_lock<std::mutex> lock(m_eventLock);
            auto event = std::make_unique<TypedEvent<T>>(name, std::forward<Args>(args)...);
            m_events.push(std::move(event));
        }

        template <typename T, typename Fn>
        void EventListener::Subscribe(CRC32i name, T *pInstance, Fn fn)
        {
            m_pSystem->Subscribe(name, this, [pInstance, fn](Event const &e) { ((*pInstance).*fn)(e); });
        }

    } // namespace Core
} // namespace Aura
