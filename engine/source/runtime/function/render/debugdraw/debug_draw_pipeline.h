#pragma once
#include "../interface/rhi.h"
#include <stdexcept>
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>

namespace SimpleEngine {

	//��������
	enum DebugDrawPipelineType : uint8_t {
		_debug_draw_pipeline_type_point = 0,
		_debug_draw_pipeline_type_line,
		_debug_draw_pipeline_type_triangle,
		_debug_draw_pipeline_type_point_no_depth_test,
		_debug_draw_pipeline_type_line_no_depth_test,
		_debug_draw_pipeline_type_triangle_no_depth_test,
		_debug_draw_pipeline_type_count
	};

	//���߻���������+����
	struct DebugDrawPipelineBase
	{
		VkPipelineLayout layout;
		VkPipeline pipeline;
	};

	//֡���帽��
	struct DebugDrawFrameBufferAttachment
	{
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
		VkFormat format;
	};

	//֡���壺��ߣ���Ⱦͨ����֡�������飬��������
	struct DebugDrawFrameBuffer {
		int width;
		int height;
		VkRenderPass render_pass;
		std::vector<VkFramebuffer> framebuffers;
		std::vector<DebugDrawFrameBufferAttachment> attachments;
	};

	class DebugDrawPipeline
	{
	public:
		DebugDrawPipeline(DebugDrawPipelineType pipeline_type):m_pipeline_type(pipeline_type){}
		void init();
		void destroy();//û����
		const DebugDrawPipelineBase& getPipeline() const { return m_pipeline; }
		const DebugDrawFrameBuffer& getFramebuffer() const { return m_framebuffer; }

		DebugDrawPipelineType m_pipeline_type;

		void recreateAfterSwapchain();//�ؽ�����������Ҫ�ؽ�֡����

	private:
		void setupPipeline();
		void setupRenderPass();
		void setupFramebuffer();
		void setupDescriptorLayout();
		DebugDrawPipelineBase m_pipeline;
		DebugDrawFrameBuffer m_framebuffer;
		std::shared_ptr<RHI> m_rhi;
		
		VkDescriptorSetLayout m_descriptor_layout;

	};
}