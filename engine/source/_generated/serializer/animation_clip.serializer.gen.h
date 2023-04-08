#pragma once
#include "runtime\resource\res_type\data\animation_clip.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const AnimNodeMap& instance);
    template<>
    AnimNodeMap& Serializer::read(const Json& json_context, AnimNodeMap& instance);
    template<>
    Json Serializer::write(const AnimationChannel& instance);
    template<>
    AnimationChannel& Serializer::read(const Json& json_context, AnimationChannel& instance);
    template<>
    Json Serializer::write(const AnimationClip& instance);
    template<>
    AnimationClip& Serializer::read(const Json& json_context, AnimationClip& instance);
    template<>
    Json Serializer::write(const AnimationAsset& instance);
    template<>
    AnimationAsset& Serializer::read(const Json& json_context, AnimationAsset& instance);
}//namespace

