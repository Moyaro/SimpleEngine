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
		static uint8_t const k_max_frames_in_flight{ 3 };//���Բ��д����֡��
		uint8_t getMaxFramesInFlight() const override { return k_max_frames_in_flight;}

		uint8_t getCurrentFrameIndex() const override { return m_current_frame_index; }
		void setCurrentFrameIndex(uint8_t index) override{ m_current_frame_index = index; }

		void init(RHIInitInfo init_info) override;
		void prepareContext() override;//���õ�ǰ�����
		bool isPointLightShadowEnabled() override { return m_enable_point_light_shadow; }
		void clear() override;

		//�豸
		void getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) override{ vkGetPhysicalDeviceProperties(m_physical_device, pProperties); }

		//��ɫ��ģ��
		VkShaderModule createShaderModule(const std::vector<unsigned char>& shader_code) override;
		void destroyShaderModule(VkShaderModule& shaderModule) override;

		VkResult createPipelineLayout(const VkPipelineLayoutCreateInfo* pCreateInfo, VkPipelineLayout* pPipelineLayout) override;
		VkResult createRenderPass(VkRenderPassCreateInfo* pCreateInfo, VkRenderPass* pRenderPass) override;
		VkResult createGraphicsPipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipelines) override;
		VkResult createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer) override;
		VkResult beginCommandBuffer(VkCommandBuffer& commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) override;//ָ��ָ���ʹ��ϸ��
		VkResult endCommandBuffer(VkCommandBuffer& commandBuffer) override;

		//��Ⱦ����
		void cmdBeginRenderPass(VkCommandBuffer& commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
		void cmdBindPipeline(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
		void cmdDraw(VkCommandBuffer& commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
		void cmdEndRenderPass(VkCommandBuffer& commandBuffer) override;
		void cmdNextSubpass(VkCommandBuffer& commandBuffer, VkSubpassContents contents) override;

		bool prepareBeforePass(std::function<void()> passUpdateAfterRecreateSwapchain) override;//��Ⱦ����ǰ��׼��
		void submitRendering(std::function<void()> passUpdateAfterRecreateSwapchain) override;//��ʼ��Ⱦ

		void cmdClearAttachments(VkCommandBuffer& commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) override;

		VkResult createSemaphore(const VkSemaphoreCreateInfo* pCreateInfo, VkSemaphore* pSemaphore) override;
		VkResult createFence(const VkFenceCreateInfo* pCreateInfo, VkFence* pFence) override;
		VkResult createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout) override;

		GLFWwindow* m_window{nullptr};
		VkInstance m_instance{ nullptr };
		VkSurfaceKHR m_surface{ nullptr };
		VkPhysicalDevice m_physical_device{ nullptr };
		VkDevice m_device{ nullptr };

		//������
		VkSwapchainKHR m_swapchain{ nullptr };
		std::vector<VkImage> m_swapchain_images;
		uint32_t m_current_swapchain_image_index;
		VkFormat m_swapchain_image_format{VK_FORMAT_UNDEFINED};
		VkExtent2D m_swapchain_extent;
		VkViewport m_viewport;
		VkRect2D m_scissor;
		void cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount,const VkViewport* pViewports) override;
		void cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount,const VkRect2D* pScissors) override;
		
		void createSwapchain() override;//������Ⱦ������ͼ����ֺ���Ļˢ��
		void createSwapchainImageViews() override;//����ͼ��
		SwapChainDesc getSwapchainInfo() override;

		//�ؽ�������
		void recreateSwapchain() override;
		void destroyFramebuffer(VkFramebuffer& framebuffer) override;

		//���ͼ����Ϣ
		DepthImageDesc getDepthImageInfo() override;
		VkFormat m_depth_image_format{ VK_FORMAT_UNDEFINED };
		VkImageView m_depth_image_view{ nullptr };
		VkImage m_depth_image{ nullptr };
		VkDeviceMemory m_depth_image_memory{ nullptr };

		std::vector<VkImageView> m_swapchain_imageviews;
		std::vector<VkFramebuffer> m_swapchain_framebuffers;

		//����
		VkQueue m_present_queue{ nullptr };
		VkQueue m_graphics_queue{ nullptr };
		VkQueue m_compute_queue{ nullptr };
		QueueFamilyIndices m_queue_indices;

		VkQueue& getGraphicsQueue() override { return m_graphics_queue; }
		VkQueue& getComputeQueue() override { return m_compute_queue; }
		QueueFamilyIndices getQueueFamilyIndices() const override { return m_queue_indices; }
		VkResult queueSubmit(VkQueue& queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) override;
		VkResult queueWaitIdle(VkQueue& queue) override;
		

		//ָ��塢ָ���
		
		VkCommandPool m_rhi_command_pool;//�����ݴ滺��
		VkCommandPool m_command_pools[k_max_frames_in_flight];
		VkCommandBuffer m_current_command_buffer;
		VkCommandBuffer m_command_buffers[k_max_frames_in_flight];

		VkCommandBuffer& getCurrentCommandBuffer() override { return m_current_command_buffer; }
		VkCommandPool getCommandPool() const{ return m_rhi_command_pool; }
		VkResult allocateCommandBuffers(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) override;
		void freeCommandBuffers(VkCommandPool& commandPool, uint32_t commandBufferCount, VkCommandBuffer* pCommandBuffers) override;
		void resetCommandPool() override;

		//�ݴ滺��
		VkCommandBuffer& beginSingleTimeCommands() override;
		void endSingleTimeCommands(VkCommandBuffer& command_buffer) override;
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size) override;
		void destroyBuffer(VkBuffer& buffer) override;

		//�ڴ�
		void freeMemory(VkDeviceMemory& memory) override;
		VkResult mapMemory(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) override;//ӳ���ڴ�
		void unmapMemory(VkDeviceMemory& memory) override;//����ӳ��
		void invalidateMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) override;//��ӳ�䵽�ڴ��е�����ʧЧ���Ա��ȡ���µ����ݡ�
		void flushMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) override;//��ӳ�䵽�ڴ��е�����ˢ�µ�Ӳ����

		//��������
		void cmdBindVertexBuffers(VkCommandBuffer& commandBuffer,uint32_t firstBinding,uint32_t bindingCount,const VkBuffer* pBuffers,const VkDeviceSize* pOffsets) override;
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory) override;
		void createBufferAndInitialize(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory, VkDeviceSize size, void* data = nullptr, int datasize = 0) override;
		VkResult createBufferVMA(VmaAllocator allocator,const VkBufferCreateInfo* pBufferCreateInfo,const VmaAllocationCreateInfo* pAllocationCreateInfo,VkBuffer* pBuffer,VmaAllocation* pAllocation,VmaAllocationInfo* pAllocationInfo) override;

		void cmdBindIndexBuffer(VkCommandBuffer& commandBuffer, VkBuffer& buffer, VkDeviceSize offset, VkIndexType indexType) override;
		void cmdDrawIndexed(VkCommandBuffer& commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) override;
		
		//�ź�����ÿ֡һ��
		uint8_t m_current_frame_index{ 0 };
		VkSemaphore m_image_available_for_render_semaphores[k_max_frames_in_flight];//ͼ���Ѿ���ȡ��������Ⱦ���ź���
		VkSemaphore m_image_finished_for_presentation_semaphores[k_max_frames_in_flight];//��Ⱦ���������Կ�ʼ���ֵ��ź���
		VkSemaphore m_image_available_for_texturescopy_semaphores[k_max_frames_in_flight];
		VkFence m_is_frame_in_flight_fences[k_max_frames_in_flight];//һ֡����ʱ�������ź�
		

		VkResult resetFences(uint32_t fenceCount, const VkFence* pFences) override;//����δ�����źŵ�״̬
		VkResult waitForFences(uint32_t fenceCount, const VkFence* pFence, VkBool32 waitAll, uint64_t timeout);//�ȴ��ź�
		void waitForFences();
		VkSemaphore getTextureCopySemaphore(uint32_t index) override{ return m_image_available_for_texturescopy_semaphores[index]; }
		const VkFence* getFenceList() const override { return m_is_frame_in_flight_fences; }
		void cmdPipelineBarrier(VkCommandBuffer& commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) {
			return vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
		}

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//�ڴ������
		VmaAllocator m_assets_allocator;
		VkResult createBufferWithAlignmentVMA(VmaAllocator allocator,const VkBufferCreateInfo* pBufferCreateInfo,const VmaAllocationCreateInfo* pAllocationCreateInfo,VkDeviceSize minAlignment,VkBuffer* pBuffer,VmaAllocation* pAllocation,VmaAllocationInfo* pAllocationInfo) override;

		//������
		VkDescriptorPool getDescriptorPool() const override { return m_descriptor_pool; }
		VkResult allocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) override;
		void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) override;
		void cmdBindDescriptorSets(VkCommandBuffer& commandBuffer,VkPipelineBindPoint pipelineBindPoint,VkPipelineLayout layout,uint32_t firstSet,uint32_t descriptorSetCount,const VkDescriptorSet* pDescriptorSets,uint32_t dynamicOffsetCount,const uint32_t* pDynamicOffsets) override;

		//����ͼ��
		void createImage(uint32_t image_width, uint32_t image_height, VkFormat format, VkImageTiling image_tiling, VkImageUsageFlags image_usage_flags, VkMemoryPropertyFlags memory_property_flags, VkImage& image, VkDeviceMemory& memory, VkImageCreateFlags image_create_flags, uint32_t array_layers, uint32_t mip_levels) override;
		void createImageView(VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels, VkImageView& image_view) override;
		void createGlobalImage(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, void* texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels = 0) override;
		VkResult createSampler(const VkSamplerCreateInfo* pCreateInfo, VkSampler* pSampler) override;
		void destroyImageView(VkImageView& imageView) override;
		void destroyImage(VkImage& image) override;
		void cmdCopyImageToBuffer(VkCommandBuffer& commandBuffer, VkImage& srcImage, VkImageLayout srcImageLayout, VkBuffer& dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) override { vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions); }
		void createCubeMap(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) override;

		//������
		VkSampler getOrCreateDefaultSampler(DefaultSamplerType type) override;
		VkSampler getOrCreateMipmapSampler(uint32_t width, uint32_t height) override;
		void destroySampler(VkSampler& sampler) override{ vkDestroySampler(m_device, sampler, nullptr); }

		VkDescriptorPool m_descriptor_pool;

		//У���
		PFN_vkCmdBeginDebugUtilsLabelEXT _vkCmdBeginDebugUtilsLabelEXT;
		PFN_vkCmdEndDebugUtilsLabelEXT   _vkCmdEndDebugUtilsLabelEXT;
		void pushEvent(VkCommandBuffer& commond_buffer, const char* name, const float* color) override;
		void popEvent(VkCommandBuffer& commond_buffer) override;
	private:
		void createInstance();
		void setupDebugCallback();
		void createSurface();//�ɹ�Vulkan��Ⱦ�ı���
		void pickPhysicalDevice();
		void createLogicalDevice();//�������豸�����Ľӿ�
		void createCommandPool();
		void createCommandBuffers();
		void createDescriptorPool();
		void createSyncPrimitives();
		void createDepthResource();

		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		
		void createAssetAllocator();

		//��������豸
		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
	
		bool m_enable_debug_utils_label{ true };
		bool m_enable_validation_layers{ true };//����У���
		bool m_enable_point_light_shadow{ true };//�������

		//У���
		const std::vector<const char*> m_validation_layers = { "VK_LAYER_KHRONOS_validation" };//У����б���ʽ�������п���У���
		VkDebugUtilsMessengerEXT m_callback{ nullptr };//�ص�������Ϣ
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		//����������
		std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };//��������չ
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);//����豸��չ֧��
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_surface_formats);
		VkPresentModeKHR chooseSwapchainPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes);
		VkExtent2D chooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		//������
		
		uint32_t m_max_material_count{ 256 };
		uint32_t m_max_vertex_blending_mesh_count{ 256 };

		//������
		VkSampler m_linear_sampler;
		VkSampler m_nearest_sampler;
		std::map<uint32_t, VkSampler> m_mipmap_sampler_map;

		//���ͼ
		VkFormat findDepthFormat();//����֧�ֵ����ͼ���ʽ��
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,VkImageTiling tiling,VkFormatFeatureFlags features);//���ÿ����ʽ�������Ƿ���ָ����ͼ��ƽ�̺͸�ʽ���Լ���

		//��Ⱦ����
		void destroyPipelineLayout(VkPipelineLayout& layout) override { vkDestroyPipelineLayout(m_device, layout, nullptr); }
		void destroyPipeline(VkPipeline& pipeline) override { vkDestroyPipeline(m_device, pipeline, nullptr); }
		void destroyRenderPass(VkRenderPass& render_pass) { vkDestroyRenderPass(m_device, render_pass, nullptr); }
	};
}