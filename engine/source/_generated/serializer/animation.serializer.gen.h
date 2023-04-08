#pragma once
#include "runtime\resource\res_type\components\animation.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const AnimationResultElement& instance);
    template<>
    AnimationResultElement& Serializer::read(const Json& json_context, AnimationResultElement& instance);
    template<>
    Json Serializer::write(const AnimationResult& instance);
    template<>
    AnimationResult& Serializer::read(const Json& json_context, AnimationResult& instance);
    template<>
    Json Serializer::write(const AnimationComponentRes& instance);
    template<>
    AnimationComponentRes& Serializer::read(const Json& json_context, AnimationComponentRes& instance);
}//namespace

