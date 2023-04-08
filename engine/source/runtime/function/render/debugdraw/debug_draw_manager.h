#pragma once
#include <memory>
#include "debug_draw_pipeline.h"
#include "debug_draw_group.h"
#include "debug_draw_context.h"
#include "debug_draw_buffer.h"
#include "debug_draw_font.h"
#include "runtime/function/render/render_resource_base.h"
#include "runtime/function/render/render_resource.h"

namespace SimpleEngine {
	class DebugDrawManager
	{
	public:
		void init();//获取rhi，安装所有管线
		void setupPipelines();//开启管线，分配缓冲，加载字体资源
		void preparePassData(std::shared_ptr<RenderResourceBase> render_resource);//获取投影视图矩阵

		~DebugDrawManager() { destroy(); }
		void destroy();//销毁管线，缓冲分配器，字体
		void clear();////删除所有图形组
		void tick(float delta_time);//检查是否有需要删除的物体和缓冲区

		void draw(uint32_t current_swapchain_image_index);//获取绘制内容、动态设置视口、裁剪，开始绘制
		
		DebugDrawGroup* tryGetOrCreateDebugDrawGroup(const std::string& name);//获取或创建组

		void updateAfterRecreateSwapchain();//重建交换链后更新每个debug管线

	private:
		void swapDataToRender();//获取当前要绘制的内容
		void drawDebugObject(uint32_t current_swapchain_image_index);
		void prepareDrawBuffer();
		void drawPointLineTriangleBox(uint32_t current_swapchain_image_index);
		void drawWireFrameObject(uint32_t current_swapchain_image_index);

		std::shared_ptr<RHI> m_rhi;
		std::mutex m_mutex;
		DebugDrawPipeline* m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_count];
		DebugDrawAllocator* m_buffer_allocator = nullptr;
		DebugDrawContext m_debug_draw_context;
		DebugDrawGroup m_debug_draw_group_for_render;
		DebugDrawFont* m_font = nullptr;

		Matrix4x4 m_proj_view_matrix;

		//记录进缓存时缓存大小的偏移量
		size_t m_point_start_offset;
		size_t m_point_end_offset;
		size_t m_line_start_offset;
		size_t m_line_end_offset;
		size_t m_triangle_start_offset;
		size_t m_triangle_end_offset;
		size_t m_no_depth_test_point_start_offset;
		size_t m_no_depth_test_point_end_offset;
		size_t m_no_depth_test_line_start_offset;
		size_t m_no_depth_test_line_end_offset;
		size_t m_no_depth_test_triangle_start_offset;
		size_t m_no_depth_test_triangle_end_offset;
		size_t m_text_start_offset;
		size_t m_text_end_offset;
	};
}

