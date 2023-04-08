#include "vulkan_util.h"
#include "vulkan_rhi.h"
#include <iostream>
#include "core/base/macro.h"

namespace SimpleEngine {
    std::unordered_map<uint32_t, VkSampler> VulkanUtil::m_mipmap_sampler_map;
    VkSampler VulkanUtil::m_nearest_sampler = VK_NULL_HANDLE;
    VkSampler VulkanUtil::m_linear_sampler = VK_NULL_HANDLE;

	VkShaderModule VulkanUtil::createShaderModule(VkDevice device,const std::vector<unsigned char>& code) {
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shader_module;
		if (vkCreateShaderModule(device, &createInfo, nullptr, &shader_module) != VK_SUCCESS) {
			return VK_NULL_HANDLE;
		}
		return shader_module;
	}

    VkImageView VulkanUtil::createImageView(VkDevice device, VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels) {
        VkImageViewCreateInfo image_view_create_info{};
        image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.image = image;
        image_view_create_info.viewType = view_type;//ͼ������
        image_view_create_info.format = format;//ͼ���ʽ

        //ͼ����;���Ĳ��ֿɷ���
        image_view_create_info.subresourceRange.aspectMask = image_aspect_flags;//ʹ��Ŀ��
        image_view_create_info.subresourceRange.baseMipLevel = 0;
        image_view_create_info.subresourceRange.levelCount = miplevels;
        image_view_create_info.subresourceRange.baseArrayLayer = 0;
        image_view_create_info.subresourceRange.layerCount = layout_count;

        //����ͼ����ͼ
        VkImageView image_view;
        if (vkCreateImageView(device, &image_view_create_info, nullptr, &image_view) != VK_SUCCESS)
        {
            throw std::runtime_error("����ͼ����ͼʧ�ܣ�");
        }

        return image_view;
    }


    void VulkanUtil::createBuffer(VkPhysicalDevice physical_device,VkDevice device,VkDeviceSize size,VkBufferUsageFlags usage,VkMemoryPropertyFlags properties,VkBuffer& buffer,VkDeviceMemory& buffer_memory)
    {
        //��������
        VkBufferCreateInfo buffer_create_info{};
        buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_create_info.size = size;//�������ֽڴ�С
        buffer_create_info.usage = usage;//ʹ��Ŀ�ģ�����/����/�ݴ滺��
        buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE; //�������������

        if (vkCreateBuffer(device, &buffer_create_info, nullptr, &buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("��������ʧ�ܣ�");
            return;
        }

        //���仺���ڴ棺���С������
        VkMemoryRequirements buffer_memory_requirements;
        vkGetBufferMemoryRequirements(device, buffer, &buffer_memory_requirements);//��ȡ�����ڴ�����
                                                                     //size����Ҫ���ڴ��С��alignment�������ڱ�������ڴ��еĿ�ʼλ�ã�memoryTypeBIts���ڴ�����λ��

        VkMemoryAllocateInfo buffer_memory_allocate_info{};
        buffer_memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        buffer_memory_allocate_info.allocationSize = buffer_memory_requirements.size;
        buffer_memory_allocate_info.memoryTypeIndex = VulkanUtil::findMemoryType(physical_device, buffer_memory_requirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &buffer_memory_allocate_info, nullptr, &buffer_memory) != VK_SUCCESS)
        {
            throw std::runtime_error("����������ڴ�ʧ�ܣ�");
            return;
        }

        //���������ڴ�ͻ������
        vkBindBufferMemory(device, buffer, buffer_memory, 0); //ƫ������0
    }

    void VulkanUtil::createBufferAndInitialize(VkDevice device, VkPhysicalDevice physicalDevice, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkBuffer& buffer, VkDeviceMemory& memory, VkDeviceSize size, void* data, int datasize){
        //��������
        VkBufferCreateInfo buffer_memory_allocate_info{};
        buffer_memory_allocate_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_memory_allocate_info.usage = usageFlags;
        buffer_memory_allocate_info.size = size;
        buffer_memory_allocate_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        if (vkCreateBuffer(device, &buffer_memory_allocate_info, nullptr, &buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("��������ʧ�ܣ�");
            return;
        }

        //���������ڴ�
        VkMemoryRequirements memReqs;
        vkGetBufferMemoryRequirements(device, buffer, &memReqs);
        VkMemoryAllocateInfo memAlloc{};
        memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = VulkanUtil::findMemoryType(physicalDevice, memReqs.memoryTypeBits, memoryPropertyFlags);
        if (vkAllocateMemory(device, &memAlloc, nullptr, &memory) != VK_SUCCESS )
        {
            throw std::runtime_error("����������ڴ�ʧ�ܣ�");
            return;
        }

        //�ѻ����ڴ�ӳ�䵽CPU�ɷ��ʵ��ڴ�
        if (data != nullptr && datasize != 0)//������ݲ�Ϊ��
        {
            void* mapped;
            if (vkMapMemory(device, memory, 0, size, 0, &mapped) != VK_SUCCESS)//ƫ��������С�����
            {
                throw std::runtime_error("ӳ�仺���ڴ�ʧ�ܣ�");
                return;
            }
            memcpy(mapped, data, datasize);//���������ݸ��Ƶ�ӳ�����ڴ�
            vkUnmapMemory(device, memory);//�����ڴ�ӳ��
        }

        //���������ڴ�ͻ������
        vkBindBufferMemory(device, buffer, memory, 0);
    }

    uint32_t VulkanUtil::findMemoryType(VkPhysicalDevice physical_device,uint32_t type_filter,VkMemoryPropertyFlags properties_flag){
        //�����豸�����ڴ�����
        VkPhysicalDeviceMemoryProperties physical_device_memory_properties;
        vkGetPhysicalDeviceMemoryProperties(physical_device, &physical_device_memory_properties);

        //�һ�����õ��ڴ�����
        for (uint32_t i = 0; i < physical_device_memory_properties.memoryTypeCount; i++)
        {
            //�ڴ���������� �� ��������Ҫ��
            if (type_filter & (1 << i) && (physical_device_memory_properties.memoryTypes[i].propertyFlags & properties_flag) == properties_flag)
            {
                return i;
            }
        }
        throw std::runtime_error("δ�ҵ������ڴ����ͣ�");
        return 0;
    }

    void VulkanUtil::copyBuffer(RHI* rhi, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size) {
        if (rhi == nullptr)
        {
            throw std::runtime_error("rhiΪ�գ�");
            return;
        }

        //���������������ʼ�����
        VkCommandBuffer rhi_command_buffer = rhi->beginSingleTimeCommands();

        //��������
        VkBufferCopy copyRegion = { srcOffset, dstOffset, size };//Դ����ƫ������Ŀ�Ļ���ƫ���������ݴ�С
        vkCmdCopyBuffer(rhi_command_buffer, srcBuffer, dstBuffer, 1, &copyRegion);

        //��������������ύ����壬�ȴ�������ɣ���������
        rhi->endSingleTimeCommands(rhi_command_buffer);
    }

    void VulkanUtil::createImage(VkPhysicalDevice physical_device, VkDevice device, uint32_t image_width, uint32_t image_height, VkFormat format, VkImageTiling image_tiling, VkImageUsageFlags image_usage_flags, VkMemoryPropertyFlags memory_property_flags, VkImage& image, VkDeviceMemory& memory, VkImageCreateFlags image_create_flags, uint32_t array_layers, uint32_t mip_levels) {
        //����ͼ��
        VkImageCreateInfo image_create_info{};
        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.flags = image_create_flags;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;//2άͼ��
        image_create_info.extent.width = image_width;
        image_create_info.extent.height = image_height;
        image_create_info.extent.depth = 1;//���
        image_create_info.mipLevels = mip_levels;
        image_create_info.arrayLayers = array_layers;
        image_create_info.format = format;//��ʽ
        image_create_info.tiling = image_tiling;//�Ƿ���Ҫֱ�ӷ���ͼ������
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//���ص�һ�α任��ᱻ����
        image_create_info.usage = image_usage_flags;//ͼ���ô�
        image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;//���ڶ��ز���
        image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//ֻ��һ��������ʹ��

        if (vkCreateImage(device, &image_create_info, nullptr, &image) != VK_SUCCESS){
            throw std::runtime_error("����ͼ��ʧ�ܣ�");
            return;
        }

        //����ͼ���ڴ�
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device, image, &memRequirements);
        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(physical_device, memRequirements.memoryTypeBits, memory_property_flags);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &memory) != VK_SUCCESS)
        {
            throw std::runtime_error("����ͼ���ڴ�ʧ�ܣ�");
            return;
        }
        vkBindImageMemory(device, image, memory, 0);
    }

    void VulkanUtil::transitionImageLayout(RHI* rhi, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout, uint32_t layer_count, uint32_t miplevels, VkImageAspectFlags aspect_mask_bits) {
        if (rhi == nullptr){
            throw std::runtime_error("rhiΪ�գ�");
            return;
        }
        VkCommandBuffer command_buffer = rhi->beginSingleTimeCommands();

        //ͼ���ڴ�������Ϣ
        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;//�����ж�������Ȩ����
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;//���в��ֱ任��ͼ��
        barrier.subresourceRange.aspectMask = aspect_mask_bits;//��Ӱ���ͼ��Χ

        //ϸ�ּ���
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = miplevels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = layer_count;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        //��Դ��������
        if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)//δ����==д�����ݲ���Ҫ�ȴ�
        {
            //��������
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            //���߽׶�
            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)//��ɫ����ȡ����ȴ��������д�����
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {//��Ȼ���
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;//����Ȳ���ʱ����ȡ
        }
        else if (old_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) // for generating mipmapped image
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else
        {
            throw std::runtime_error("��֧�ֵĲ��ֱ任���ͣ�");
            return;
        }

        //ָ��塢֮ǰ��֮��Ĺ��߽׶Ρ������ϱ�������������ڴ�����2�������ڴ�����2��ͼ���ڴ�����2
        vkCmdPipelineBarrier(command_buffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        rhi->endSingleTimeCommands(command_buffer);
    }

    void VulkanUtil::copyBufferToImage(RHI* rhi, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layer_count) {
        if (rhi == nullptr)
        {
            throw std::runtime_error("rhiΪ�գ�");
            return;
        }
        VkCommandBuffer command_buffer = rhi->beginSingleTimeCommands();

        VkBufferImageCopy region{};
        region.bufferOffset = 0;//Ҫ���Ƶ������ڻ����е�ƫ��λ��
        //���ݴ�ŷ�ʽ�����ڶ���
        region.bufferRowLength = 0;//0�����մ��
        region.bufferImageHeight = 0;
        //���ݱ����Ƶ�ͼ����һ����
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = layer_count;
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = { width, height, 1 };

        //4��Ŀ��ͼ��ǰʹ�õ�ͼ�񲼾�
        vkCmdCopyBufferToImage(command_buffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        rhi->endSingleTimeCommands(command_buffer);
    }

    void VulkanUtil::createGlobalImage(RHI* rhi, VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, void* texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) {
        if (!texture_image_pixels){
            return;
        }

        //����ͼ���ʽ��������ֽڴ�С
        VkDeviceSize texture_byte_size;
        if (texture_image_format == VK_FORMAT_R8G8B8_UNORM || texture_image_format == VK_FORMAT_R8G8B8_SRGB)
            texture_byte_size = texture_image_width * texture_image_height * 3;
        else if (texture_image_format == VK_FORMAT_R8G8B8A8_UNORM || texture_image_format == VK_FORMAT_R8G8B8A8_SRGB || texture_image_format == VK_FORMAT_R32_SFLOAT)
            texture_byte_size = texture_image_width * texture_image_height * 4;
        else if (texture_image_format == VK_FORMAT_R32G32_SFLOAT) 
            texture_byte_size = texture_image_width * texture_image_height * 4 * 2;
        else if (texture_image_format == VK_FORMAT_R32G32B32_SFLOAT) 
            texture_byte_size = texture_image_width * texture_image_height * 4 * 3;
        else if (texture_image_format == VK_FORMAT_R32G32B32A32_SFLOAT) 
            texture_byte_size = texture_image_width * texture_image_height * 4 * 4;
        else 
            throw std::runtime_error("�����ڵ�ͼ���ʽ��");
        
        //�����ݴ滺�壬������������
        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        rhi->createBuffer(texture_byte_size,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,staging_buffer,staging_buffer_memory);
        void* data;
        rhi->mapMemory(staging_buffer_memory, 0, texture_byte_size, 0, &data);
        memcpy(data, texture_image_pixels, static_cast<size_t>(texture_byte_size));
        rhi->unmapMemory(staging_buffer_memory);

        uint32_t mip_levels = (miplevels != 0) ? miplevels : floor(log2(std::max(texture_image_width, texture_image_height))) + 1;

        //��vma��������ͼ��
        VkImageCreateInfo image_create_info{};
        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.flags = 0;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;
        image_create_info.extent.width = texture_image_width;
        image_create_info.extent.height = texture_image_height;
        image_create_info.extent.depth = 1;
        image_create_info.mipLevels = mip_levels;
        image_create_info.arrayLayers = 1;
        image_create_info.format = texture_image_format;
        image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;//����Ҫֱ�ӷ���ͼ������
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//���ص�һ�α任�ᱻ����
        image_create_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;//�������ݵĽ��շ��ͷ��ͷ����ɱ���ɫ������
        image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

        vmaCreateImage(static_cast<VulkanRHI*>(rhi)->m_assets_allocator,&image_create_info,&allocInfo,&image,&image_allocation,NULL);

        
        transitionImageLayout(rhi,image,VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,1,1,VK_IMAGE_ASPECT_COLOR_BIT);//�任ͼ�񲼾֣����ܴ���
        copyBufferToImage(rhi, staging_buffer, image, texture_image_width, texture_image_height, 1);//�����ݴ滺���е����ݵ�����ͼ��

        transitionImageLayout(rhi,image,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,1,1,VK_IMAGE_ASPECT_COLOR_BIT);//תΪ�������ݵ�ͼ�񲼾�

        rhi->destroyBuffer(staging_buffer);
        rhi->freeMemory(staging_buffer_memory);

        genMipmappedImage(rhi, image, texture_image_width, texture_image_height, mip_levels);

        image_view = createImageView(static_cast<VulkanRHI*>(rhi)->m_device,image,texture_image_format,VK_IMAGE_ASPECT_COLOR_BIT,VK_IMAGE_VIEW_TYPE_2D,1,mip_levels);
    }

    void VulkanUtil::genMipmappedImage(RHI* rhi, VkImage image, uint32_t width, uint32_t height, uint32_t mip_levels)
    {
        if (rhi == nullptr)
        {
            LOG_ERROR("rhi is nullptr");
            return;
        }

        VkCommandBuffer command_buffer = rhi->beginSingleTimeCommands();

        for (uint32_t i = 1; i < mip_levels; i++)
        {
            VkImageBlit imageBlit{};
            imageBlit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageBlit.srcSubresource.layerCount = 1;
            imageBlit.srcSubresource.mipLevel = i - 1;
            imageBlit.srcOffsets[1].x = std::max((int32_t)(width >> (i - 1)), 1);
            imageBlit.srcOffsets[1].y = std::max((int32_t)(height >> (i - 1)), 1);
            imageBlit.srcOffsets[1].z = 1;

            imageBlit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageBlit.dstSubresource.layerCount = 1;
            imageBlit.dstSubresource.mipLevel = i;
            imageBlit.dstOffsets[1].x = std::max((int32_t)(width >> i), 1);
            imageBlit.dstOffsets[1].y = std::max((int32_t)(height >> i), 1);
            imageBlit.dstOffsets[1].z = 1;

            VkImageSubresourceRange mipSubRange{};
            mipSubRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            mipSubRange.baseMipLevel = i;
            mipSubRange.levelCount = 1;
            mipSubRange.layerCount = 1;

            VkImageMemoryBarrier barrier{};
            barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.image = image;
            barrier.subresourceRange = mipSubRange;

            vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
            vkCmdBlitImage(command_buffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageBlit, VK_FILTER_LINEAR);

            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
        }

        VkImageSubresourceRange mipSubRange{};
        mipSubRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        mipSubRange.baseMipLevel = 0;
        mipSubRange.levelCount = mip_levels;
        mipSubRange.layerCount = 1;

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange = mipSubRange;

        vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        static_cast<VulkanRHI*>(rhi)->endSingleTimeCommands(command_buffer);
    }

    VkSampler VulkanUtil::getOrCreateNearestSampler(VkPhysicalDevice physical_device, VkDevice device)
    {
        if (m_nearest_sampler == VK_NULL_HANDLE)
        {
            VkPhysicalDeviceProperties physical_device_properties{};
            vkGetPhysicalDeviceProperties(physical_device, &physical_device_properties);

            VkSamplerCreateInfo samplerInfo{};

            samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerInfo.magFilter = VK_FILTER_NEAREST;
            samplerInfo.minFilter = VK_FILTER_NEAREST;
            
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            
            samplerInfo.anisotropyEnable = VK_FALSE;
            samplerInfo.maxAnisotropy = 1; 
            samplerInfo.compareEnable = VK_FALSE;
            samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
            samplerInfo.mipLodBias = 0.0f;
            samplerInfo.minLod = 0.0f;
            samplerInfo.maxLod = 8.0f;

            samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
            samplerInfo.unnormalizedCoordinates = VK_FALSE;

            if (vkCreateSampler(device, &samplerInfo, nullptr, &m_nearest_sampler) != VK_SUCCESS)
            {
                throw std::runtime_error("����������ʧ�ܣ�");
            }
        }

        return m_nearest_sampler;
    }

    VkSampler VulkanUtil::getOrCreateLinearSampler(VkPhysicalDevice physical_device, VkDevice device)
    {
        if (m_linear_sampler == VK_NULL_HANDLE)
        {
            VkPhysicalDeviceProperties physical_device_properties{};
            vkGetPhysicalDeviceProperties(physical_device, &physical_device_properties);

            VkSamplerCreateInfo samplerInfo{};
            samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerInfo.magFilter = VK_FILTER_LINEAR;//����Ŵ�ʱ��������
            samplerInfo.minFilter = VK_FILTER_LINEAR;//������Сʱ��������

            //ָ��Ѱַģʽ
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;//��������ͼ��Χʱʹ������ı߽�����
            samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            //�������Թ���
            samplerInfo.anisotropyEnable = VK_FALSE;
            samplerInfo.maxAnisotropy = 1; //����������ɫʹ�õ�������
            //���������趨��ֵ�Ƚϣ��ȽϽ�����ڹ���
            samplerInfo.compareEnable = VK_FALSE;
            samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
            //���÷ּ�ϸ��
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
            samplerInfo.mipLodBias = 0.0f;
            samplerInfo.minLod = 0.0f;
            samplerInfo.maxLod = 8.0f; // todo: m_irradiance_texture_miplevels

            samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;//��BORDERѰַģʽʱ����������Χ�ı߽���ɫ
            samplerInfo.unnormalizedCoordinates = VK_FALSE;//ָ������ʹ�õ�����ϵͳ

            if (vkCreateSampler(device, &samplerInfo, nullptr, &m_linear_sampler) != VK_SUCCESS)
            {
                throw std::runtime_error("����������ʧ�ܣ�");
            }
        }

        return m_linear_sampler;
    }

    VkSampler VulkanUtil::getOrCreateMipmapSampler(VkPhysicalDevice physical_device,VkDevice device,uint32_t width,uint32_t height)
    {
        if (width <= 0 || height <= 0)
        {
            throw std::runtime_error("width <= 0 || height <= 0");
        }

        VkSampler sampler;
        uint32_t  mip_levels = floor(log2(std::max(width, height))) + 1;
        auto      find_sampler = m_mipmap_sampler_map.find(mip_levels);
        if (find_sampler != m_mipmap_sampler_map.end())
        {
            return find_sampler->second;
        }
        else
        {
            VkPhysicalDeviceProperties physical_device_properties{};
            vkGetPhysicalDeviceProperties(physical_device, &physical_device_properties);

            VkSamplerCreateInfo samplerInfo{};
            samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerInfo.magFilter = VK_FILTER_LINEAR;
            samplerInfo.minFilter = VK_FILTER_LINEAR;
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = physical_device_properties.limits.maxSamplerAnisotropy;

            samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
            samplerInfo.unnormalizedCoordinates = VK_FALSE;
            samplerInfo.compareEnable = VK_FALSE;
            samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

            samplerInfo.maxLod = mip_levels - 1;

            if (vkCreateSampler(device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS)
            {
                throw std::runtime_error("����������ʧ�ܣ�");
            }
        }

        m_mipmap_sampler_map.insert(std::make_pair(mip_levels, sampler));

        return sampler;
    }

    void VulkanUtil::destroyNearestSampler(VkDevice device)
    {
        vkDestroySampler(device, m_nearest_sampler, nullptr);
        m_nearest_sampler = VK_NULL_HANDLE;
    }

    void VulkanUtil::destroyLinearSampler(VkDevice device)
    {
        vkDestroySampler(device, m_linear_sampler, nullptr);
        m_linear_sampler = VK_NULL_HANDLE;
    }

    void VulkanUtil::destroyMipmappedSampler(VkDevice device)
    {
        for (auto sampler : m_mipmap_sampler_map)
        {
            vkDestroySampler(device, sampler.second, nullptr);
        }
        m_mipmap_sampler_map.clear();
    }

    void VulkanUtil::createCubeMap(RHI* rhi, VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels)
    {
        VkDeviceSize texture_layer_byte_size;
        VkDeviceSize cube_byte_size;
        VkFormat     vulkan_image_format;
        switch (texture_image_format)
        {
        case VK_FORMAT_R8G8B8_UNORM:
            texture_layer_byte_size = texture_image_width * texture_image_height * 3;
            vulkan_image_format = VK_FORMAT_R8G8B8_UNORM;
            break;
        case VK_FORMAT_R8G8B8_SRGB:
            texture_layer_byte_size = texture_image_width * texture_image_height * 3;
            vulkan_image_format = VK_FORMAT_R8G8B8_SRGB;
            break;
        case VK_FORMAT_R8G8B8A8_UNORM:
            texture_layer_byte_size = texture_image_width * texture_image_height * 4;
            vulkan_image_format = VK_FORMAT_R8G8B8A8_UNORM;
            break;
        case VK_FORMAT_R8G8B8A8_SRGB:
            texture_layer_byte_size = texture_image_width * texture_image_height * 4;
            vulkan_image_format = VK_FORMAT_R8G8B8A8_SRGB;
            break;
        case VK_FORMAT_R32G32_SFLOAT:
            texture_layer_byte_size = texture_image_width * texture_image_height * 4 * 2;
            vulkan_image_format = VK_FORMAT_R32G32_SFLOAT;
            break;
        case VK_FORMAT_R32G32B32_SFLOAT:
            texture_layer_byte_size = texture_image_width * texture_image_height * 4 * 3;
            vulkan_image_format = VK_FORMAT_R32G32B32_SFLOAT;
            break;
        case VK_FORMAT_R32G32B32A32_SFLOAT:
            texture_layer_byte_size = texture_image_width * texture_image_height * 4 * 4;
            vulkan_image_format = VK_FORMAT_R32G32B32A32_SFLOAT;
            break;
        default:
            texture_layer_byte_size = VkDeviceSize(-1);
            LOG_ERROR("invalid texture_layer_byte_size");
            return;
            break;
        }
        cube_byte_size = texture_layer_byte_size * 6;

        // create cubemap texture image
        // use the vmaAllocator to allocate asset texture image
        VkImageCreateInfo image_create_info{};
        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;
        image_create_info.extent.width = static_cast<uint32_t>(texture_image_width);
        image_create_info.extent.height = static_cast<uint32_t>(texture_image_height);
        image_create_info.extent.depth = 1;
        image_create_info.mipLevels = miplevels;
        image_create_info.arrayLayers = 6;
        image_create_info.format = vulkan_image_format;
        image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_create_info.usage =
            VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

        vmaCreateImage(static_cast<VulkanRHI*>(rhi)->m_assets_allocator,
            &image_create_info,
            &allocInfo,
            &image,
            &image_allocation,
            NULL);

        VkBuffer       inefficient_staging_buffer;
        VkDeviceMemory inefficient_staging_buffer_memory;
        createBuffer(static_cast<VulkanRHI*>(rhi)->m_physical_device,
            static_cast<VulkanRHI*>(rhi)->m_device,
            cube_byte_size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            inefficient_staging_buffer,
            inefficient_staging_buffer_memory);

        void* data = NULL;
        vkMapMemory(
            static_cast<VulkanRHI*>(rhi)->m_device, inefficient_staging_buffer_memory, 0, cube_byte_size, 0, &data);
        for (int i = 0; i < 6; i++)
        {
            memcpy((void*)(static_cast<char*>(data) + texture_layer_byte_size * i),
                texture_image_pixels[i],
                static_cast<size_t>(texture_layer_byte_size));
        }
        vkUnmapMemory(static_cast<VulkanRHI*>(rhi)->m_device, inefficient_staging_buffer_memory);

        // layout transitions -- image layout is set from none to destination
        transitionImageLayout(rhi,
            image,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            6,
            miplevels,
            VK_IMAGE_ASPECT_COLOR_BIT);
        // copy from staging buffer as destination
        copyBufferToImage(rhi,
            inefficient_staging_buffer,
            image,
            static_cast<uint32_t>(texture_image_width),
            static_cast<uint32_t>(texture_image_height),
            6);

        vkDestroyBuffer(static_cast<VulkanRHI*>(rhi)->m_device, inefficient_staging_buffer, nullptr);
        vkFreeMemory(static_cast<VulkanRHI*>(rhi)->m_device, inefficient_staging_buffer_memory, nullptr);

        generateTextureMipMaps(
            rhi, image, vulkan_image_format, texture_image_width, texture_image_height, 6, miplevels);

        image_view = createImageView(static_cast<VulkanRHI*>(rhi)->m_device,
            image,
            vulkan_image_format,
            VK_IMAGE_ASPECT_COLOR_BIT,
            VK_IMAGE_VIEW_TYPE_CUBE,
            6,
            miplevels);
    }

    void VulkanUtil::generateTextureMipMaps(RHI* rhi,VkImage  image,VkFormat image_format,uint32_t texture_width,uint32_t texture_height,uint32_t layers,uint32_t miplevels)
    {
        VkFormatProperties format_properties;
        vkGetPhysicalDeviceFormatProperties(
            static_cast<VulkanRHI*>(rhi)->m_physical_device, image_format, &format_properties);
        if (!(format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
        {
            LOG_ERROR("generateTextureMipMaps() : linear bliting not supported!");
            return;
        }

        VkCommandBuffer command_buffer = static_cast<VulkanRHI*>(rhi)->beginSingleTimeCommands();

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = image;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = layers;
        barrier.subresourceRange.levelCount = 1; // 1 level a time

        int32_t mipwidth = texture_width;
        int32_t mipheight = texture_height;

        for (uint32_t i = 1; i < miplevels; i++) // use miplevel i-1 to generate miplevel i and set i-1 to
                                                 // shader_read
        {
            barrier.subresourceRange.baseMipLevel = i - 1;
            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            vkCmdPipelineBarrier(command_buffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                0,
                0,
                nullptr,
                0,
                nullptr,
                1,
                &barrier);

            VkImageBlit blit{};
            blit.srcOffsets[0] = { 0, 0, 0 };
            blit.srcOffsets[1] = { mipwidth, mipheight, 1 };
            blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.srcSubresource.mipLevel = i - 1;
            blit.srcSubresource.baseArrayLayer = 0;
            blit.srcSubresource.layerCount = layers; // miplevel i-1 to i for all layers

            blit.dstOffsets[0] = { 0, 0, 0 };
            blit.dstOffsets[1] = { mipwidth > 1 ? mipwidth / 2 : 1, mipheight > 1 ? mipheight / 2 : 1, 1 };
            blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.dstSubresource.mipLevel = i;
            blit.dstSubresource.baseArrayLayer = 0;
            blit.dstSubresource.layerCount = layers;

            vkCmdBlitImage(command_buffer,
                image,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                image,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1,
                &blit,
                VK_FILTER_LINEAR);

            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            vkCmdPipelineBarrier(command_buffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                0,
                0,
                nullptr,
                0,
                nullptr,
                1,
                &barrier); // for completed miplevel, change to shader_read

            if (mipwidth > 1)
                mipwidth /= 2;
            if (mipheight > 1)
                mipheight /= 2;
        }

        // the last miplevel(miplevels - 1) change to shader_read
        barrier.subresourceRange.baseMipLevel = miplevels - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(command_buffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0,
            0,
            nullptr,
            0,
            nullptr,
            1,
            &barrier);

        static_cast<VulkanRHI*>(rhi)->endSingleTimeCommands(command_buffer);
    }
}