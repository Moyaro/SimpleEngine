#pragma once
#include "runtime\function\framework\component\rigidbody\rigidbody_component.h"
#include "_generated\serializer\component.serializer.gen.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const RigidBodyComponent& instance);
    template<>
    RigidBodyComponent& Serializer::read(const Json& json_context, RigidBodyComponent& instance);
}//namespace

