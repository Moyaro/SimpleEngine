#pragma once
#include "runtime\resource\res_type\components\rigid_body.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const RigidBodyShape& instance);
    template<>
    RigidBodyShape& Serializer::read(const Json& json_context, RigidBodyShape& instance);
    template<>
    Json Serializer::write(const RigidBodyComponentRes& instance);
    template<>
    RigidBodyComponentRes& Serializer::read(const Json& json_context, RigidBodyComponentRes& instance);
}//namespace

