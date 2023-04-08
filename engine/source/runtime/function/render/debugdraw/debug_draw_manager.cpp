#include "debug_draw_manager.h"
#include "../../global/global_context.h"
#include "runtime/function/render/render_system.h"
#include <iostream>

namespace SimpleEngine {
	//获取rhi，开启管线
	void DebugDrawManager::init() {
		m_rhi = g_runtime_global_context.m_render_system->getRHI();
		setupPipelines();
	}

	//开启所有管线，分配缓冲
	void DebugDrawManager::setupPipelines() {
		for (uint8_t i = 0; i < DebugDrawPipelineType::_debug_draw_pipeline_type_count; i++) {
			m_debug_draw_pipeline[i] = new DebugDrawPipeline((DebugDrawPipelineType)i);
			m_debug_draw_pipeline[i]->init();
		}
		m_buffer_allocator = new DebugDrawAllocator();
		m_font = new DebugDrawFont();
		m_font->init();
		m_buffer_allocator->init(m_font);
	}
	
	//***********************************绘制*******************************************//
	void DebugDrawManager::draw(uint32_t current_swapchain_image_index){
		swapDataToRender();//获取当前要绘制的内容

		//设置视口、裁剪
		SwapChainDesc desc = m_rhi->getSwapchainInfo();
		m_rhi->cmdSetViewport(0, 1, desc.viewport);
		m_rhi->cmdSetScissor(0, 1, desc.scissor);

		drawDebugObject(current_swapchain_image_index);//绘制图形
	}

	void DebugDrawManager::drawDebugObject(uint32_t current_swapchain_image_index)
	{
		prepareDrawBuffer();//准备需要的缓冲
		drawPointLineTriangleBox(current_swapchain_image_index);
		drawWireFrameObject(current_swapchain_image_index);
	}

	//准备缓冲
	void DebugDrawManager::prepareDrawBuffer()
	{
		m_buffer_allocator->clear();//清理所有缓存

		std::vector<DebugDrawVertex> vertexs;

		//将顶点数据记录到临时缓存中，记录下前后缓存大小的变化
		m_debug_draw_group_for_render.writePointData(vertexs, false);//获取顶点数据
		m_point_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_point_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_debug_draw_group_for_render.writeLineData(vertexs, false);
		m_line_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_line_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_debug_draw_group_for_render.writeTriangleData(vertexs, false);
		m_triangle_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_triangle_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_debug_draw_group_for_render.writePointData(vertexs, true);
		m_no_depth_test_point_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_no_depth_test_point_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_debug_draw_group_for_render.writeLineData(vertexs, true);
		m_no_depth_test_line_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_no_depth_test_line_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_debug_draw_group_for_render.writeTriangleData(vertexs, true);
		m_no_depth_test_triangle_start_offset = m_buffer_allocator->cacheVertexs(vertexs);
		m_no_depth_test_triangle_end_offset = m_buffer_allocator->getVertexCacheOffset();

		m_buffer_allocator->cacheUniformObject(m_proj_view_matrix);

		std::vector<std::pair<Matrix4x4, Vector4> > dynamicObject = { std::make_pair(Matrix4x4::IDENTITY,Vector4(0,0,0,0)) };
		m_buffer_allocator->cacheUniformDynamicObject(dynamicObject);//空颜色，identity matrix

		//m_debug_draw_group_for_render.writeUniformDynamicDataToCache(dynamicObject);
		//m_buffer_allocator->cacheUniformDynamicObject(dynamicObject);//cache the wire frame uniform dynamic object

		m_buffer_allocator->allocator();//创建缓存区
	}

	//***********************************huizhi*******************************************//

	void DebugDrawManager::drawPointLineTriangleBox(uint32_t current_swapchain_image_index)
	{
		//绑定顶点缓冲
		VkBuffer vertex_buffers[] = { m_buffer_allocator->getVertexBuffer() };
		if (vertex_buffers[0] == nullptr){
			return;
		}
		VkDeviceSize offsets[] = { 0 };
		m_rhi->cmdBindVertexBuffers(m_rhi->getCurrentCommandBuffer(), 0, 1, vertex_buffers, offsets);//命令缓冲，偏移值，顶点缓冲数，顶点缓冲数组，开始读取数据的起始偏移量

		std::vector<DebugDrawPipeline*> pipelines{ m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_point],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_line],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_triangle],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_point_no_depth_test],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_line_no_depth_test],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_triangle_no_depth_test],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_triangle_no_depth_test] };

		//缓存大小的偏移量的集合
		std::vector<size_t> start_offsets{ m_point_start_offset, m_line_start_offset, m_triangle_start_offset, m_no_depth_test_point_start_offset, m_no_depth_test_line_start_offset, m_no_depth_test_triangle_start_offset,m_text_start_offset };
		std::vector<size_t> end_offsets{ m_point_end_offset,m_line_end_offset,m_triangle_end_offset, m_no_depth_test_point_end_offset, m_no_depth_test_line_end_offset,m_no_depth_test_triangle_end_offset,m_text_end_offset };

		std::array<VkClearValue, 2> clear_values;
		clear_values[0].color = { 0.0f,0.0f,0.0f,1.0f };
		clear_values[1].depthStencil = { 1.0f, 0 };//初始值为远平面的深度值

		//开始渲染流程的信息
		VkRenderPassBeginInfo renderpass_begin_info{};
		renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		//指定渲染的区域
		renderpass_begin_info.renderArea.offset = { 0, 0 };
		renderpass_begin_info.renderArea.extent = m_rhi->getSwapchainInfo().extent;
		renderpass_begin_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
		renderpass_begin_info.pClearValues = clear_values.data();

		for (size_t i = 0; i < pipelines.size(); i++)
		{
			if (end_offsets[i] - start_offsets[i] == 0)//如果需要绘制的顶点数据为0，直接跳过
			{
				continue;
			}
			renderpass_begin_info.renderPass = pipelines[i]->getFramebuffer().render_pass;
			renderpass_begin_info.framebuffer = pipelines[i]->getFramebuffer().framebuffers[current_swapchain_image_index];
			//开始流程
			m_rhi->cmdBeginRenderPass(m_rhi->getCurrentCommandBuffer(), &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);//要执行的指令都在主要指令缓冲
			//绑定图形管线
			m_rhi->cmdBindPipeline(m_rhi->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[i]->getPipeline().pipeline);

			//绑定描述符集
			uint32_t dynamicOffset = 0;//指定动态描述符的数组偏移
			VkDescriptorSet descriptor_set = m_buffer_allocator->getDescriptorSet();
			m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[i]->getPipeline().layout, 0, 1, &descriptor_set, 1, &dynamicOffset);

			//绘制：命令缓冲、顶点数、实例数（1时不进行实例渲染），gl_VertexIndex的值，gl_InstanceIndex的值
			m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(), end_offsets[i] - start_offsets[i], 1, start_offsets[i], 0);
			//结束渲染流程
			m_rhi->cmdEndRenderPass(m_rhi->getCurrentCommandBuffer());
		}
	}

	void DebugDrawManager::drawWireFrameObject(uint32_t current_swapchain_image_index)
	{
		//draw wire frame object : sphere, cylinder, capsule

		std::vector<DebugDrawPipeline*>vc_pipelines{ m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_line],
													 m_debug_draw_pipeline[DebugDrawPipelineType::_debug_draw_pipeline_type_line_no_depth_test] };
		std::vector<bool>no_depth_tests = { false,true };

		for (int32_t i = 0; i < 2; i++)
		{
			bool no_depth_test = no_depth_tests[i];

			VkDeviceSize offsets[] = { 0 };
			VkClearValue clear_values[2];
			clear_values[0].color = { 0.0f,0.0f,0.0f,0.0f };
			clear_values[1].depthStencil = { 1.0f, 0 };
			VkRenderPassBeginInfo renderpass_begin_info{};
			renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderpass_begin_info.renderArea.offset = { 0, 0 };
			renderpass_begin_info.renderArea.extent = m_rhi->getSwapchainInfo().extent;
			renderpass_begin_info.clearValueCount = (sizeof(clear_values) / sizeof(clear_values[0]));
			renderpass_begin_info.pClearValues = clear_values;
			renderpass_begin_info.renderPass = vc_pipelines[i]->getFramebuffer().render_pass;
			renderpass_begin_info.framebuffer = vc_pipelines[i]->getFramebuffer().framebuffers[current_swapchain_image_index];
			m_rhi->cmdBeginRenderPass(m_rhi->getCurrentCommandBuffer(), &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
			m_rhi->cmdBindPipeline(m_rhi->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, vc_pipelines[i]->getPipeline().pipeline);

			size_t uniform_dynamic_size = m_buffer_allocator->getSizeOfUniformBufferObject();
			uint32_t dynamicOffset = uniform_dynamic_size;

			size_t sphere_count = m_debug_draw_group_for_render.getSphereCount(no_depth_test);
			size_t cylinder_count = m_debug_draw_group_for_render.getCylinderCount(no_depth_test);
			size_t capsule_count = m_debug_draw_group_for_render.getCapsuleCount(no_depth_test);

			if (sphere_count > 0)
			{
				VkBuffer sphere_vertex_buffers[] = { m_buffer_allocator->getSphereVertexBuffer() };
				m_rhi->cmdBindVertexBuffers(m_rhi->getCurrentCommandBuffer(), 0, 1, sphere_vertex_buffers, offsets);
				for (size_t j = 0; j < sphere_count; j++)
				{

					m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(),VK_PIPELINE_BIND_POINT_GRAPHICS,vc_pipelines[i]->getPipeline().layout,0,1,&m_buffer_allocator->getDescriptorSet(),1,&dynamicOffset);
					m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(), m_buffer_allocator->getSphereVertexBufferSize(), 1, 0, 0);
					dynamicOffset += uniform_dynamic_size;
				}
			}

			if (cylinder_count > 0)
			{
				VkBuffer cylinder_vertex_buffers[] = { m_buffer_allocator->getCylinderVertexBuffer() };
				m_rhi->cmdBindVertexBuffers(m_rhi->getCurrentCommandBuffer(), 0, 1, cylinder_vertex_buffers, offsets);
				for (size_t j = 0; j < cylinder_count; j++)
				{
					m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(),
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						vc_pipelines[i]->getPipeline().layout,
						0,
						1,
						&m_buffer_allocator->getDescriptorSet(),
						1,
						&dynamicOffset);
					m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(), m_buffer_allocator->getCylinderVertexBufferSize(), 1, 0, 0);
					dynamicOffset += uniform_dynamic_size;
				}
			}

			if (capsule_count > 0)
			{
				VkBuffer capsule_vertex_buffers[] = { m_buffer_allocator->getCapsuleVertexBuffer() };
				m_rhi->cmdBindVertexBuffers(m_rhi->getCurrentCommandBuffer(), 0, 1, capsule_vertex_buffers, offsets);
				for (size_t j = 0; j < capsule_count; j++)
				{
					//draw capsule up part
					m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(),
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						vc_pipelines[i]->getPipeline().layout,
						0,
						1,
						&m_buffer_allocator->getDescriptorSet(),
						1,
						&dynamicOffset);
					m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(), m_buffer_allocator->getCapsuleVertexBufferUpSize(), 1, 0, 0);
					dynamicOffset += uniform_dynamic_size;

					//draw capsule mid part
					m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(),
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						vc_pipelines[i]->getPipeline().layout,
						0,
						1,
						&m_buffer_allocator->getDescriptorSet(),
						1,
						&dynamicOffset);
					m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(), m_buffer_allocator->getCapsuleVertexBufferMidSize(), 1, m_buffer_allocator->getCapsuleVertexBufferUpSize(), 0);
					dynamicOffset += uniform_dynamic_size;

					//draw capsule down part
					m_rhi->cmdBindDescriptorSets(m_rhi->getCurrentCommandBuffer(),
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						vc_pipelines[i]->getPipeline().layout,
						0,
						1,
						&m_buffer_allocator->getDescriptorSet(),
						1,
						&dynamicOffset);
					m_rhi->cmdDraw(m_rhi->getCurrentCommandBuffer(),
						m_buffer_allocator->getCapsuleVertexBufferDownSize(),
						1,
						m_buffer_allocator->getCapsuleVertexBufferUpSize() + m_buffer_allocator->getCapsuleVertexBufferMidSize(),
						0);
					dynamicOffset += uniform_dynamic_size;
				}
			}

			m_rhi->cmdEndRenderPass(m_rhi->getCurrentCommandBuffer());
		}
	}

	//***********************************删除*******************************************//

	//销毁所有管线、缓存分配器、字体
	void DebugDrawManager::destroy() {
		for (uint8_t i = 0; i < DebugDrawPipelineType::_debug_draw_pipeline_type_count; i++) {
			m_debug_draw_pipeline[i]->destroy();
			delete m_debug_draw_pipeline[i];
		}
		m_buffer_allocator->destory();
		delete m_buffer_allocator;

		delete m_font;
	}

	//删除所有组
	void DebugDrawManager::clear() {
		std::lock_guard<std::mutex> guard(m_mutex);
		m_debug_draw_context.clear();
	}

	void DebugDrawManager::tick(float delta_time) {
		std::lock_guard<std::mutex> guard(m_mutex);
		m_buffer_allocator->tick();//每帧删除缓冲区
		m_debug_draw_context.tick(delta_time);//检查是否有结束生命周期的物体
	}

	//***********************************获取绘制内容*******************************************//

	DebugDrawGroup* DebugDrawManager::tryGetOrCreateDebugDrawGroup(const std::string& name)
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		return m_debug_draw_context.tryGetOrCreateDebugDrawGroup(name);
	}

	void DebugDrawManager::swapDataToRender() {
		
		DebugDrawGroup* test = tryGetOrCreateDebugDrawGroup("test");
		Vector3 point0(-0.5f, -0.5f, 3.0f);
		Vector3 point1(0.5f, -0.5f, 3.0f);
		Vector3 point2(0.5f, 0.5f, 0.5f);
		Vector3 point3(-0.5, 0.5f, 0.0f);
		Vector4 color0(1.0f, 0.0f, 1.0f, 1.0f);
		Vector4 color1(0.0f, 1.0f, 0.0f, 1.0f);
		Vector4 color2(0.0f, 0.0f, 1.0f, 1.0f);
		Vector4 color3(1.0f, 1.0f, 1.0f, 1.0f);
		Vector3 point4(-0.5f, -0.5f, -0.5f);
		Vector3 point5(0.5f, -0.5f, -1.0f);
		Vector3 point6(0.0f, 0.0f, 0.0f);
		Vector3 point7(-0.5, 0.5f, -5.0f);
		//test->addQuad(point0, point1, point2, point3, color0, color1, color2, color3, _debugDrawTimeType_infinity, false, _FillMode_solid);
		//test->addQuad(point4, point5, point6, point7, color0, color1, color2, color3, _debugDrawTimeType_infinity, true, _FillMode_solid);
		Vector4 rotation(0.0f, 0.0f, 0.0f, 0.0f);
		//test->addBox(point6, point2, rotation, color0, _debugDrawTimeType_infinity, false);

		std::lock_guard<std::mutex> guard(m_mutex);
		//从context找到所有组
		m_debug_draw_group_for_render.clear();
		size_t debug_draw_group_count = m_debug_draw_context.m_debug_draw_groups.size();

		//将目前的所有组都合并到要进行绘制的组里
		for (size_t index = 0; index < debug_draw_group_count; index++)
		{
			DebugDrawGroup* debug_draw_group = m_debug_draw_context.m_debug_draw_groups[index];
			if (debug_draw_group == nullptr) continue;
			m_debug_draw_group_for_render.mergeFrom(debug_draw_group);
		}
	}

	//准备通道数据：投影视图矩阵
	void DebugDrawManager::preparePassData(std::shared_ptr<RenderResourceBase> render_resource)
	{
		const RenderResource* resource = static_cast<const RenderResource*>(render_resource.get());
		m_proj_view_matrix = resource->m_mesh_perframe_storage_buffer_object.proj_view_matrix;
	}




	//***********************************重建交换链*******************************************//
	void DebugDrawManager::updateAfterRecreateSwapchain()
	{
		for (uint8_t i = 0; i < DebugDrawPipelineType::_debug_draw_pipeline_type_count; i++)
		{
			m_debug_draw_pipeline[i]->recreateAfterSwapchain();//删除帧缓冲
		}
	}


}