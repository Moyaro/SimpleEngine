#pragma once
#include "runtime\resource\res_type\data\skeleton_mask.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const BoneBlendMask& instance);
    template<>
    BoneBlendMask& Serializer::read(const Json& json_context, BoneBlendMask& instance);
}//namespace

