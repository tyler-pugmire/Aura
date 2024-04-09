#pragma once

#include "Aura.h"
#include "EASTL/array.h"

#include <compare>
#include <string>

namespace Aura
{
    namespace Core
    {
        class Checksum
        {
        public:
            constexpr Checksum() : m_checksum(CRC_INIT){};
            constexpr Checksum(u32 checksum) : m_checksum(checksum)
            {
            }

            static constexpr u32 CRC_INIT = 0xFFFFFFFF;
            constexpr inline u32 AsU32() const
            {
                return m_checksum;
            }

            auto operator<=>(Checksum const &right) const = default;

        protected:
            static constexpr u32 s_polynomial = 0xEDB88320;
            static constexpr eastl::array<u32, 256> s_lookup = []() {
                eastl::array<u32, 256> table = {};

                for (s32 i = 0; i < table.size(); ++i)
                {
                    u32 crc = i;
                    for (u32 j = 0; j < 8; ++j)
                    {
                        crc = (crc >> 1) ^ (-int(crc & 1) & s_polynomial);
                    }
                    table[i] = crc;
                }
                return table;
            }();
            u32 m_checksum;
        };

        class CRC32 : public Checksum
        {
        public:
            static const CRC32 INVALID;

            constexpr CRC32(u32 checksum) : Checksum(checksum)
            {
            }

            constexpr CRC32(char const *str) : Checksum(Hash(str, std::string::traits_type::length(str)))
            {
            }

            auto operator<=>(CRC32 const &right) const = default;

            static constexpr u32 Hash(char const *str, size_t len)
            {
                u32 crc = ~0;
                for (size_t i = 0; i < len; ++i)
                {
                    crc = (crc >> 8) ^ s_lookup[(crc & 0xFF) ^ *str++];
                }
                return ~crc;
            }
        };

        class CRC32i : public Checksum
        {
        public:
            static const CRC32i INVALID;
            constexpr CRC32i(u32 checksum) : Checksum(checksum)
            {
            }

            constexpr CRC32i(char const *str) : Checksum(Hash(str, std::string::traits_type::length(str)))
            {
            }

            static constexpr u32 Hash(char const *str, size_t len)
            {
                u32 crc = ~0;
                for (size_t i = 0; i < len; ++i)
                {
                    char c = str[i];
                    c = (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
                    crc = (crc >> 8) ^ s_lookup[(crc & 0xFF) ^ c];
                }
                return ~crc;
            }

            auto operator<=>(CRC32i const &right) const = default;
        };

#define CRC_STATIC(str)                                                                                                \
    std::integral_constant<u32, Aura::Core::CRC32::Hash(str, std::string::traits_type::length(str))>::value

#define CRCi_STATIC(str)                                                                                               \
    std::integral_constant<u32, Aura::Core::CRC32i::Hash(str, std::string::traits_type::length(str))>::value

    } // namespace Core
} // namespace Aura
