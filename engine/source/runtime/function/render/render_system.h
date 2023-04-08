#pragma once

#include "render_swap_context.h"
#include "runtime/function/render/render_entity.h"
#include "runtime/function/render/render_guid_allocator.h"
#include "runtime/function/render/render_swap_context.h"
#include "runtime/function/render/render_pipeline_base.h"
#include "runtime/function/render/render_pipeline.h"
#include "runtime/function/render/render_scene.h"
#include "render_type.h"
#include <memory>
#include <optional>
#include <array>

namespace SimpleEngine {
	class WindowSystem;
	class RHI;
	class DebugDrawManager;
	class RenderScene;
	class RenderCamera;
	class RenderResourceBase;
	class RenderPipelineBase;
	class WindowUI;

	//渲染系统初始化信息
	struct RenderSystemInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	//视口内容
	struct EngineContentViewport
	{
		float offset_x{ 0.f };
		float offset_y{ 0.f };
		float width{ 0.f };
		float height{ 0.f };
	};

	class RenderSystem
	{
	public:
		RenderSystem() = default;
		~RenderSystem() { clear(); }
		void clear();//清理指针
		void clearForLevelReloading(){ m_render_scene->clearForLevelReloading(); }

		void init(RenderSystemInitInfo init_info);//初始化rhi、resource、pipeline
		void tick(float delta_time);//渲染
		

		//交换逻辑渲染的数据
		void swapLogicRenderData() { m_swap_context.swapLogicRenderData(); }//交换
		RenderSwapContext& getSwapContext() { return m_swap_context; }

		std::shared_ptr<RHI> getRHI() { return m_rhi; }
		std::shared_ptr<RenderCamera> getRenderCamera() const { return m_render_camera; }

		uint32_t  getGuidOfPickedMesh(const Vector2& picked_uv){ return m_render_pipeline->getGuidOfPickedMesh(picked_uv); }
		GObjectID getGObjectIDByMeshID(uint32_t mesh_id) const{ return m_render_scene->getGObjectIDByMeshID(mesh_id); }

		//视口
		EngineContentViewport getEngineContentViewport() const;
		void updateEngineContentViewport(float offset_x, float offset_y, float width, float height);

		void initializeUIRenderBackend(WindowUI* window_ui){ m_render_pipeline->initializeUIRenderBackend(window_ui); }
		void setRenderPipelineType(RENDER_PIPELINE_TYPE pipeline_type) { m_render_pipeline_type = pipeline_type; }//选择前置渲染/延迟渲染

		//轴
		void createAxis(std::array<RenderEntity, 3> axis_entities, std::array<RenderMeshData, 3> mesh_datas);
		void setVisibleAxis(std::optional<RenderEntity> axis);
		void setSelectedAxis(size_t selected_axis);

		//id分配器
		GuidAllocator<GameObjectPartId>& getGOInstanceIdAllocator(){ return m_render_scene->getInstanceIdAllocator(); }
		GuidAllocator<MeshSourceDesc>& getMeshAssetIdAllocator(){ return m_render_scene->getMeshAssetIdAllocator(); }
	private:
		RENDER_PIPELINE_TYPE m_render_pipeline_type{ RENDER_PIPELINE_TYPE::FORWARD_PIPELINE };//渲染方式
		RenderSwapContext m_swap_context;//交换数据的上下文

		std::shared_ptr<RHI> m_rhi;
		std::shared_ptr<RenderResourceBase> m_render_resource;
		std::shared_ptr<RenderPipelineBase> m_render_pipeline;
		std::shared_ptr<RenderCamera>       m_render_camera;
		std::shared_ptr<RenderScene>        m_render_scene;

		void processSwapData();//处理交换数据
	};
}