#pragma once
#include "runtime\resource\res_type\components\emitter.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const ParticleComponentRes& instance);
    template<>
    ParticleComponentRes& Serializer::read(const Json& json_context, ParticleComponentRes& instance);
}//namespace

