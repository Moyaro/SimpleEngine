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
		void init();//��ȡrhi����װ���й���
		void setupPipelines();//�������ߣ����仺�壬����������Դ
		void preparePassData(std::shared_ptr<RenderResourceBase> render_resource);//��ȡͶӰ��ͼ����

		~DebugDrawManager() { destroy(); }
		void destroy();//���ٹ��ߣ����������������
		void clear();////ɾ������ͼ����
		void tick(float delta_time);//����Ƿ�����Ҫɾ��������ͻ�����

		void draw(uint32_t current_swapchain_image_index);//��ȡ�������ݡ���̬�����ӿڡ��ü�����ʼ����
		
		DebugDrawGroup* tryGetOrCreateDebugDrawGroup(const std::string& name);//��ȡ�򴴽���

		void updateAfterRecreateSwapchain();//�ؽ������������ÿ��debug����

	private:
		void swapDataToRender();//��ȡ��ǰҪ���Ƶ�����
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

		//��¼������ʱ�����С��ƫ����
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

