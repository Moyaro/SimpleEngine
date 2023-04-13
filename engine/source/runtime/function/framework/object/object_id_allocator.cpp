#include "runtime/function/framework/object/object_id_allocator.h"
#include <stdexcept>

namespace SimpleEngine
{
    std::atomic<GObjectID> ObjectIDAllocator::m_next_id{ 0 };

    GObjectID ObjectIDAllocator::alloc()
    {
        std::atomic<GObjectID> new_object_id = m_next_id.load();
        m_next_id++;
        if (m_next_id > k_invalid_gobject_id)
        {
            throw std::runtime_error("id分配超过上限！");
        }

        return new_object_id;
    }

}