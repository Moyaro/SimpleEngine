#include "render_system.h"
#include "interface/rhi.h"
#include "interface/vulkan_rhi.h"
#include "resource/asset_manager/asset_manager.h"
#include "resource/config_manager/config_manager.h"
#include "function/render/debugdraw/debug_draw_manager.h"
#include "function/global/global_context.h"
#include "render_resource.h"
#include "render_pipeline.h"
#include "render_camera.h"
#include "runtime/function/render/render_scene.h"
#include "resource/res_type/global/global_rendering.h"
#include "runtime/function/render/render_pass.h"
#include "runtime/function/render/passes/main_camera_pass.h"
#include "core/base/macro.h"
#include <cassert>

namespace SimpleEngine {
	void RenderSystem::init(RenderSystemInitInfo init_info) {
		//获取配置、资产管理器
		std::shared_ptr<ConfigManager> config_manager = g_runtime_global_context.m_config_manager;
		assert(config_manager);
		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
		assert(asset_manager);

		//初始化RHI
		RHIInitInfo rhi_init_info;
		rhi_init_info.windowSystem = init_info.window_system;
		m_rhi = std::make_shared<VulkanRHI>();
		m_rhi->init(rhi_init_info);

		//获取全局渲染资源
		GlobalRenderingRes global_rendering_res;
		const std::string& global_rendering_res_url = config_manager->getGlobalRenderingResUrl();
		asset_manager->loadAsset(global_rendering_res_url, global_rendering_res);

		//初始化渲染资源
		//加载环境光
		LevelResourceDesc level_resource_desc;
		level_resource_desc.m_ibl_resource_desc.m_skybox_irradiance_map = global_rendering_res.m_skybox_irradiance_map;
		level_resource_desc.m_ibl_resource_desc.m_skybox_specular_map = global_rendering_res.m_skybox_specular_map;
		level_resource_desc.m_ibl_resource_desc.m_brdf_map = global_rendering_res.m_brdf_map;

		m_render_resource = std::make_shared<RenderResource>();
		m_render_resource->uploadGlobalRenderResource(m_rhi, level_resource_desc);


		//初始化摄像机
		m_render_camera = std::make_shared<RenderCamera>();
		const CameraPose& camera_pose = global_rendering_res.m_camera_config.m_pose;
		m_render_camera->lookAt(camera_pose.m_position, camera_pose.m_target, camera_pose.m_up);
		m_render_camera->m_zfar = global_rendering_res.m_camera_config.m_z_far;
		m_render_camera->m_znear = global_rendering_res.m_camera_config.m_z_near;
		m_render_camera->setAspect(global_rendering_res.m_camera_config.m_aspect.x / global_rendering_res.m_camera_config.m_aspect.y);

		//初始化场景
        m_render_scene = std::make_shared<RenderScene>();
        m_render_scene->m_ambient_light = { global_rendering_res.m_ambient_light.toVector3() };
        m_render_scene->m_directional_light.m_direction =
            global_rendering_res.m_directional_light.m_direction.normalisedCopy();
        m_render_scene->m_directional_light.m_color = global_rendering_res.m_directional_light.m_color.toVector3();
		m_render_scene->setVisibleNodesReference();

		//初始化渲染管线
		RenderPipelineInitInfo pipeline_init_info;
		pipeline_init_info.render_resource = m_render_resource;
		m_render_pipeline = std::make_shared<RenderPipeline>();
		m_render_pipeline->m_rhi = m_rhi;
		m_render_pipeline->init(pipeline_init_info);

		// descriptor set layout in main camera pass will be used when uploading resource
		std::static_pointer_cast<RenderResource>(m_render_resource)->m_mesh_descriptor_set_layout = &static_cast<RenderPass*>(m_render_pipeline->m_main_camera_pass.get())->m_descriptor_infos[MainCameraPass::LayoutType::_per_mesh].layout;
		std::static_pointer_cast<RenderResource>(m_render_resource)->m_material_descriptor_set_layout = &static_cast<RenderPass*>(m_render_pipeline->m_main_camera_pass.get())->m_descriptor_infos[MainCameraPass::LayoutType::_mesh_per_material].layout;

	}

	void RenderSystem::tick(float delta_time) {
		processSwapData();
		m_rhi->prepareContext();//获取目前的命令缓冲

        m_render_resource->updatePerFrameBuffer(m_render_scene, m_render_camera);

		//更新可见物体
		m_render_scene->updateVisibleObjects(std::static_pointer_cast<RenderResource>(m_render_resource),m_render_camera);

		m_render_pipeline->preparePassData(m_render_resource);

		g_runtime_global_context.m_debugdraw_manager->tick(delta_time);

		m_render_pipeline->forwardRender(m_render_resource);
	}

    //***********************************轴*******************************************//

    void RenderSystem::createAxis(std::array<RenderEntity, 3> axis_entities, std::array<RenderMeshData, 3> mesh_datas)
    {
        for (int i = 0; i < axis_entities.size(); i++)
        {
            m_render_resource->uploadGameObjectRenderResource(m_rhi, axis_entities[i], mesh_datas[i]);
        }
    }

    void RenderSystem::setVisibleAxis(std::optional<RenderEntity> axis)
    {
        m_render_scene->m_render_axis = axis;

        if (axis.has_value())
        {
            std::static_pointer_cast<RenderPipeline>(m_render_pipeline)->setAxisVisibleState(true);
        }
        else
        {
            std::static_pointer_cast<RenderPipeline>(m_render_pipeline)->setAxisVisibleState(false);
        }
    }

    void RenderSystem::setSelectedAxis(size_t selected_axis)
    {
        std::static_pointer_cast<RenderPipeline>(m_render_pipeline)->setSelectedAxis(selected_axis);
    }

	
    //***********************************视口*******************************************//

	EngineContentViewport RenderSystem::getEngineContentViewport() const {
        float x = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.x;
        float y = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.y;
        float width = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.width;
        float height = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.height;
        return { x, y, width, height };
	}


	void RenderSystem::updateEngineContentViewport(float offset_x, float offset_y, float width, float height) {
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.x = offset_x;
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.y = offset_y;
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.width = width;
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.height = height;
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.minDepth = 0.0f;
        std::static_pointer_cast<VulkanRHI>(m_rhi)->m_viewport.maxDepth = 1.0f;

        m_render_camera->setAspect(width / height);
	}

    //***********************************交换数据*******************************************//

	void RenderSystem::processSwapData() {
		SwapData& swap_data = m_swap_context.getRenderSwapData();//获取交换数据

		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;

        //更新场景资源
        if (swap_data.m_level_resource_desc.has_value())
        {
            LOG_INFO("正在更新场景资源");
            m_render_resource->uploadGlobalRenderResource(m_rhi, swap_data.m_level_resource_desc.value());//更新
            m_swap_context.resetLevelResourceSwapData();//清空
        }

        //更新GO
        if (swap_data.m_game_object_resource_desc.has_value())
        {
            while (!swap_data.m_game_object_resource_desc->isEmpty())
            {
                GameObjectDesc gobject = swap_data.m_game_object_resource_desc->getNextProcessObject();//获取要处理的物体
                for (size_t part_index = 0; part_index < gobject.getObjectParts().size(); part_index++)
                {
                    const auto& game_object_part = gobject.getObjectParts()[part_index];//获取part
                    GameObjectPartId part_id = { gobject.getId(), part_index };//获取partId

                    bool is_entity_in_scene = m_render_scene->getInstanceIdAllocator().hasElement(part_id);//场景中是否有该实体
                    //创建实体
                    RenderEntity render_entity;
                    render_entity.m_instance_id = static_cast<uint32_t>(m_render_scene->getInstanceIdAllocator().allocGuid(part_id));
                    render_entity.m_model_matrix = game_object_part.m_transform_desc.m_transform_matrix;
                    //把实例id放入map
                    m_render_scene->addInstanceIdToMap(render_entity.m_instance_id, gobject.getId());

                    //网格资源：包围盒
                    MeshSourceDesc mesh_source = { game_object_part.m_mesh_desc.m_mesh_file };
                    bool is_mesh_loaded = m_render_scene->getMeshAssetIdAllocator().hasElement(mesh_source);//查看网格是否被加载

                    RenderMeshData mesh_data;
                    if (!is_mesh_loaded){
                        mesh_data = m_render_resource->loadMeshData(mesh_source, render_entity.m_bounding_box);//读网格数据
                    }
                    else{
                        render_entity.m_bounding_box = m_render_resource->getCachedBoudingBox(mesh_source);//直接从缓存获取
                    }
                    render_entity.m_mesh_asset_id = m_render_scene->getMeshAssetIdAllocator().allocGuid(mesh_source);//分配id
                    

                    //材质
                    MaterialSourceDesc material_source;
                    if (game_object_part.m_material_desc.m_with_texture)//如果自带纹理
                    {
                        material_source = { game_object_part.m_material_desc.m_base_color_texture_file,
                                           game_object_part.m_material_desc.m_metallic_roughness_texture_file,
                                           game_object_part.m_material_desc.m_normal_texture_file,
                                           game_object_part.m_material_desc.m_occlusion_texture_file,
                                           game_object_part.m_material_desc.m_emissive_texture_file };
                    }
                    else
                    {
                        material_source = {asset_manager->getFullPath("asset/texture/default/albedo.jpg").generic_string(),asset_manager->getFullPath("asset/texture/default/mr.jpg").generic_string(),asset_manager->getFullPath("asset/texture/default/normal.jpg").generic_string(),"","" };
                    }
                    bool is_material_loaded = m_render_scene->getMaterialAssetdAllocator().hasElement(material_source);//是否材质已经加载

                    RenderMaterialData material_data;
                    if (!is_material_loaded)
                    {
                        material_data = m_render_resource->loadMaterialData(material_source);//加载材质数据
                    }
                    render_entity.m_material_asset_id = m_render_scene->getMaterialAssetdAllocator().allocGuid(material_source);//分配材质id

                    //
                    if (!is_mesh_loaded)
                    {
                        m_render_resource->uploadGameObjectRenderResource(m_rhi, render_entity, mesh_data);
                    }
                    if (!is_material_loaded)
                    {
                        m_render_resource->uploadGameObjectRenderResource(m_rhi, render_entity, material_data);
                    }
                    if (!is_entity_in_scene)
                    {
                        m_render_scene->m_render_entities.push_back(render_entity);
                    }
                    else
                    {
                        for (auto& entity : m_render_scene->m_render_entities)
                        {
                            if (entity.m_instance_id == render_entity.m_instance_id)
                            {
                                entity = render_entity;
                                break;
                            }
                        }
                    }
                }
                // after finished processing, pop this game object
                swap_data.m_game_object_resource_desc->pop();
            }
            m_swap_context.resetGameObjectResourceSwapData();
        }

        //删除要清理的物体的id
        if (swap_data.m_game_object_to_delete.has_value())
        {
            while (!swap_data.m_game_object_to_delete->isEmpty())
            {
                GameObjectDesc gobject = swap_data.m_game_object_to_delete->getNextProcessObject();
                m_render_scene->deleteEntityByGObjectID(gobject.getId());
                swap_data.m_game_object_to_delete->pop();
            }

            m_swap_context.resetGameObjectToDelete();
        }

        //处理相机交换数据：进行信息设置
        if (swap_data.m_camera_swap_data.has_value())
        {
            if (swap_data.m_camera_swap_data->m_fov_x.has_value())
            {
                m_render_camera->setFOVx(*swap_data.m_camera_swap_data->m_fov_x);
            }

            if (swap_data.m_camera_swap_data->m_view_matrix.has_value())
            {
                m_render_camera->setMainViewMatrix(*swap_data.m_camera_swap_data->m_view_matrix);
            }

            if (swap_data.m_camera_swap_data->m_camera_type.has_value())
            {
                m_render_camera->setCurrentCameraType(*swap_data.m_camera_swap_data->m_camera_type);
            }

            m_swap_context.resetCameraSwapData();
        }
	}


	//***********************************清理数据*******************************************//
	void RenderSystem::clear() {
		if (m_rhi) {
			m_rhi->clear();
		}
		m_rhi.reset();

		if (m_render_scene)
		{
			m_render_scene->clear();
		}
		m_render_scene.reset();

		if (m_render_resource) {
			m_render_resource->clear();
		}
		m_render_resource.reset();

		if (m_render_pipeline) {
			m_render_pipeline->clear();
		}
		m_render_pipeline.reset();
	}
}