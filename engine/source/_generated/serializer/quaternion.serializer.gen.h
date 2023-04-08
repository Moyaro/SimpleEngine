#pragma once
#include "runtime\core\math\quaternion.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const Quaternion& instance);
    template<>
    Quaternion& Serializer::read(const Json& json_context, Quaternion& instance);
}//namespace

