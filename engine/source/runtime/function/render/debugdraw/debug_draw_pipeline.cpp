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
		//��ɫ���帽��
		VkAttachmentDescription color_attanchment_description = {};
		color_attanchment_description.format = m_rhi->getSwapchainInfo().image_format;//��ɫ���Ÿ�ʽ
		color_attanchment_description.samples = VK_SAMPLE_COUNT_1_BIT;//������
		//����ɫ����Ȼ�����Ч
		color_attanchment_description.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;//��Ⱦǰ�Ը��������ݵĲ���
		color_attanchment_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//��Ⱦ��Ը��������ݵĲ���
		//��ģ�建����Ч
		color_attanchment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		color_attanchment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//ͼ���ڴ沼��
		color_attanchment_description.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		color_attanchment_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;//��Ⱦͨ��������ͼ����ý���������

		//����������Ϣ
		VkAttachmentReference color_attachment_ref = {};
		color_attachment_ref.attachment = 0;//���������ṹ�������е�����
		color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//�����̿�ʼʱת�������Ĳ���

		//��Ȼ��帽��
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

		//�����̣����ø���
		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//ͼ����Ⱦ������
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment_ref;
		subpass.pDepthStencilAttachment = &depth_attachment_ref;

		std::array<VkAttachmentDescription, 2> attachments = { color_attanchment_description, depth_attachment_description };

		//�����̼�������ϵ������ͼ����ͼ�任���ñ任�ڱ�Ҫʱ�Ž���
		VkSubpassDependency debug_draw_dependency;
		debug_draw_dependency.srcSubpass = 0;//������������������
		debug_draw_dependency.dstSubpass = VK_SUBPASS_EXTERNAL;//��������������������������Ⱦ���̽����������������
		debug_draw_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;//��Ҫ�ȴ��Ĺ��߽׶�
		debug_draw_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		debug_draw_dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT; //�����̽��еĲ�������
		debug_draw_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		debug_draw_dependency.dependencyFlags = 0; 

		//������Ⱦ����
		VkRenderPassCreateInfo render_pass_info = {};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		render_pass_info.attachmentCount = static_cast<uint32_t>(attachments.size());
		render_pass_info.pAttachments = attachments.data();
		render_pass_info.subpassCount = 1;
		render_pass_info.pSubpasses = &subpass;
		render_pass_info.dependencyCount = 1;
		render_pass_info.pDependencies = &debug_draw_dependency;

		if (m_rhi->createRenderPass(&render_pass_info, &m_framebuffer.render_pass) != VK_SUCCESS) {
			throw std::runtime_error("������Ⱦ����ʧ�ܣ�");
		}
	}

	void DebugDrawPipeline::setupPipeline() {
		VkShaderModule vert_shader_module = m_rhi->createShaderModule(DEBUG_DRAW_VERT);
		VkShaderModule frag_shader_module = m_rhi->createShaderModule(DEBUG_DRAW_FRAG);

		//������ɫ���׶Σ�ָ����ɫ���ڹ�����һ�׶�ʹ��
		VkPipelineShaderStageCreateInfo vert_shader_stage_create_info = {};
		vert_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vert_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;//��ѡ����ɱ�̽׶�
		vert_shader_stage_create_info.module = vert_shader_module;
		vert_shader_stage_create_info.pName = "main";//��ɫ������

		VkPipelineShaderStageCreateInfo frag_shader_stage_create_info = {};
		frag_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		frag_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		frag_shader_stage_create_info.module = frag_shader_module;
		frag_shader_stage_create_info.pName = "main";

		VkPipelineShaderStageCreateInfo shader_stages[] = { vert_shader_stage_create_info,frag_shader_stage_create_info };

		//���ö�������:���ö���󶨡�������Ϣ
		auto vertex_binding_descriptions = DebugDrawVertex::getBindingDescriptions();
		auto vertex_attribute_descriptions = DebugDrawVertex::getAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(vertex_binding_descriptions.size());//ȷ��������ÿ�����������ÿ��instance
		vertex_input_info.pVertexBindingDescriptions = vertex_binding_descriptions.data();
		vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertex_attribute_descriptions.size());//������Ϣ
		vertex_input_info.pVertexAttributeDescriptions = vertex_attribute_descriptions.data();

		//��������װ�䣺����ͼԪ����
		VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
		input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly.primitiveRestartEnable = VK_FALSE;//STRIPģʽ��

		//�����ӿڣ����������Ⱦ�����֡��������ͼ��֡�����ӳ�䣬�ü����Σ���Щ���ش���֡����
		SwapChainDesc desc = m_rhi->getSwapchainInfo();
		VkPipelineViewportStateCreateInfo viewport_state = {};
		viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state.viewportCount = 1;
		viewport_state.pViewports = desc.viewport;
		viewport_state.scissorCount = 1;
		viewport_state.pScissors = desc.scissor;

		//���ù�դ����������ͼԪ���Ƭ�Σ���������
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;//����������Ӱ��ͼ
		rasterizer.rasterizerDiscardEnable = VK_FALSE;//�Ƿ��ֹ���м���ͼԪͨ����դ���׶�
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;//����Ƭ�εķ�ʽ
		rasterizer.lineWidth = 1.0;//�߿�
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;//�����޳�����
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;//���棺˳ʱ�붥����
		rasterizer.depthBiasClamp = VK_FALSE;//�Ƿ�ı����ֵ
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		//���ö��ز�������ϲ�ͬ����β�����Ƭ����ɫ��������������ɫ
		VkPipelineMultisampleStateCreateInfo mutismapling = {};
		mutismapling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		mutismapling.sampleShadingEnable = VK_FALSE;
		mutismapling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		//������ɫ���:Ƭ����ɫ��ԭ֡����������ɫ���
		//ʵ�ְ�͸��Ч��
		VkPipelineColorBlendAttachmentState color_blend_attachment = {};
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;//��Щ��ɫͨ����д��֡����
		color_blend_attachment.blendEnable = VK_FALSE;//VK_TRUE
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		//����ȫ�ֻ�ϳ���
		VkPipelineColorBlendStateCreateInfo color_blending = {};
		color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blending.logicOpEnable = VK_FALSE;
		color_blending.attachmentCount = 1;
		color_blending.pAttachments = &color_blend_attachment;

		//������Ȳ���
		VkPipelineDepthStencilStateCreateInfo depth_stencil_create_info{};
		depth_stencil_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_stencil_create_info.depthTestEnable = VK_TRUE;
		depth_stencil_create_info.depthWriteEnable = VK_TRUE;//Ƭ��ͨ�����Ժ��Ƿ�д�����ֵ
		depth_stencil_create_info.depthCompareOp = VK_COMPARE_OP_LESS;//С�ڱȽ����㣺С����Ȼ�������ֵд����ɫ����
		depth_stencil_create_info.depthBoundsTestEnable = VK_FALSE;//��ȷ�Χ����
		depth_stencil_create_info.stencilTestEnable = VK_FALSE;//ģ�����

		//������Ҫ��̬�޸ĵ�״̬
		VkDynamicState dynamic_states[] = { VK_DYNAMIC_STATE_SCISSOR,VK_DYNAMIC_STATE_VIEWPORT };
		VkPipelineDynamicStateCreateInfo dynamic_state = {};
		dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state.dynamicStateCount = 2;
		dynamic_state.pDynamicStates = dynamic_states;

		//�������߲���:������ɫ����uniform����
		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 1;
		pipeline_layout_info.pSetLayouts = &m_descriptor_layout;

		if (m_rhi->createPipelineLayout(&pipeline_layout_info, &m_pipeline.layout) != VK_SUCCESS) {
			throw std::runtime_error("�������߲���ʧ�ܣ�");
		}

		//�������߶���
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
		pipeline_info.subpass = 0;//����������
		pipeline_info.basePipelineHandle = VK_NULL_HANDLE;//ͨ���Ѿ����ڵĹ��ߴ����µ�ͼ�ι���

		//���ݹ�������ѡ�񼸺�ͼԪ����
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
			throw std::runtime_error("��������ʧ�ܣ�");
		}

		//������ɫ��ģ��
		m_rhi->destroyShaderModule(vert_shader_module);
		m_rhi->destroyShaderModule(frag_shader_module);
	}

	void DebugDrawPipeline::setupFramebuffer() {
		std::vector<VkImageView> imageViews = m_rhi->getSwapchainInfo().imageViews;
		m_framebuffer.framebuffers.resize(imageViews.size());

		for (size_t i = 0; i < imageViews.size(); i++) {
			
			//ÿ��ͼ�񴴽�һ֡����
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
				throw std::runtime_error("����֡����ʧ�ܣ�");
			}
		}
	}

	void DebugDrawPipeline::setupDescriptorLayout() {
		//����������Ϣ
		VkDescriptorSetLayoutBinding uboLayoutBinding[3];
		uboLayoutBinding[0].binding = 0;//��������
		uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;//����������
		uboLayoutBinding[0].descriptorCount = 1;
		uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;//ָ��ʹ�ý׶�
		uboLayoutBinding[0].pImmutableSamplers = nullptr;//������ͼ��ɼ���ص�������

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

		//������������Ϣ
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 3;
		layoutInfo.pBindings = uboLayoutBinding;

		if (m_rhi->createDescriptorSetLayout(&layoutInfo, &m_descriptor_layout) != VK_SUCCESS){
			throw std::runtime_error("��������������ʧ�ܣ�");
		}
	}
}