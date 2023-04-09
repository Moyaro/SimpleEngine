#pragma once
#include "runtime\core\math\transform.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const Transform& instance);
    template<>
    Transform& Serializer::read(const Json& json_context, Transform& instance);
}//namespace
