#include "runtime/function/framework/component/mesh/mesh_component.h"

#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/resource/res_type/data/material.h"

#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/framework/object/object.h"
#include "runtime/function/global/global_context.h"

#include "runtime/function/render/render_swap_context.h"
#include "runtime/function/render/render_system.h"

namespace SimpleEngine
{
    void MeshComponent::postLoadResource(std::weak_ptr<GObject> parent_object)
    {
        //设置父物体
        m_parent_object = parent_object;

        std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
        assert(asset_manager);

        //遍历所有网格资源,从中获取信息后放入网格描述信息里
        m_raw_meshes.resize(m_mesh_res.m_sub_meshes.size());

        size_t raw_mesh_count = 0;
        for (const SubMeshRes& sub_mesh : m_mesh_res.m_sub_meshes)
        {
            GameObjectPartDesc& meshComponent = m_raw_meshes[raw_mesh_count];//网格描述信息
            meshComponent.m_mesh_desc.m_mesh_file = asset_manager->getFullPath(sub_mesh.m_obj_file_ref).generic_string();//获取mesh_file全路径

            meshComponent.m_material_desc.m_with_texture = sub_mesh.m_material.empty() == false;//检查对应资源材质是否有地址

            if (meshComponent.m_material_desc.m_with_texture)//如果有材质资源，就读取进material_res，然后把全路径赋给meshComponent
            {
                MaterialRes material_res;
                asset_manager->loadAsset(sub_mesh.m_material, material_res);

                meshComponent.m_material_desc.m_base_color_texture_file =
                    asset_manager->getFullPath(material_res.m_base_colour_texture_file).generic_string();
                meshComponent.m_material_desc.m_metallic_roughness_texture_file =
                    asset_manager->getFullPath(material_res.m_metallic_roughness_texture_file).generic_string();
                meshComponent.m_material_desc.m_normal_texture_file =
                    asset_manager->getFullPath(material_res.m_normal_texture_file).generic_string();
                meshComponent.m_material_desc.m_occlusion_texture_file =
                    asset_manager->getFullPath(material_res.m_occlusion_texture_file).generic_string();
                meshComponent.m_material_desc.m_emissive_texture_file =
                    asset_manager->getFullPath(material_res.m_emissive_texture_file).generic_string();
            }

            auto object_space_transform = sub_mesh.m_transform.getMatrix();

            meshComponent.m_transform_desc.m_transform_matrix = object_space_transform;//获取transform

            ++raw_mesh_count;
        }
    }

    void MeshComponent::tick(float delta_time)
    {
        if (!m_parent_object.lock())
            return;

        TransformComponent* transform_component = m_parent_object.lock()->tryGetComponent(TransformComponent);//获取变换组件

        if (transform_component->isDirty())//如果人物位置要改变，就把人物身上的每个子网格还未改变的变换矩阵交给渲染重新更新资源
        {
            std::vector<GameObjectPartDesc> dirty_mesh_parts;
            for (GameObjectPartDesc& mesh_part : m_raw_meshes)
            {
                Matrix4x4 object_transform_matrix = mesh_part.m_transform_desc.m_transform_matrix;

                mesh_part.m_transform_desc.m_transform_matrix = transform_component->getMatrix() * object_transform_matrix;
                dirty_mesh_parts.push_back(mesh_part);

                mesh_part.m_transform_desc.m_transform_matrix = object_transform_matrix;
            }

            RenderSwapContext& render_swap_context = g_runtime_global_context.m_render_system->getSwapContext();
            SwapData& logic_swap_data = render_swap_context.getLogicSwapData();

            logic_swap_data.addDirtyGameObject(GameObjectDesc{ m_parent_object.lock()->getID(), dirty_mesh_parts });

            transform_component->setDirtyFlag(false);
        }
    }
}