#pragma once
#include "runtime\function\framework\component\component.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const Component& instance);
    template<>
    Component& Serializer::read(const Json& json_context, Component& instance);
}//namespace

