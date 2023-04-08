#pragma once

#include <atomic>
#include <limits>

namespace SimpleEngine
{
    using GObjectID = std::size_t;

    constexpr GObjectID k_invalid_gobject_id = std::numeric_limits<std::size_t>::max();//��Чid
    /// <summary>
    /// Ϊÿ��game object����id
    /// </summary>
    class ObjectIDAllocator
    {
    public:
        static GObjectID alloc();//����id

    private:
        static std::atomic<GObjectID> m_next_id;//��һ��Ҫ�����id
    };
}