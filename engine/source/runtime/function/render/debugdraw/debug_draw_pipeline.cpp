#include "debug_draw_pipeline.h"
#include "../interface/rhi.h"
#include "../interface/rhi_struct.h"
#include "../../global/global_context.h"
#include "../../../../../shader/generated/cpp/debug_draw_vert.h"
#include "../../../../../shader/generated/cpp/debug_draw_frag.h"
#include "runtime/function/render/render_system.h"
#include "../interface/vulkan_rhi.h"
#include "debug_draw_primitive.h"

#include <array>

namespace SimpleEngine {
	void DebugDrawPipeline::init() {
		m_rhi = g_runtime_global_context.m_render_system->getRHI();
		setupRenderPass();
		setupFramebuffer();
		setupDescriptorLayout();
		setupPipeline();
	}

	void DebugDrawPipeline::destroy() {
		/*m_rhi->destroyPipeline(m_pipeline.pipeline);
		m_rhi->destroyPipelineLayout(m_pipeline.layout);
		m_rhi->destroyRenderPass(m_framebuffer.render_pass);*/
	}

	void DebugDrawPipeline::recreateAfterSwapchain()
	{
		for (auto framebuffer : m_framebuffer.framebuffers)
		{
			m_rhi->destroyFramebuffer(framebuffer);
		}
		setupFramebuffer();
	}

	
	void DebugDrawPipeline::setupRenderPass() {
		//颜色缓冲附件
		VkAttachmentDescription color_attanchment_description = {};
		color_attanchment_description.format = m_rhi->getSwapchainInfo().image_format;//颜色附着格式
		color_attanchment_description.samples = VK_SAMPLE_COUNT_1_BIT;//采样数
		//对颜色、深度缓冲起效
		color_attanchment_description.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;//渲染前对附着中数据的操作
		color_attanchment_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//渲染后对附着中数据的操作
		//对模板缓冲起效
		color_attanchment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		color_attanchment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//图像内存布局
		color_attanchment_description.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		color_attanchment_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;//渲染通道结束后图像可用交换链呈现

		//附着引用信息
		VkAttachmentReference color_attachment_ref = {};
		color_attachment_ref.attachment = 0;//附着描述结构体数组中的索引
		color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//子流程开始时转换附件的布局

		//深度缓冲附件
		VkAttachmentDescription depth_attachment_description{};
		depth_attachment_description.format = m_rhi->getDepthImageInfo().depth_image_format;
		depth_attachment_description.samples = VK_SAMPLE_COUNT_1_BIT;
		depth_attachment_description.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		depth_attachment_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		depth_attachment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depth_attachment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depth_attachment_description.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		depth_attachment_description.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depth_attachment_ref{};
		depth_attachment_ref.attachment = 1;
		depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		//子流程：引用附着
		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//图像渲染子流程
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment_ref;
		subpass.pDepthStencilAttachment = &depth_attachment_ref;

		std::array<VkAttachmentDescription, 2> attachments = { color_attanchment_description, depth_attachment_description };

		//子流程间依赖关系：控制图像视图变换，让变换在必要时才进行
		VkSubpassDependency debug_draw_dependency;
		debug_draw_dependency.srcSubpass = 0;//被依赖的子流程索引
		debug_draw_dependency.dstSubpass = VK_SUBPASS_EXTERNAL;//依赖被依赖的子流程索引：渲染流程结束后的子流程索引
		debug_draw_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;//需要等待的管线阶段
		debug_draw_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		debug_draw_dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT; //子流程进行的操作类型
		debug_draw_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		debug_draw_dependency.dependencyFlags = 0; 

		//创建渲染流程
		VkRenderPassCreateInfo render_pass_info = {};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		render_pass_info.attachmentCount = static_cast<uint32_t>(attachments.size());
		render_pass_info.pAttachments = attachments.data();
		render_pass_info.subpassCount = 1;
		render_pass_info.pSubpasses = &subpass;
		render_pass_info.dependencyCount = 1;
		render_pass_info.pDependencies = &debug_draw_dependency;

		if (m_rhi->createRenderPass(&render_pass_info, &m_framebuffer.render_pass) != VK_SUCCESS) {
			throw std::runtime_error("创建渲染流程失败！");
		}
	}

	void DebugDrawPipeline::setupPipeline() {
		VkShaderModule vert_shader_module = m_rhi->createShaderModule(DEBUG_DRAW_VERT);
		VkShaderModule frag_shader_module = m_rhi->createShaderModule(DEBUG_DRAW_FRAG);

		//设置着色器阶段：指定着色器在管线哪一阶段使用
		VkPipelineShaderStageCreateInfo vert_shader_stage_create_info = {};
		vert_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vert_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;//可选任意可编程阶段
		vert_shader_stage_create_info.module = vert_shader_module;
		vert_shader_stage_create_info.pName = "main";//着色器函数

		VkPipelineShaderStageCreateInfo frag_shader_stage_create_info = {};
		frag_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		frag_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		frag_shader_stage_create_info.module = frag_shader_module;
		frag_shader_stage_create_info.pName = "main";

		VkPipelineShaderStageCreateInfo shader_stages[] = { vert_shader_stage_create_info,frag_shader_stage_create_info };

		//设置顶点输入:设置顶点绑定、属性信息
		auto vertex_binding_descriptions = DebugDrawVertex::getBindingDescriptions();
		auto vertex_attribute_descriptions = DebugDrawVertex::getAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(vertex_binding_descriptions.size());//确定数据是每个顶点或者是每个instance
		vertex_input_info.pVertexBindingDescriptions = vertex_binding_descriptions.data();
		vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertex_attribute_descriptions.size());//属性信息
		vertex_input_info.pVertexAttributeDescriptions = vertex_attribute_descriptions.data();

		//设置输入装配：几何图元类型
		VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
		input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly.primitiveRestartEnable = VK_FALSE;//STRIP模式用

		//设置视口：描述输出渲染结果的帧缓冲区域，图像到帧缓冲的映射，裁剪矩形：哪些像素存在帧缓冲
		SwapChainDesc desc = m_rhi->getSwapchainInfo();
		VkPipelineViewportStateCreateInfo viewport_state = {};
		viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state.viewportCount = 1;
		viewport_state.pViewports = desc.viewport;
		viewport_state.scissorCount = 1;
		viewport_state.pScissors = desc.scissor;

		//设置光栅化：将几何图元变成片段，开启测试
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;//用于生成阴影贴图
		rasterizer.rasterizerDiscardEnable = VK_FALSE;//是否禁止所有几何图元通过光栅化阶段
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;//生成片段的方式
		rasterizer.lineWidth = 1.0;//线宽
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;//表面剔除类型
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;//正面：顺时针顶点序
		rasterizer.depthBiasClamp = VK_FALSE;//是否改变深度值
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		//设置多重采样：组合不同多边形产生的片段颜色决定最终像素颜色
		VkPipelineMultisampleStateCreateInfo mutismapling = {};
		mutismapling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		mutismapling.sampleShadingEnable = VK_FALSE;
		mutismapling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		//设置颜色混合:片段颜色和原帧缓冲像素颜色混合
		//实现半透明效果
		VkPipelineColorBlendAttachmentState color_blend_attachment = {};
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;//哪些颜色通道可写入帧缓冲
		color_blend_attachment.blendEnable = VK_FALSE;//VK_TRUE
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		//设置全局混合常量
		VkPipelineColorBlendStateCreateInfo color_blending = {};
		color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blending.logicOpEnable = VK_FALSE;
		color_blending.attachmentCount = 1;
		color_blending.pAttachments = &color_blend_attachment;

		//设置深度测试
		VkPipelineDepthStencilStateCreateInfo depth_stencil_create_info{};
		depth_stencil_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_stencil_create_info.depthTestEnable = VK_TRUE;
		depth_stencil_create_info.depthWriteEnable = VK_TRUE;//片段通过测试后是否写入深度值
		depth_stencil_create_info.depthCompareOp = VK_COMPARE_OP_LESS;//小于比较运算：小于深度缓冲的深度值写入颜色附着
		depth_stencil_create_info.depthBoundsTestEnable = VK_FALSE;//深度范围测试
		depth_stencil_create_info.stencilTestEnable = VK_FALSE;//模板测试

		//设置需要动态修改的状态
		VkDynamicState dynamic_states[] = { VK_DYNAMIC_STATE_SCISSOR,VK_DYNAMIC_STATE_VIEWPORT };
		VkPipelineDynamicStateCreateInfo dynamic_state = {};
		dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state.dynamicStateCount = 2;
		dynamic_state.pDynamicStates = dynamic_states;

		//创建管线布局:设置着色器的uniform变量
		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 1;
		pipeline_layout_info.pSetLayouts = &m_descriptor_layout;

		if (m_rhi->createPipelineLayout(&pipeline_layout_info, &m_pipeline.layout) != VK_SUCCESS) {
			throw std::runtime_error("创建管线布局失败！");
		}

		//创建管线对象
		VkGraphicsPipelineCreateInfo pipeline_info = {};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.stageCount = 2;
		pipeline_info.pStages = shader_stages;
		pipeline_info.pVertexInputState = &vertex_input_info;
		pipeline_info.pInputAssemblyState = &input_assembly;
		pipeline_info.pViewportState = &viewport_state;
		pipeline_info.pRasterizationState = &rasterizer;
		pipeline_info.pMultisampleState = &mutismapling;
		pipeline_info.pDepthStencilState = &depth_stencil_create_info;
		pipeline_info.pColorBlendState = &color_blending;
		pipeline_info.pDynamicState = &dynamic_state;
		pipeline_info.layout = m_pipeline.layout;
		pipeline_info.renderPass = m_framebuffer.render_pass;
		pipeline_info.subpass = 0;//子流程索引
		pipeline_info.basePipelineHandle = VK_NULL_HANDLE;//通过已经存在的管线创建新的图形管线

		//根据管线类型选择几何图元类型
		if (m_pipeline_type == _debug_draw_pipeline_type_point)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		}
		else if (m_pipeline_type == _debug_draw_pipeline_type_line)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		}
		else if (m_pipeline_type == _debug_draw_pipeline_type_triangle)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		}
		else if (m_pipeline_type == _debug_draw_pipeline_type_point_no_depth_test)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			depth_stencil_create_info.depthTestEnable = VK_FALSE;
		}
		else if (m_pipeline_type == _debug_draw_pipeline_type_line_no_depth_test)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			depth_stencil_create_info.depthTestEnable = VK_FALSE;
		}
		else if (m_pipeline_type == _debug_draw_pipeline_type_triangle_no_depth_test)
		{
			input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			depth_stencil_create_info.depthTestEnable = VK_FALSE;
		}

		if (m_rhi->createGraphicsPipelines(VK_NULL_HANDLE, 1, &pipeline_info, &m_pipeline.pipeline) != VK_SUCCESS)
		{
			throw std::runtime_error("创建管线失败！");
		}

		//清理着色器模块
		m_rhi->destroyShaderModule(vert_shader_module);
		m_rhi->destroyShaderModule(frag_shader_module);
	}

	void DebugDrawPipeline::setupFramebuffer() {
		std::vector<VkImageView> imageViews = m_rhi->getSwapchainInfo().imageViews;
		m_framebuffer.framebuffers.resize(imageViews.size());

		for (size_t i = 0; i < imageViews.size(); i++) {
			
			//每个图像创建一帧缓冲
			std::vector<VkImageView> attachments = { imageViews[i], m_rhi->getDepthImageInfo().depth_image_view };

			VkFramebufferCreateInfo framebuffer_info = {};
			framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebuffer_info.renderPass = m_framebuffer.render_pass;
			framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebuffer_info.pAttachments = attachments.data();
			framebuffer_info.width = m_rhi->getSwapchainInfo().extent.width;
			framebuffer_info.height = m_rhi->getSwapchainInfo().extent.height;
			framebuffer_info.layers = 1;

			if (m_rhi->createFramebuffer(&framebuffer_info, &m_framebuffer.framebuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("创建帧缓冲失败！");
			}
		}
	}

	void DebugDrawPipeline::setupDescriptorLayout() {
		//描述符绑定信息
		VkDescriptorSetLayoutBinding uboLayoutBinding[3];
		uboLayoutBinding[0].binding = 0;//描述符绑定
		uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;//描述符类型
		uboLayoutBinding[0].descriptorCount = 1;
		uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;//指定使用阶段
		uboLayoutBinding[0].pImmutableSamplers = nullptr;//用于与图像采集相关的描述符

		uboLayoutBinding[1].binding = 1;
		uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
		uboLayoutBinding[1].descriptorCount = 1;
		uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding[1].pImmutableSamplers = nullptr;

		uboLayoutBinding[2].binding = 2;
		uboLayoutBinding[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		uboLayoutBinding[2].descriptorCount = 1;
		uboLayoutBinding[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		uboLayoutBinding[2].pImmutableSamplers = nullptr;

		//描述集布局信息
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 3;
		layoutInfo.pBindings = uboLayoutBinding;

		if (m_rhi->createDescriptorSetLayout(&layoutInfo, &m_descriptor_layout) != VK_SUCCESS){
			throw std::runtime_error("创建描述符布局失败！");
		}
	}
}