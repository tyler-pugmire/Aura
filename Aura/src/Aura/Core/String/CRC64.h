#pragma once

#include "Aura.h"
#include "EASTL/array.h"

#include <compare>
#include <string>
namespace Aura
{
    namespace Core
    {
        class Checksum64
        {
        public:
            constexpr Checksum64() : m_checksum(CRC_INIT){};
            constexpr Checksum64(u64 checksum) : m_checksum(checksum)
            {
            }

            static constexpr u64 CRC_INIT = 0xFFFFFFFFFFFFFFFFULL;
            constexpr inline u64 AsU64() const
            {
                return m_checksum;
            }

            auto operator<=>(Checksum64 const &right) const = default;

        protected:
            static constexpr u64 s_polynomial = 0xD800000000000000ULL;
            static constexpr eastl::array<u64, 256> s_lookup = []() {
                eastl::array<u64, 256> table = {};

                for (std::uint32_t i = 0; i < 256; ++i)
                {
                    u64 crc = i;
                    for (std::uint32_t j = 0; j < 8; ++j)
                    {
                        crc = (crc & 1) ? (crc >> 1) ^ s_polynomial : crc >> 1;
                    }
                    table[i] = crc;
                }
                return table;
            }();
            u64 m_checksum;
        };

        class CRC64 : public Checksum64
        {
        public:
            static const CRC64 INVALID;

            constexpr CRC64(u64 checksum) : Checksum64(checksum)
            {
            }

            constexpr CRC64(char const *str) : Checksum64(Hash(str, std::string::traits_type::length(str)))
            {
            }

            static constexpr u64 Hash(char const *str, size_t len)
            {
                u64 crc = ~0;
                for (size_t i = 0; i < len; ++i)
                {
                    crc = (crc >> 8) ^ s_lookup[(crc & 0xFF) ^ *str++];
                }
                return ~crc;
            }

            auto operator<=>(CRC64 const &right) const = default;
        };

        class CRC64i : public Checksum64
        {
        public:
            static const CRC64i INVALID;
            constexpr CRC64i(u64 checksum) : Checksum64(checksum)
            {
            }

            constexpr CRC64i(char const *str) : Checksum64(Hash(str, std::string::traits_type::length(str)))
            {
            }

            static constexpr u64 Hash(char const *str, size_t len)
            {
                u64 crc = ~0;
                for (size_t i = 0; i < len; ++i)
                {
                    char c = str[i];
                    c = (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
                    crc = (crc >> 8) ^ s_lookup[(crc & 0xFF) ^ c];
                }
                return ~crc;
            }

            auto operator<=>(CRC64i const &right) const = default;
        };

        using PathHash = CRC64i;

#define CRC64_STATIC(str)                                                                                              \
    std::integral_constant<u64, Aura::Core::CRC64::Hash(str, std::string::traits_type::length(str))>::value

#define CRC64i_STATIC(str)                                                                                             \
    std::integral_constant<u64, Aura::Core::CRC64i::Hash(str, std::string::traits_type::length(str))>::value

#define PATH_HASH_STATIC(str)                                                                                          \
    std::integral_constant<u64, Aura::Core::CRC64i::Hash(str, std::string::traits_type::length(str))>::value

    } // namespace Core
} // namespace Aura
