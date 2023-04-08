#pragma once
#include "runtime\resource\res_type\global\global_particle.h"

namespace SimpleEngine{
    template<>
    Json Serializer::write(const GlobalParticleRes& instance);
    template<>
    GlobalParticleRes& Serializer::read(const Json& json_context, GlobalParticleRes& instance);
}//namespace

