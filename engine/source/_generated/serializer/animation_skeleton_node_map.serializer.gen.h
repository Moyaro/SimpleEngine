#pragma once
#include "runtime\resource\res_type\data\animation_skeleton_node_map.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const AnimSkelMap& instance);
    template<>
    AnimSkelMap& Serializer::read(const Json& json_context, AnimSkelMap& instance);
}//namespace

