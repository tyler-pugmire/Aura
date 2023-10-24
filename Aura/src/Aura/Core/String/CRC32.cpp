#include "CRC32.h"

namespace Aura
{
    namespace Core
    {
        const CRC32 CRC32::INVALID(Checksum::CRC_INIT);
        const CRC32i CRC32i::INVALID(Checksum::CRC_INIT);

        static_assert(CRC32("Hello, World!") == 0xEC4AC3D0);
        static_assert(CRC32i("Hello, World!") == CRC32i("HeLlO, WoRlD!"));
    } // namespace Core
} // namespace Aura
