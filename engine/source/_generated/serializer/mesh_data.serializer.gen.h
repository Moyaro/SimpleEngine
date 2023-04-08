#pragma once
#include "runtime\resource\res_type\data\mesh_data.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const Vertex& instance);
    template<>
    Vertex& Serializer::read(const Json& json_context, Vertex& instance);
    template<>
    Json Serializer::write(const SkeletonBinding& instance);
    template<>
    SkeletonBinding& Serializer::read(const Json& json_context, SkeletonBinding& instance);
    template<>
    Json Serializer::write(const MeshData& instance);
    template<>
    MeshData& Serializer::read(const Json& json_context, MeshData& instance);
}//namespace

