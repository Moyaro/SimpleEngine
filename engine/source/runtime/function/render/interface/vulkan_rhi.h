#pragma once

#include "rhi.h"
#include "rhi_struct.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <map>

namespace SimpleEngine {
	class VulkanRHI : public RHI
	{
	public:
		static uint8_t const k_max_frames_in_flight{ 3 };//可以并行处理的帧数
		uint8_t getMaxFramesInFlight() const override { return k_max_frames_in_flight;}

		uint8_t getCurrentFrameIndex() const override { return m_current_frame_index; }
		void setCurrentFrameIndex(uint8_t index) override{ m_current_frame_index = index; }

		void init(RHIInitInfo init_info) override;
		void prepareContext() override;//设置当前命令缓冲
		bool isPointLightShadowEnabled() override { return m_enable_point_light_shadow; }
		void clear() override;

		//设备
		void getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) override{ vkGetPhysicalDeviceProperties(m_physical_device, pProperties); }

		//着色器模块
		VkShaderModule createShaderModule(const std::vector<unsigned char>& shader_code) override;
		void destroyShaderModule(VkShaderModule& shaderModule) override;

		VkResult createPipelineLayout(const VkPipelineLayoutCreateInfo* pCreateInfo, VkPipelineLayout* pPipelineLayout) override;
		VkResult createRenderPass(VkRenderPassCreateInfo* pCreateInfo, VkRenderPass* pRenderPass) override;
		VkResult createGraphicsPipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipelines) override;
		VkResult createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer) override;
		VkResult beginCommandBuffer(VkCommandBuffer& commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) override;//指定指令缓冲使用细节
		VkResult endCommandBuffer(VkCommandBuffer& commandBuffer) override;

		//渲染流程
		void cmdBeginRenderPass(VkCommandBuffer& commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
		void cmdBindPipeline(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
		void cmdDraw(VkCommandBuffer& commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
		void cmdEndRenderPass(VkCommandBuffer& commandBuffer) override;
		void cmdNextSubpass(VkCommandBuffer& commandBuffer, VkSubpassContents contents) override;

		bool prepareBeforePass(std::function<void()> passUpdateAfterRecreateSwapchain) override;//渲染流程前的准备
		void submitRendering(std::function<void()> passUpdateAfterRecreateSwapchain) override;//开始渲染

		void cmdClearAttachments(VkCommandBuffer& commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) override;

		VkResult createSemaphore(const VkSemaphoreCreateInfo* pCreateInfo, VkSemaphore* pSemaphore) override;
		VkResult createFence(const VkFenceCreateInfo* pCreateInfo, VkFence* pFence) override;
		VkResult createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout) override;

		GLFWwindow* m_window{nullptr};
		VkInstance m_instance{ nullptr };
		VkSurfaceKHR m_surface{ nullptr };
		VkPhysicalDevice m_physical_device{ nullptr };
		VkDevice m_device{ nullptr };

		//交换链
		VkSwapchainKHR m_swapchain{ nullptr };
		std::vector<VkImage> m_swapchain_images;
		uint32_t m_current_swapchain_image_index;
		VkFormat m_swapchain_image_format{VK_FORMAT_UNDEFINED};
		VkExtent2D m_swapchain_extent;
		VkViewport m_viewport;
		VkRect2D m_scissor;
		void cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount,const VkViewport* pViewports) override;
		void cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount,const VkRect2D* pScissors) override;
		
		void createSwapchain() override;//缓冲渲染，用于图像呈现和屏幕刷新
		void createSwapchainImageViews() override;//访问图像
		SwapChainDesc getSwapchainInfo() override;

		//重建交换链
		void recreateSwapchain() override;
		void destroyFramebuffer(VkFramebuffer& framebuffer) override;

		//深度图的信息
		DepthImageDesc getDepthImageInfo() override;
		VkFormat m_depth_image_format{ VK_FORMAT_UNDEFINED };
		VkImageView m_depth_image_view{ nullptr };
		VkImage m_depth_image{ nullptr };
		VkDeviceMemory m_depth_image_memory{ nullptr };

		std::vector<VkImageView> m_swapchain_imageviews;
		std::vector<VkFramebuffer> m_swapchain_framebuffers;

		//队列
		VkQueue m_present_queue{ nullptr };
		VkQueue m_graphics_queue{ nullptr };
		VkQueue m_compute_queue{ nullptr };
		QueueFamilyIndices m_queue_indices;

		VkQueue& getGraphicsQueue() override { return m_graphics_queue; }
		VkQueue& getComputeQueue() override { return m_compute_queue; }
		QueueFamilyIndices getQueueFamilyIndices() const override { return m_queue_indices; }
		VkResult queueSubmit(VkQueue& queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) override;
		VkResult queueWaitIdle(VkQueue& queue) override;
		

		//指令缓冲、指令池
		
		VkCommandPool m_rhi_command_pool;//用于暂存缓冲
		VkCommandPool m_command_pools[k_max_frames_in_flight];
		VkCommandBuffer m_current_command_buffer;
		VkCommandBuffer m_command_buffers[k_max_frames_in_flight];

		VkCommandBuffer& getCurrentCommandBuffer() override { return m_current_command_buffer; }
		VkCommandPool getCommandPool() const{ return m_rhi_command_pool; }
		VkResult allocateCommandBuffers(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) override;
		void freeCommandBuffers(VkCommandPool& commandPool, uint32_t commandBufferCount, VkCommandBuffer* pCommandBuffers) override;
		void resetCommandPool() override;

		//暂存缓冲
		VkCommandBuffer& beginSingleTimeCommands() override;
		void endSingleTimeCommands(VkCommandBuffer& command_buffer) override;
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size) override;
		void destroyBuffer(VkBuffer& buffer) override;

		//内存
		void freeMemory(VkDeviceMemory& memory) override;
		VkResult mapMemory(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) override;//映射内存
		void unmapMemory(VkDeviceMemory& memory) override;//结束映射
		void invalidateMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) override;//将映射到内存中的数据失效，以便获取最新的数据。
		void flushMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) override;//将映射到内存中的数据刷新到硬件中

		//创建缓冲
		void cmdBindVertexBuffers(VkCommandBuffer& commandBuffer,uint32_t firstBinding,uint32_t bindingCount,const VkBuffer* pBuffers,const VkDeviceSize* pOffsets) override;
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory) override;
		void createBufferAndInitialize(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory, VkDeviceSize size, void* data = nullptr, int datasize = 0) override;
		VkResult createBufferVMA(VmaAllocator allocator,const VkBufferCreateInfo* pBufferCreateInfo,const VmaAllocationCreateInfo* pAllocationCreateInfo,VkBuffer* pBuffer,VmaAllocation* pAllocation,VmaAllocationInfo* pAllocationInfo) override;

		void cmdBindIndexBuffer(VkCommandBuffer& commandBuffer, VkBuffer& buffer, VkDeviceSize offset, VkIndexType indexType) override;
		void cmdDrawIndexed(VkCommandBuffer& commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) override;
		
		//信号量：每帧一个
		uint8_t m_current_frame_index{ 0 };
		VkSemaphore m_image_available_for_render_semaphores[k_max_frames_in_flight];//图像已经获取，可以渲染的信号量
		VkSemaphore m_image_finished_for_presentation_semaphores[k_max_frames_in_flight];//渲染结束，可以开始呈现的信号量
		VkSemaphore m_image_available_for_texturescopy_semaphores[k_max_frames_in_flight];
		VkFence m_is_frame_in_flight_fences[k_max_frames_in_flight];//一帧结束时发出的信号
		

		VkResult resetFences(uint32_t fenceCount, const VkFence* pFences) override;//调至未发出信号的状态
		VkResult waitForFences(uint32_t fenceCount, const VkFence* pFence, VkBool32 waitAll, uint64_t timeout);//等待信号
		void waitForFences();
		VkSemaphore getTextureCopySemaphore(uint32_t index) override{ return m_image_available_for_texturescopy_semaphores[index]; }
		const VkFence* getFenceList() const override { return m_is_frame_in_flight_fences; }
		void cmdPipelineBarrier(VkCommandBuffer& commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) {
			return vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
		}

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//内存分配器
		VmaAllocator m_assets_allocator;
		VkResult createBufferWithAlignmentVMA(VmaAllocator allocator,const VkBufferCreateInfo* pBufferCreateInfo,const VmaAllocationCreateInfo* pAllocationCreateInfo,VkDeviceSize minAlignment,VkBuffer* pBuffer,VmaAllocation* pAllocation,VmaAllocationInfo* pAllocationInfo) override;

		//描述符
		VkDescriptorPool getDescriptorPool() const override { return m_descriptor_pool; }
		VkResult allocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) override;
		void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) override;
		void cmdBindDescriptorSets(VkCommandBuffer& commandBuffer,VkPipelineBindPoint pipelineBindPoint,VkPipelineLayout layout,uint32_t firstSet,uint32_t descriptorSetCount,const VkDescriptorSet* pDescriptorSets,uint32_t dynamicOffsetCount,const uint32_t* pDynamicOffsets) override;

		//纹理图像
		void createImage(uint32_t image_width, uint32_t image_height, VkFormat format, VkImageTiling image_tiling, VkImageUsageFlags image_usage_flags, VkMemoryPropertyFlags memory_property_flags, VkImage& image, VkDeviceMemory& memory, VkImageCreateFlags image_create_flags, uint32_t array_layers, uint32_t mip_levels) override;
		void createImageView(VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels, VkImageView& image_view) override;
		void createGlobalImage(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, void* texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels = 0) override;
		VkResult createSampler(const VkSamplerCreateInfo* pCreateInfo, VkSampler* pSampler) override;
		void destroyImageView(VkImageView& imageView) override;
		void destroyImage(VkImage& image) override;
		void cmdCopyImageToBuffer(VkCommandBuffer& commandBuffer, VkImage& srcImage, VkImageLayout srcImageLayout, VkBuffer& dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) override { vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions); }
		void createCubeMap(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) override;

		//采样器
		VkSampler getOrCreateDefaultSampler(DefaultSamplerType type) override;
		VkSampler getOrCreateMipmapSampler(uint32_t width, uint32_t height) override;
		void destroySampler(VkSampler& sampler) override{ vkDestroySampler(m_device, sampler, nullptr); }

		VkDescriptorPool m_descriptor_pool;

		//校验层
		PFN_vkCmdBeginDebugUtilsLabelEXT _vkCmdBeginDebugUtilsLabelEXT;
		PFN_vkCmdEndDebugUtilsLabelEXT   _vkCmdEndDebugUtilsLabelEXT;
		void pushEvent(VkCommandBuffer& commond_buffer, const char* name, const float* color) override;
		void popEvent(VkCommandBuffer& commond_buffer) override;
	private:
		void createInstance();
		void setupDebugCallback();
		void createSurface();//可供Vulkan渲染的表面
		void pickPhysicalDevice();
		void createLogicalDevice();//与物理设备交互的接口
		void createCommandPool();
		void createCommandBuffers();
		void createDescriptorPool();
		void createSyncPrimitives();
		void createDepthResource();

		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		
		void createAssetAllocator();

		//检测物理设备
		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
	
		bool m_enable_debug_utils_label{ true };
		bool m_enable_validation_layers{ true };//启动校验层
		bool m_enable_point_light_shadow{ true };//启动点光

		//校验层
		const std::vector<const char*> m_validation_layers = { "VK_LAYER_KHRONOS_validation" };//校验层列表，隐式开启所有可用校验层
		VkDebugUtilsMessengerEXT m_callback{ nullptr };//回调函数信息
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		//创建交换链
		std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };//交换链扩展
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);//检查设备扩展支持
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_surface_formats);
		VkPresentModeKHR chooseSwapchainPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes);
		VkExtent2D chooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		//描述符
		
		uint32_t m_max_material_count{ 256 };
		uint32_t m_max_vertex_blending_mesh_count{ 256 };

		//采样器
		VkSampler m_linear_sampler;
		VkSampler m_nearest_sampler;
		std::map<uint32_t, VkSampler> m_mipmap_sampler_map;

		//深度图
		VkFormat findDepthFormat();//查找支持的深度图像格式。
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,VkImageTiling tiling,VkFormatFeatureFlags features);//检查每个格式的属性是否与指定的图像平铺和格式特性兼容

		//渲染管线
		void destroyPipelineLayout(VkPipelineLayout& layout) override { vkDestroyPipelineLayout(m_device, layout, nullptr); }
		void destroyPipeline(VkPipeline& pipeline) override { vkDestroyPipeline(m_device, pipeline, nullptr); }
		void destroyRenderPass(VkRenderPass& render_pass) { vkDestroyRenderPass(m_device, render_pass, nullptr); }
	};
}