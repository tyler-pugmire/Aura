#include "CRC64.h"

namespace Aura
{
    namespace Core
    {
        const CRC64 CRC64::INVALID(Checksum64::CRC_INIT);
        const CRC64i CRC64i::INVALID(Checksum64::CRC_INIT);

        static_assert(CRC64("dir/filename.txt") == CRC64(0x19A496F2D8E31CECULL));
        static_assert(PathHash("dir/filename.txt") == PathHash("Dir/FileName.TxT"));
    } // namespace Core
} // namespace Aura
