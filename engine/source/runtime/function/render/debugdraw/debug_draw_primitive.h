#pragma once

#include "runtime/function/render/interface/rhi.h"
#include "runtime/core/math/math_headers.h"
/// <summary>
/// 原始物体各项属性
/// </summary>
namespace SimpleEngine {

    //infinity和one_frame的时间
    static const float k_debug_draw_infinity_life_time = -2.f;
    static const float k_debug_draw_one_frame = 0.0f;

	//时间类型
	enum DebugDrawTimeType : uint8_t
	{
		_debugDrawTimeType_infinity,
		_debugDrawTimeType_one_frame,
		_debugDrawTimeType_common
	};

	//填充模式
	enum FillMode : uint8_t {
		_FillMode_wireframe = 0,
		_FillMode_solid = 1,
		_FillMode_count,
	};

	//原始物体类型
	enum DebugDrawPrimitiveType : uint8_t
	{
		_debug_draw_primitive_type_point = 0,
		_debug_draw_primitive_type_line,
		_debug_draw_primitive_type_triangle,
		_debug_draw_primitive_type_quad,
        _debug_draw_primitive_type_box,
        _debug_draw_primitive_type_cylinder,
        _debug_draw_primitive_type_sphere,
        _debug_draw_primitive_type_capsule,
        _debug_draw_primitive_type_text,
		k_debug_draw_primitive_type_count
	};

    

    //顶点信息：位置、颜色、纹理坐标
    class DebugDrawVertex
    {
    public:
        Vector3 pos;
        Vector4 color;
        Vector2 texcoord;
        DebugDrawVertex() { pos = Vector3(-1.0f, -1.0f, -1.0f); color = Vector4(-1.0f, -1.0f, -1.0f, -1.0f); texcoord = Vector2(-1.0f, -1.0f); }

        //获取绑定信息
        static std::array<VkVertexInputBindingDescription, 1> getBindingDescriptions()
        {
            //顶点数据从内存加载的速率
            std::array<VkVertexInputBindingDescription, 1> binding_descriptions;
            binding_descriptions[0].binding = 0;//绑定索引
            binding_descriptions[0].stride = sizeof(DebugDrawVertex);//一个条目到下一个条目的字节数
            binding_descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;//移动到每个顶点后的下一个数据条目

            return binding_descriptions;
        }

        //处理顶点输入
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 3> attribute_descriptions{};

            // position
            attribute_descriptions[0].binding = 0;
            attribute_descriptions[0].location = 0;
            attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attribute_descriptions[0].offset = offsetof(DebugDrawVertex, pos);//字节偏移量

            // color
            attribute_descriptions[1].binding = 0;
            attribute_descriptions[1].location = 1;
            attribute_descriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
            attribute_descriptions[1].offset = offsetof(DebugDrawVertex, color);

            // texcoord
            attribute_descriptions[2].binding = 0;
            attribute_descriptions[2].location = 2;
            attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attribute_descriptions[2].offset = offsetof(DebugDrawVertex, texcoord);

            return attribute_descriptions;
        }
    };

    //原始物体：记录时间类型、生命周期、填充模式、是否深度测试
    class DebugDrawPrimitive
    {
    public:
        DebugDrawTimeType m_time_type{ _debugDrawTimeType_infinity };
        float m_life_time{ 0.f };
        FillMode m_fill_mode{ _FillMode_wireframe };
        bool m_no_depth_test = false;

    public:
        bool isTimeOut(float delta_time);
        void setTime(float in_life_time);

    private:
        bool m_rendered = false;//用于只渲染一次的物体
    };

    //点、线、三角形、平面类
    class DebugDrawPoint : public DebugDrawPrimitive
    {
    public:
        DebugDrawVertex m_vertex;
        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_point;
    };

    class DebugDrawLine : public DebugDrawPrimitive
    {
    public:
        DebugDrawVertex m_vertex[2];
        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_line;
    };

    class DebugDrawTriangle : public DebugDrawPrimitive
    {
    public:
        DebugDrawVertex m_vertex[3];
        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_triangle;
    };

    class DebugDrawQuad : public DebugDrawPrimitive
    {
    public:
        DebugDrawVertex m_vertex[4];
        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_quad;
    };

    class DebugDrawBox : public DebugDrawPrimitive
    {
    public:
        Vector3 m_center_point;
        Vector3 m_half_extents;
        Vector4 m_color;
        Vector4 m_rotate;

        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_box;
    };

    class DebugDrawCylinder : public DebugDrawPrimitive
    {
    public:
        Vector3 m_center;
        Vector4 m_rotate;
        float   m_radius{ 0.f };
        float   m_height{ 0.f };
        Vector4 m_color;

        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_cylinder;
    };
    class DebugDrawSphere : public DebugDrawPrimitive
    {
    public:
        Vector3 m_center;
        float   m_radius{ 0.f };
        Vector4 m_color;

        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_sphere;
    };

    class DebugDrawCapsule : public DebugDrawPrimitive
    {
    public:
        Vector3 m_center;
        Vector4 m_rotation;
        Vector3 m_scale;
        float   m_radius{ 0.f };
        float   m_height{ 0.f };
        Vector4 m_color;

        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_capsule;
    };

    class DebugDrawText : public DebugDrawPrimitive
    {
    public:
        std::string m_content;//内容
        Vector4     m_color;
        Vector3     m_coordinate;//坐标
        int         m_size;//字体大小
        bool        m_is_screen_text;

        static const DebugDrawPrimitiveType k_type_enum_value = _debug_draw_primitive_type_text;
    };
}