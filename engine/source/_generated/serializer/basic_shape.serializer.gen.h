#pragma once
#include "runtime\resource\res_type\data\basic_shape.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const Geometry& instance);
    template<>
    Geometry& Serializer::read(const Json& json_context, Geometry& instance);
    template<>
    Json Serializer::write(const Box& instance);
    template<>
    Box& Serializer::read(const Json& json_context, Box& instance);
    template<>
    Json Serializer::write(const Sphere& instance);
    template<>
    Sphere& Serializer::read(const Json& json_context, Sphere& instance);
    template<>
    Json Serializer::write(const Capsule& instance);
    template<>
    Capsule& Serializer::read(const Json& json_context, Capsule& instance);
}//namespace

