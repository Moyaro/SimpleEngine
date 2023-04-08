#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "rhi.h"

namespace SimpleEngine {
	/// <summary>
	/// ��Ⱦ�����ڿ��ظ��������ݵļ���
	/// </summary>
	class VulkanUtil
	{
	public:
		static VkShaderModule createShaderModule(VkDevice device, const std::vector<unsigned char>& code);//��ɫ��ģ�飺����ɫ�������ڹ�����ʹ��

		//��������
		static void createBuffer(VkPhysicalDevice physical_device,VkDevice device,VkDeviceSize size,VkBufferUsageFlags usage,VkMemoryPropertyFlags properties,VkBuffer& buffer,VkDeviceMemory& buffer_memory);
		static void createBufferAndInitialize(VkDevice device,VkPhysicalDevice physicalDevice,VkBufferUsageFlags usageFlags,VkMemoryPropertyFlags memoryPropertyFlags,VkBuffer& buffer,VkDeviceMemory& memory,VkDeviceSize size,void* data = nullptr,int datasize = 0);
		static uint32_t findMemoryType(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties_flag);//�ҵ��ڴ����ͺ󷵻�����
		static void copyBuffer(RHI* rhi,VkBuffer srcBuffer,VkBuffer dstBuffer,VkDeviceSize srcOffset,VkDeviceSize dstOffset,VkDeviceSize size);//����临������

		static VkImageView createImageView(VkDevice device,VkImage& image,VkFormat format,VkImageAspectFlags image_aspect_flags,VkImageViewType view_type,uint32_t layout_count,uint32_t miplevels);

		//����ͼ��
		static void createImage(VkPhysicalDevice physical_device,VkDevice device,uint32_t image_width,uint32_t image_height,VkFormat format,VkImageTiling image_tiling,VkImageUsageFlags image_usage_flags,VkMemoryPropertyFlags memory_property_flags,VkImage& image,VkDeviceMemory& memory,VkImageCreateFlags image_create_flags,uint32_t array_layers,uint32_t mip_levels);
		static void transitionImageLayout(RHI* rhi,VkImage image,VkImageLayout old_layout,VkImageLayout new_layout,uint32_t layer_count,uint32_t miplevels,VkImageAspectFlags aspect_mask_bits);//ͼ�񲼾ֱ任
		static void copyBufferToImage(RHI* rhi,VkBuffer buffer,VkImage image,uint32_t width,uint32_t height,uint32_t layer_count);//���ƻ��嵽ͼ��
		static void createGlobalImage(RHI* rhi,VkImage& image,VkImageView& image_view,VmaAllocation& image_allocation,uint32_t texture_image_width,uint32_t texture_image_height,void* texture_image_pixels,VkFormat texture_image_format,uint32_t miplevels = 0);
		static void createCubeMap(RHI* rhi, VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels);
		static void generateTextureMipMaps(RHI* rhi, VkImage  image, VkFormat image_format, uint32_t texture_width, uint32_t texture_height, uint32_t layers, uint32_t miplevels);
		static void genMipmappedImage(RHI* rhi, VkImage image, uint32_t width, uint32_t height, uint32_t mip_levels);

		//������
		static VkSampler getOrCreateMipmapSampler(VkPhysicalDevice physical_device, VkDevice device, uint32_t width, uint32_t height);
		static VkSampler getOrCreateNearestSampler(VkPhysicalDevice physical_device, VkDevice device);
		static VkSampler getOrCreateLinearSampler(VkPhysicalDevice physical_device, VkDevice device);
		static void destroyMipmappedSampler(VkDevice device);
		static void destroyNearestSampler(VkDevice device);
		static void destroyLinearSampler(VkDevice device);

	private:
		static std::unordered_map<uint32_t, VkSampler> m_mipmap_sampler_map;
		static VkSampler m_nearest_sampler;
		static VkSampler m_linear_sampler;
	};
}