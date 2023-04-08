#pragma once
#include "runtime\resource\res_type\components\motor.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const ControllerConfig& instance);
    template<>
    ControllerConfig& Serializer::read(const Json& json_context, ControllerConfig& instance);
    template<>
    Json Serializer::write(const PhysicsControllerConfig& instance);
    template<>
    PhysicsControllerConfig& Serializer::read(const Json& json_context, PhysicsControllerConfig& instance);
    template<>
    Json Serializer::write(const MotorComponentRes& instance);
    template<>
    MotorComponentRes& Serializer::read(const Json& json_context, MotorComponentRes& instance);
}//namespace

