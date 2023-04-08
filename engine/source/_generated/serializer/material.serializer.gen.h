#pragma once
#include "runtime\resource\res_type\data\material.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const MaterialRes& instance);
    template<>
    MaterialRes& Serializer::read(const Json& json_context, MaterialRes& instance);
}//namespace

