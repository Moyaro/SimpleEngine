#pragma once

#include "runtime/core/math/axis_aligned.h"
#include "runtime/core/math/matrix4.h"

#include <cstdint>
#include <vector>

namespace SimpleEngine
{
    /// <summary>
    /// ����Ⱦ������������Ϣ��������ģ�;������񡢲��ʵ�����
    /// </summary>
    class RenderEntity
    {
    public:
        uint32_t  m_instance_id{ 0 };
        Matrix4x4 m_model_matrix{ Matrix4x4::IDENTITY };//ģ�;���

        //����
        size_t                 m_mesh_asset_id{ 0 };
        AxisAlignedBox         m_bounding_box;//��Χ��

        //����
        size_t  m_material_asset_id{ 0 };
        bool    m_blend{ false };//�Ƿ����û��
        bool    m_double_sided{ false };//�Ƿ�����˫����Ⱦ
        Vector4 m_base_color_factor{ 1.0f, 1.0f, 1.0f, 1.0f };//������ɫ
        float   m_metallic_factor{ 1.0f };//������
        float   m_roughness_factor{ 1.0f };//�ֲڶ�
        float   m_normal_scale{ 1.0f };//����
        float   m_occlusion_strength{ 1.0f };//�������ڱ�
        Vector3 m_emissive_factor{ 0.0f, 0.0f, 0.0f };//�Է���
    };
}