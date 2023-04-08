#pragma once
#include "runtime/function/framework/object/object_id_allocator.h"
#include "runtime/function/render/light.h"
#include "runtime/function/render/render_common.h"
#include "runtime/function/render/render_entity.h"
#include "runtime/function/render/render_guid_allocator.h"
#include "runtime/function/render/render_object.h"

namespace SimpleEngine {
    class RenderResource;
    class RenderCamera;

    class RenderScene
    {
    public:
        // light
        AmbientLight      m_ambient_light;
        PDirectionalLight m_directional_light;
        PointLightList    m_point_light_list;

        //渲染实体
        std::vector<RenderEntity> m_render_entities;

        // axis, for editor
        std::optional<RenderEntity> m_render_axis;

        // visible objects (updated per frame)
        std::vector<RenderMeshNode> m_directional_light_visible_mesh_nodes;
        std::vector<RenderMeshNode> m_point_lights_visible_mesh_nodes;
        std::vector<RenderMeshNode> m_main_camera_visible_mesh_nodes;
        RenderAxisNode m_axis_node;

        //清理
        void clear(){}

        //每帧更新可见物体
        void updateVisibleObjects(std::shared_ptr<RenderResource> render_resource,std::shared_ptr<RenderCamera> camera);

        // set visible nodes ptr in render pass
        void setVisibleNodesReference();

        GuidAllocator<GameObjectPartId>& getInstanceIdAllocator() { return m_instance_id_allocator; }
        GuidAllocator<MeshSourceDesc>& getMeshAssetIdAllocator() { return m_mesh_asset_id_allocator; }
        GuidAllocator<MaterialSourceDesc>& getMaterialAssetdAllocator() { return m_material_asset_id_allocator; }

        void      addInstanceIdToMap(uint32_t instance_id, GObjectID go_id) { m_mesh_object_id_map[instance_id] = go_id; }
        GObjectID getGObjectIDByMeshID(uint32_t mesh_id) const;
        void deleteEntityByGObjectID(GObjectID go_id);

        //清理渲染实体、实例id分配器、map
        void clearForLevelReloading();

    private:
        //实例、网格资源、材质资源ID分配器
        GuidAllocator<GameObjectPartId>   m_instance_id_allocator;
        GuidAllocator<MeshSourceDesc>     m_mesh_asset_id_allocator;
        GuidAllocator<MaterialSourceDesc> m_material_asset_id_allocator;

        std::unordered_map<uint32_t, GObjectID> m_mesh_object_id_map;

        void updateVisibleObjectsDirectionalLight(std::shared_ptr<RenderResource> render_resource, std::shared_ptr<RenderCamera> camera);
        void updateVisibleObjectsPointLight(std::shared_ptr<RenderResource> render_resource);
        void updateVisibleObjectsMainCamera(std::shared_ptr<RenderResource> render_resource, std::shared_ptr<RenderCamera> camera);
        void updateVisibleObjectsAxis(std::shared_ptr<RenderResource> render_resource);
    };
}