#include "runtime/resource/res_type/components/rigid_body.h"


namespace SimpleEngine
{
    RigidBodyShape::RigidBodyShape(const RigidBodyShape& res) :
        m_local_transform(res.m_local_transform)
    {
        if (res.m_geometry.getTypeName() == "Box")
        {
            m_type     = RigidBodyShapeType::box;
            m_geometry = ENGINE_REFLECTION_NEW(Box);
            ENGINE_REFLECTION_DEEP_COPY(Box, m_geometry, res.m_geometry);
        }
        else
        {
           
        }
    }

    RigidBodyShape::~RigidBodyShape()
    {
        ENGINE_REFLECTION_DELETE(m_geometry);
    }
} // namespace SimpleEngine