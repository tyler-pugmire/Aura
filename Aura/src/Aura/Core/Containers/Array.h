#pragma once

#include "Aura.h"

#include <array>

namespace Aura
{
    namespace Core
    {
        template <typename T, size_t SIZE>
        using BasicArray = std::array<T, SIZE>;
    } // namespace Core
} // namespace Aura
