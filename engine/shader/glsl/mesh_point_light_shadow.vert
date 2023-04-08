#version 310 es

#extension GL_GOOGLE_include_directive : enable

#include "../include/constants.h"
#include "../include/structures.h"

layout(set = 0, binding = 1) readonly buffer _unused_name_per_drawcall
{
    VulkanMeshInstance mesh_instances[m_mesh_per_drawcall_max_instance_count];
};

layout(location = 0) in highp vec3 in_position;

layout(location = 0) out highp vec3 out_position_world_space;

void main()
{
    highp mat4 model_matrix = mesh_instances[gl_InstanceIndex].model_matrix;

    highp vec3 model_position;
    model_position = in_position;

    out_position_world_space = (model_matrix * vec4(model_position, 1.0)).xyz;
}
