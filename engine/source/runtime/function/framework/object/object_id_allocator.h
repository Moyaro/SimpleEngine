#pragma once

#include <atomic>
#include <limits>

namespace SimpleEngine
{
    using GObjectID = std::size_t;

    constexpr GObjectID k_invalid_gobject_id = std::numeric_limits<std::size_t>::max();//无效id
    /// <summary>
    /// 为每个game object分配id
    /// </summary>
    class ObjectIDAllocator
    {
    public:
        static GObjectID alloc();//分配id

    private:
        static std::atomic<GObjectID> m_next_id;//下一个要分配的id
    };
}