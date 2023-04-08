#pragma once

#include "../../render/window_system.h"
#include "rhi_struct.h"
#include <vk_mem_alloc.h>
#include<memory>
#include<vector>

namespace SimpleEngine {
	struct RHIInitInfo
	{
		std::shared_ptr<WindowSystem> windowSystem;
	};

	class RHI
	{
	public:
		virtual void init(RHIInitInfo init_info) = 0;
		virtual void prepareContext() = 0;
		virtual bool isPointLightShadowEnabled() = 0;

		virtual void clear() = 0;

		virtual uint8_t getMaxFramesInFlight() const = 0;
		virtual uint8_t getCurrentFrameIndex() const = 0;
		virtual void setCurrentFrameIndex(uint8_t index) = 0;

		//校验层
		virtual void pushEvent(VkCommandBuffer& commond_buffer, const char* name, const float* color) = 0;
		virtual void popEvent(VkCommandBuffer& commond_buffer) = 0;

		//设备
		virtual void getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) = 0;

		//队列
		virtual QueueFamilyIndices getQueueFamilyIndices() const = 0;
		virtual VkResult queueSubmit(VkQueue& queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) = 0;
		virtual VkResult queueWaitIdle(VkQueue& queue) = 0;

		virtual VkCommandPool getCommandPool() const = 0;
		virtual VkResult allocateCommandBuffers(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) = 0;
		virtual void freeCommandBuffers(VkCommandPool& commandPool, uint32_t commandBufferCount, VkCommandBuffer* pCommandBuffers) = 0;
		virtual void resetCommandPool() = 0;

		//交换链
		virtual void createSwapchain() = 0;//缓冲渲染，用于图像呈现和屏幕刷新
		virtual void createSwapchainImageViews() = 0;//访问图像
		virtual void recreateSwapchain() = 0;

		//重建交换链用
		virtual void destroyFramebuffer(VkFramebuffer& framebuffer) = 0;
		
		virtual SwapChainDesc getSwapchainInfo() = 0;
		virtual DepthImageDesc getDepthImageInfo() = 0;

		//运行时动态修改视口、裁剪设置
		virtual void cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount,const VkViewport* pViewports) = 0;
		virtual void cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount,const VkRect2D* pScissors) = 0;
		
		//渲染流程
		virtual void cmdBeginRenderPass(VkCommandBuffer& commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) = 0;
		virtual void cmdBindPipeline(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) = 0;
		virtual void cmdDraw(VkCommandBuffer& commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;
		virtual void cmdEndRenderPass(VkCommandBuffer& commandBuffer) = 0;
		virtual void cmdNextSubpass(VkCommandBuffer& commandBuffer, VkSubpassContents contents) = 0;

		virtual bool prepareBeforePass(std::function<void()> passUpdateAfterRecreateSwapchain) = 0;
		virtual void submitRendering(std::function<void()> passUpdateAfterRecreateSwapchain) = 0;

		virtual void cmdClearAttachments(VkCommandBuffer& commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) = 0;

		//信号
		virtual VkResult waitForFences(uint32_t fenceCount,const VkFence* pFence, VkBool32 waitAll, uint64_t timeout) = 0;
		virtual VkResult resetFences(uint32_t fenceCount, const VkFence* pFences) = 0;
		virtual void waitForFences() = 0;
		virtual VkSemaphore getTextureCopySemaphore(uint32_t index) = 0;
		virtual const VkFence* getFenceList() const = 0;
		virtual void cmdPipelineBarrier(VkCommandBuffer& commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) = 0;

		//内存
		virtual void freeMemory(VkDeviceMemory& memory) = 0;
		virtual VkResult mapMemory(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) = 0;
		virtual void unmapMemory(VkDeviceMemory& memory) = 0;
		virtual void invalidateMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) = 0;
		virtual void flushMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size) = 0;

		virtual void cmdBindVertexBuffers(VkCommandBuffer& commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) = 0;
		virtual void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory) = 0;
		virtual void createBufferAndInitialize(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory, VkDeviceSize size, void* data = nullptr, int datasize = 0) = 0;
		virtual VkResult createBufferVMA(VmaAllocator allocator,const VkBufferCreateInfo* pBufferCreateInfo,const VmaAllocationCreateInfo* pAllocationCreateInfo,VkBuffer* pBuffer,VmaAllocation* pAllocation,VmaAllocationInfo* pAllocationInfo) = 0;

		//着色器模块
		virtual VkShaderModule createShaderModule(const std::vector<unsigned char>& shader_code) = 0;
		virtual void destroyShaderModule(VkShaderModule& shaderModule) = 0;

		virtual VkResult createPipelineLayout(const VkPipelineLayoutCreateInfo* pCreateInfo, VkPipelineLayout* pPipelineLayout) = 0;
		virtual VkResult createRenderPass(VkRenderPassCreateInfo* pCreateInfo, VkRenderPass* pRenderPass) = 0;
		virtual VkResult createGraphicsPipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipelines) = 0;

		virtual VkResult createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer) = 0;
		virtual VkResult beginCommandBuffer(VkCommandBuffer& commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) = 0;
		virtual VkResult endCommandBuffer(VkCommandBuffer& commandBuffer) = 0;

		//暂存缓冲
		virtual VkCommandBuffer& beginSingleTimeCommands() = 0;
		virtual void endSingleTimeCommands(VkCommandBuffer& command_buffer) = 0;
		virtual void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size) = 0;
		virtual void destroyBuffer(VkBuffer& buffer) = 0;

		//索引缓冲
		virtual void cmdBindIndexBuffer(VkCommandBuffer& commandBuffer, VkBuffer& buffer, VkDeviceSize offset, VkIndexType indexType) = 0;
		virtual void cmdDrawIndexed(VkCommandBuffer& commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) = 0;

		virtual VkResult createSemaphore(const VkSemaphoreCreateInfo* pCreateInfo, VkSemaphore* pSemaphore) = 0;
		virtual VkResult createFence(const VkFenceCreateInfo* pCreateInfo, VkFence* pFence) = 0;
		
		virtual VkCommandBuffer& getCurrentCommandBuffer() = 0;
		virtual VkQueue& getGraphicsQueue() = 0;
		virtual VkQueue& getComputeQueue() = 0;

		//描述符
		virtual VkResult createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout) = 0;
		virtual VkDescriptorPool getDescriptorPool() const = 0;
		virtual VkResult allocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) = 0;
		virtual void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) = 0;
		virtual void cmdBindDescriptorSets(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) = 0;

		//纹理图像
		virtual void createImage(uint32_t image_width, uint32_t image_height, VkFormat format, VkImageTiling image_tiling, VkImageUsageFlags image_usage_flags, VkMemoryPropertyFlags memory_property_flags, VkImage& image, VkDeviceMemory& memory, VkImageCreateFlags image_create_flags, uint32_t array_layers, uint32_t mip_levels) = 0;
		virtual void createImageView(VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels,VkImageView& image_view) = 0;
		virtual void createGlobalImage(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, void* texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels = 0) = 0;
		virtual void destroyImageView(VkImageView& imageView) = 0;
		virtual void destroyImage(VkImage& image) = 0;
		virtual void cmdCopyImageToBuffer(VkCommandBuffer& commandBuffer, VkImage& srcImage, VkImageLayout srcImageLayout, VkBuffer& dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) = 0;
		virtual void createCubeMap(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) = 0;

		//采样器
		virtual VkResult createSampler(const VkSamplerCreateInfo* pCreateInfo, VkSampler* pSampler) = 0;
		virtual VkSampler getOrCreateDefaultSampler(DefaultSamplerType type) = 0;
		virtual VkSampler getOrCreateMipmapSampler(uint32_t width, uint32_t height) = 0;
		virtual void destroySampler(VkSampler& sampler) = 0;

		//渲染管线
		virtual void destroyPipelineLayout(VkPipelineLayout& layout) = 0;
		virtual void destroyPipeline(VkPipeline& pipeline) = 0;
		virtual void destroyRenderPass(VkRenderPass& render_pass) = 0;

		virtual VkResult createBufferWithAlignmentVMA(VmaAllocator allocator, const VkBufferCreateInfo* pBufferCreateInfo, const VmaAllocationCreateInfo* pAllocationCreateInfo, VkDeviceSize minAlignment, VkBuffer* pBuffer, VmaAllocation* pAllocation, VmaAllocationInfo* pAllocationInfo) = 0;
	};	
}