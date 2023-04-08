#version 310 es

#extension GL_GOOGLE_include_directive : enable

#include "../include/constants.h"
#include "../include/structures.h"

layout(set = 0, binding = 0) readonly buffer _unused_name_perframe
{
    mat4 proj_view_matrix;
    uint rt_width;
    uint rt_height;
};

layout(set = 0, binding = 1) readonly buffer _unused_name_perdrawcall
{
    mat4 model_matrices[m_mesh_per_drawcall_max_instance_count];
    uint node_ids[m_mesh_per_drawcall_max_instance_count];
};


layout(location = 0) in vec3 in_position;

layout(location = 0) flat out highp uint out_nodeid;

void main()
{
    highp mat4 model_matrix = model_matrices[gl_InstanceIndex];

    highp vec3 model_position;
    
    
    model_position = in_position;

    gl_Position = proj_view_matrix * model_matrix * vec4(in_position, 1.0);

    out_nodeid = node_ids[gl_InstanceIndex];
}