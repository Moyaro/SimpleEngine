#pragma once

#include "runtime/core/math/matrix4.h"
#include "runtime/function/framework/object/object_id_allocator.h"
#include <string>
#include <vector>

namespace SimpleEngine {

    //网格
    REFLECTION_TYPE(GameObjectMeshDesc)
        STRUCT(GameObjectMeshDesc, Fields)
    {
        REFLECTION_BODY(GameObjectMeshDesc)
            std::string m_mesh_file;
    };

    //材质
    REFLECTION_TYPE(GameObjectMaterialDesc)
        STRUCT(GameObjectMaterialDesc, Fields)
    {
        REFLECTION_BODY(GameObjectMaterialDesc)
        std::string m_base_color_texture_file;
        std::string m_metallic_roughness_texture_file;
        std::string m_normal_texture_file;
        std::string m_occlusion_texture_file;
        std::string m_emissive_texture_file;
        bool m_with_texture{ false };
    };

    //移动
    REFLECTION_TYPE(GameObjectTransformDesc)
        STRUCT(GameObjectTransformDesc, WhiteListFields)
    {
        REFLECTION_BODY(GameObjectTransformDesc)
            Matrix4x4 m_transform_matrix {
            Matrix4x4::IDENTITY
        };
    };

    //物体信息
    REFLECTION_TYPE(GameObjectPartDesc)
        STRUCT(GameObjectPartDesc, Fields)
    {
        REFLECTION_BODY(GameObjectPartDesc)
        GameObjectMeshDesc m_mesh_desc;
        GameObjectMaterialDesc  m_material_desc;
        GameObjectTransformDesc m_transform_desc;
        bool m_with_animation{ false };
    };

    constexpr size_t k_invalid_part_id = std::numeric_limits<size_t>::max();

    //物体的组件ID
    struct GameObjectPartId
    {
        GObjectID m_go_id{ k_invalid_gobject_id };
        size_t    m_part_id{ k_invalid_part_id };

        bool   operator==(const GameObjectPartId& rhs) const { return m_go_id == rhs.m_go_id && m_part_id == rhs.m_part_id; }
        size_t getHashValue() const { return m_go_id ^ (m_part_id << 1); }
        bool   isValid() const { return m_go_id != k_invalid_gobject_id && m_part_id != k_invalid_part_id; }
    };

    //物体
    class GameObjectDesc
    {
    public:
        GameObjectDesc() : m_go_id(0) {}
        GameObjectDesc(size_t go_id, const std::vector<GameObjectPartDesc>& parts) :m_go_id(go_id), m_object_parts(parts){}

        GObjectID getId() const { return m_go_id; }
        const std::vector<GameObjectPartDesc>& getObjectParts() const { return m_object_parts; }
    private:
        GObjectID m_go_id{ k_invalid_gobject_id };
        std::vector<GameObjectPartDesc> m_object_parts;
    };
    
}
    //自定义hash值求法
    template<>
    struct std::hash<SimpleEngine::GameObjectPartId>
    {
        size_t operator()(const SimpleEngine::GameObjectPartId& rhs) const noexcept { return rhs.getHashValue(); }
    };