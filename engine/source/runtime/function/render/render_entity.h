#pragma once

#include "runtime/core/math/axis_aligned.h"
#include "runtime/core/math/matrix4.h"

#include <cstdint>
#include <vector>

namespace SimpleEngine
{
    /// <summary>
    /// 可渲染的物体的相关信息，包括其模型矩阵、网格、材质等属性
    /// </summary>
    class RenderEntity
    {
    public:
        uint32_t  m_instance_id{ 0 };
        Matrix4x4 m_model_matrix{ Matrix4x4::IDENTITY };//模型矩阵

        //网格
        size_t                 m_mesh_asset_id{ 0 };
        AxisAlignedBox         m_bounding_box;//包围盒

        //材质
        size_t  m_material_asset_id{ 0 };
        bool    m_blend{ false };//是否启用混合
        bool    m_double_sided{ false };//是否启用双面渲染
        Vector4 m_base_color_factor{ 1.0f, 1.0f, 1.0f, 1.0f };//基础颜色
        float   m_metallic_factor{ 1.0f };//金属度
        float   m_roughness_factor{ 1.0f };//粗糙度
        float   m_normal_scale{ 1.0f };//法线
        float   m_occlusion_strength{ 1.0f };//环境光遮蔽
        Vector3 m_emissive_factor{ 0.0f, 0.0f, 0.0f };//自发光
    };
}