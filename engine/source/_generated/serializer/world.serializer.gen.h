#pragma once
#include "runtime\resource\res_type\common\world.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const WorldRes& instance);
    template<>
    WorldRes& Serializer::read(const Json& json_context, WorldRes& instance);
}//namespace

