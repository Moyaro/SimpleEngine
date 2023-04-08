#pragma once
#include "../interface/rhi.h"
#include <stdexcept>
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>

namespace SimpleEngine {

	//管线类型
	enum DebugDrawPipelineType : uint8_t {
		_debug_draw_pipeline_type_point = 0,
		_debug_draw_pipeline_type_line,
		_debug_draw_pipeline_type_triangle,
		_debug_draw_pipeline_type_point_no_depth_test,
		_debug_draw_pipeline_type_line_no_depth_test,
		_debug_draw_pipeline_type_triangle_no_depth_test,
		_debug_draw_pipeline_type_count
	};

	//管线基础：布局+管线
	struct DebugDrawPipelineBase
	{
		VkPipelineLayout layout;
		VkPipeline pipeline;
	};

	//帧缓冲附着
	struct DebugDrawFrameBufferAttachment
	{
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
		VkFormat format;
	};

	//帧缓冲：宽高，渲染通道，帧缓冲数组，附着数组
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
		void destroy();//没内容
		const DebugDrawPipelineBase& getPipeline() const { return m_pipeline; }
		const DebugDrawFrameBuffer& getFramebuffer() const { return m_framebuffer; }

		DebugDrawPipelineType m_pipeline_type;

		void recreateAfterSwapchain();//重建交换链后，需要重建帧缓冲

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