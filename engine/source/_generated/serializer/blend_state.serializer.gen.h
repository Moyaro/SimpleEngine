#pragma once
#include "runtime\resource\res_type\data\blend_state.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const BoneBlendWeight& instance);
    template<>
    BoneBlendWeight& Serializer::read(const Json& json_context, BoneBlendWeight& instance);
    template<>
    Json Serializer::write(const BlendStateWithClipData& instance);
    template<>
    BlendStateWithClipData& Serializer::read(const Json& json_context, BlendStateWithClipData& instance);
    template<>
    Json Serializer::write(const BlendState& instance);
    template<>
    BlendState& Serializer::read(const Json& json_context, BlendState& instance);
}//namespace

