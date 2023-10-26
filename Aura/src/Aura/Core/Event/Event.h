#pragma once

#include "Aura/Core/String/CRC32.h"

#include <typeinfo>

namespace Aura
{
    namespace Core
    {
        class Event
        {
        public:
            explicit Event(CRC32i name, CRC32 typeId = CRC32::INVALID) : m_name(name), m_typeId(typeId)
            {
            }
            virtual ~Event() = default;

            template <typename T>
            T const *DataAs() const
            {
                if (m_typeId != CRC32(typeid(T).name()))
                {
                    return nullptr;
                }
                return reinterpret_cast<T const *>(GetDataInternal());
            }

            CRC32i GetName() const
            {
                return m_name;
            }

            CRC32 GetTypeId() const
            {
                return m_typeId;
            }

        private:
            CRC32i m_name;
            CRC32 m_typeId;

            virtual void const *GetDataInternal() const
            {
                return nullptr;
            }
        };

        template <typename T>
        class TypedEvent : public Event
        {
        public:
            template <typename... Args>
            TypedEvent(CRC32i name, Args &&...args)
                : Event(name, CRC32(typeid(T).name())), m_data(std::forward<Args>(args)...)
            {
            }

        private:
            T m_data;

            virtual void const *GetDataInternal() const final
            {
                return &m_data;
            }
        };
    } // namespace Core
} // namespace Aura
