#pragma once

#include "runtime/function/render/render_type.h"
#include <optional>
namespace SimpleEngine
{
    /////////////////////////////////////////////////
    #define Vk_DELETE_PTR(x) delete x; x = nullptr;

    
    ////////////////////struct declaration////////////////////////
    struct MemoryBarrier {
        VkStructureType sType;
        const void* pNext;
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
    };

    struct CopyDescriptorSet {
        VkStructureType sType;
        const void* pNext;
        VkDescriptorSet* srcSet;
        uint32_t srcBinding;
        uint32_t srcArrayElement;
        VkDescriptorSet* dstSet;
        uint32_t dstBinding;
        uint32_t dstArrayElement;
        uint32_t descriptorCount;
    };

    struct DescriptorImageInfo {
        VkSampler* sampler;
        VkImageView* imageView;
        VkImageLayout imageLayout;
    };

    struct DescriptorBufferInfo {
        VkBuffer* buffer;
        VkDeviceSize offset;
        VkDeviceSize range;
    };

    struct Offset2D {
        int32_t x;
        int32_t y;
    };

    struct SpecializationMapEntry {
        uint32_t constantID;
        uint32_t offset;
        size_t size;
    };

    struct BufferMemoryBarrier {
        VkStructureType sType;
        const void* pNext;
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
        uint32_t srcQueueFamilyIndex;
        uint32_t dstQueueFamilyIndex;
        VkBuffer* buffer;
        VkDeviceSize offset;
        VkDeviceSize size;
    };

    struct ImageSubresourceRange {
        VkImageAspectFlags aspectMask;
        uint32_t baseMipLevel;
        uint32_t levelCount;
        uint32_t baseArrayLayer;
        uint32_t layerCount;
    };

    struct ImageMemoryBarrier {
        VkStructureType sType;
        const void* pNext;
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
        VkImageLayout oldLayout;
        VkImageLayout newLayout;
        uint32_t  srcQueueFamilyIndex;
        uint32_t  dstQueueFamilyIndex;
        VkImage* image;
        VkImageSubresourceRange subresourceRange;
    };

    struct Extent2D {
        uint32_t width;
        uint32_t height;
    };

    struct Extent3D {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
    };

    struct ApplicationInfo
    {
        VkStructureType sType;
        const void* pNext;
        const char* pApplicationName;
        uint32_t applicationVersion;
        const char* pEngineName;
        uint32_t engineVersion;
        uint32_t apiVersion;
    };

    struct AttachmentDescription
    {
        VkAttachmentDescriptionFlags flags;
        VkFormat format;
        VkSampleCountFlagBits samples;
        VkAttachmentLoadOp loadOp;
        VkAttachmentStoreOp storeOp;
        VkAttachmentLoadOp stencilLoadOp;
        VkAttachmentStoreOp stencilStoreOp;
        VkImageLayout initialLayout;
        VkImageLayout finalLayout;
    };

    struct BufferCopy
    {
        VkDeviceSize srcOffset;
        VkDeviceSize dstOffset;
        VkDeviceSize size;
    };

    struct BufferCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkBufferCreateFlags flags;
        VkDeviceSize size;
        VkBufferUsageFlags usage;
        VkSharingMode sharingMode;
        uint32_t queueFamilyIndexCount;
        const uint32_t* pQueueFamilyIndices;
    };

    struct Offset3D
    {
        int32_t x;
        int32_t y;
        int32_t z;
    };

    struct ImageSubresourceLayers
    {
        VkImageAspectFlags aspectMask;
        uint32_t mipLevel;
        uint32_t baseArrayLayer;
        uint32_t layerCount;
    };

    struct BufferImageCopy
    {
        VkDeviceSize bufferOffset;
        uint32_t bufferRowLength;
        uint32_t bufferImageHeight;
        VkImageSubresourceLayers imageSubresource;
        VkOffset3D imageOffset;
        VkExtent3D imageExtent;
    };

    struct CommandBufferAllocateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkCommandPool* commandPool;
        VkCommandBufferLevel level;
        uint32_t commandBufferCount;
    };

    struct CommandBufferBeginInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkCommandBufferUsageFlags flags;
        const VkCommandBufferInheritanceInfo* pInheritanceInfo;
    };

    struct CommandBufferInheritanceInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkRenderPass* renderPass;
        uint32_t subpass;
        VkFramebuffer* framebuffer;
        VkBool32 occlusionQueryEnable;
        VkQueryControlFlags queryFlags;
        VkQueryPipelineStatisticFlags pipelineStatistics;
    };

    struct CommandPoolCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkCommandPoolCreateFlags flags;
        uint32_t queueFamilyIndex;
    };

    struct DescriptorPoolSize
    {
        VkDescriptorType type;
        uint32_t descriptorCount;
    };

    struct DescriptorPoolCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDescriptorPoolCreateFlags flags;
        uint32_t maxSets;
        uint32_t poolSizeCount;
        const VkDescriptorPoolSize* pPoolSizes;
    };

    struct DescriptorSetAllocateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDescriptorPool* descriptorPool;
        uint32_t descriptorSetCount;
        const VkDescriptorSetLayout* const* pSetLayouts;
    };

    struct DescriptorSetLayoutBinding
    {
        uint32_t binding;
        VkDescriptorType descriptorType;
        uint32_t descriptorCount;
        VkShaderStageFlags stageFlags;
        VkSampler* const* pImmutableSamplers = nullptr;
    };

    struct DescriptorSetLayoutCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDescriptorSetLayoutCreateFlags flags;
        uint32_t bindingCount;
        const VkDescriptorSetLayoutBinding* pBindings;
    };

    struct DeviceCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDeviceCreateFlags flags;
        uint32_t queueCreateInfoCount;
        const VkDeviceQueueCreateInfo** pQueueCreateInfos;
        uint32_t enabledLayerCount;
        const char* const* ppEnabledLayerNames;
        uint32_t enabledExtensionCount;
        const char* const* ppEnabledExtensionNames;
        const VkPhysicalDeviceFeatures** pEnabledFeatures;
    };

    struct DeviceQueueCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDeviceQueueCreateFlags flags;
        uint32_t queueFamilyIndex;
        uint32_t queueCount;
        const float* pQueuePriorities;
    };

    struct ExtensionProperties
    {
        char extensionName[VK_MAX_EXTENSION_NAME_SIZE];
        uint32_t specVersion;
    };

    struct FenceCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkFenceCreateFlags flags;
    };

    struct FormatProperties
    {
        VkFormatFeatureFlags linearTilingFeatures;
        VkFormatFeatureFlags optimalTilingFeatures;
        VkFormatFeatureFlags bufferFeatures;
    };

    struct FramebufferCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkFramebufferCreateFlags flags;
        VkRenderPass* renderPass;
        uint32_t attachmentCount;
        VkImageView* const* pAttachments;
        uint32_t width;
        uint32_t height;
        uint32_t layers;
    };

    struct GraphicsPipelineCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineCreateFlags flags;
        uint32_t stageCount;
        const VkPipelineShaderStageCreateInfo* pStages;
        const VkPipelineVertexInputStateCreateInfo* pVertexInputState;
        const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState;
        const VkPipelineTessellationStateCreateInfo* pTessellationState;
        const VkPipelineViewportStateCreateInfo* pViewportState;
        const VkPipelineRasterizationStateCreateInfo* pRasterizationState;
        const VkPipelineMultisampleStateCreateInfo* pMultisampleState;
        const VkPipelineDepthStencilStateCreateInfo* pDepthStencilState;
        const VkPipelineColorBlendStateCreateInfo* pColorBlendState;
        const VkPipelineDynamicStateCreateInfo* pDynamicState;
        VkPipelineLayout* layout;
        VkRenderPass* renderPass;
        uint32_t subpass;
        VkPipeline* basePipelineHandle;
        int32_t basePipelineIndex;
    };

    struct ComputePipelineCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineCreateFlags flags;
        VkPipelineShaderStageCreateInfo* pStages;
        VkPipelineLayout* layout;
        VkPipeline* basePipelineHandle;
        int32_t basePipelineIndex;
    };

    struct ImageBlit
    {
        VkImageSubresourceLayers srcSubresource;
        VkOffset3D srcOffsets[2];
        VkImageSubresourceLayers dstSubresource;
        VkOffset3D dstOffsets[2];
    };

    struct ImageCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkImageCreateFlags flags;
        VkImageType imageType;
        VkFormat format;
        VkExtent3D extent;
        uint32_t mipLevels;
        uint32_t arrayLayers;
        VkSampleCountFlagBits samples;
        VkImageTiling tiling;
        VkImageUsageFlags usage;
        VkSharingMode sharingMode;
        uint32_t queueFamilyIndexCount;
        const uint32_t* pQueueFamilyIndices;
        VkImageLayout initialLayout;
    };

    struct ImageFormatProperties
    {
        VkExtent3D maxExtent;
        uint32_t maxMipLevels;
        uint32_t maxArrayLayers;
        VkSampleCountFlags sampleCounts;
        VkDeviceSize maxResourceSize;
    };

    struct ComponentMapping
    {
        VkComponentSwizzle r;
        VkComponentSwizzle g;
        VkComponentSwizzle b;
        VkComponentSwizzle a;
    };

    struct ImageViewCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkImageViewCreateFlags flags;
        VkImage* image;
        VkImageViewType viewType;
        VkFormat format;
        VkComponentMapping components;
        VkImageSubresourceRange subresourceRange;
    };

    struct InstanceCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkInstanceCreateFlags flags;
        const VkApplicationInfo** pApplicationInfo;
        uint32_t enabledLayerCount;
        const char* const* ppEnabledLayerNames;
        uint32_t enabledExtensionCount;
        const char* const* ppEnabledExtensionNames;
    };

    struct LayerProperties
    {
        char layerName[VK_MAX_EXTENSION_NAME_SIZE];
        uint32_t specVersion;
        uint32_t implementationVersion;
        char description[VK_MAX_DESCRIPTION_SIZE];
    };

    struct MemoryAllocateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkDeviceSize allocationSize;
        uint32_t memoryTypeIndex;
    };

    struct MemoryHeap
    {
        VkDeviceSize size;
        VkMemoryHeapFlags flags;
    };

    struct MemoryRequirements
    {
        VkDeviceSize size;
        VkDeviceSize alignment;
        uint32_t memoryTypeBits;
    };

    struct MemoryType
    {
        VkMemoryPropertyFlags propertyFlags;
        uint32_t heapIndex;
    };

    struct PhysicalDeviceMemoryProperties
    {
        uint32_t memoryTypeCount;
        VkMemoryType memoryTypes[VK_MAX_MEMORY_TYPES];
        uint32_t memoryHeapCount;
        VkMemoryHeap memoryHeaps[VK_MAX_MEMORY_HEAPS];
    };

    struct PhysicalDeviceSparseProperties
    {
        VkBool32 residencyStandard2DBlockShape;
        VkBool32 residencyStandard2DMultisampleBlockShape;
        VkBool32 residencyStandard3DBlockShape;
        VkBool32 residencyAlignedMipSize;
        VkBool32 residencyNonResidentStrict;
    };

    struct PhysicalDeviceProperties
    {
        uint32_t apiVersion;
        uint32_t driverVersion;
        uint32_t vendorID;
        uint32_t deviceID;
        VkPhysicalDeviceType deviceType;
        char deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
        uint8_t pipelineCacheUUID[VK_UUID_SIZE];
        VkPhysicalDeviceLimits limits;
        VkPhysicalDeviceSparseProperties sparseProperties;
    };

    struct PipelineColorBlendStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineColorBlendStateCreateFlags flags;
        VkBool32 logicOpEnable;
        VkLogicOp logicOp;
        uint32_t attachmentCount;
        const VkPipelineColorBlendAttachmentState* pAttachments;
        float blendConstants[4];
    };

    struct StencilOpState
    {
        VkStencilOp failOp;
        VkStencilOp passOp;
        VkStencilOp depthFailOp;
        VkCompareOp compareOp;
        uint32_t compareMask;
        uint32_t writeMask;
        uint32_t reference;
    };

    struct PipelineDepthStencilStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineDepthStencilStateCreateFlags flags;
        VkBool32 depthTestEnable;
        VkBool32 depthWriteEnable;
        VkCompareOp depthCompareOp;
        VkBool32 depthBoundsTestEnable;
        VkBool32 stencilTestEnable;
        VkStencilOpState front;
        VkStencilOpState back;
        float minDepthBounds;
        float maxDepthBounds;
    };

    struct PipelineDynamicStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineDynamicStateCreateFlags flags;
        uint32_t dynamicStateCount;
        const VkDynamicState* pDynamicStates;
    };

    struct PipelineInputAssemblyStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineInputAssemblyStateCreateFlags flags;
        VkPrimitiveTopology topology;
        VkBool32 primitiveRestartEnable;
    };

    struct PipelineLayoutCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineLayoutCreateFlags flags;
        uint32_t setLayoutCount;
        VkDescriptorSetLayout* const* pSetLayouts;
        uint32_t pushConstantRangeCount;
        const VkPushConstantRange* pPushConstantRanges;
    };

    struct PipelineMultisampleStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineMultisampleStateCreateFlags flags;
        VkSampleCountFlagBits rasterizationSamples;
        VkBool32 sampleShadingEnable;
        float minSampleShading;
        const VkSampleMask** pSampleMask;
        VkBool32 alphaToCoverageEnable;
        VkBool32 alphaToOneEnable;
    };

    struct PipelineRasterizationStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineRasterizationStateCreateFlags flags;
        VkBool32 depthClampEnable;
        VkBool32 rasterizerDiscardEnable;
        VkPolygonMode polygonMode;
        VkCullModeFlags cullMode;
        VkFrontFace frontFace;
        VkBool32 depthBiasEnable;
        float depthBiasConstantFactor;
        float depthBiasClamp;
        float depthBiasSlopeFactor;
        float lineWidth;
    };

    struct PipelineShaderStageCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineShaderStageCreateFlags flags;
        VkShaderStageFlagBits stage;
        VkShaderModule module;
        const char* pName;
        const VkSpecializationInfo* pSpecializationInfo;
    };

    struct PipelineTessellationStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineTessellationStateCreateFlags flags;
        uint32_t patchControlPoints;
    };

    struct PipelineVertexInputStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineVertexInputStateCreateFlags flags;
        uint32_t vertexBindingDescriptionCount;
        const VkVertexInputBindingDescription* pVertexBindingDescriptions;
        uint32_t vertexAttributeDescriptionCount;
        const VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
    };

    struct PipelineViewportStateCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkPipelineViewportStateCreateFlags flags;
        uint32_t viewportCount;
        const VkViewport* pViewports;
        uint32_t scissorCount;
        const VkRect2D* pScissors;
    };

    struct PushConstantRange
    {
        VkShaderStageFlags stageFlags;
        uint32_t offset;
        uint32_t size;
    };

    struct QueueFamilyProperties
    {
        VkQueueFlags queueFlags;
        uint32_t queueCount;
        uint32_t timestampValidBits;
        VkExtent3D minImageTransferGranularity;
    };

    struct RenderPassCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkRenderPassCreateFlags flags;
        uint32_t attachmentCount;
        const VkAttachmentDescription* pAttachments;
        uint32_t subpassCount;
        const VkSubpassDescription* pSubpasses;
        uint32_t dependencyCount;
        const VkSubpassDependency* pDependencies;
    };

    struct SamplerCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkSamplerCreateFlags flags;
        VkFilter magFilter;
        VkFilter minFilter;
        VkSamplerMipmapMode mipmapMode;
        VkSamplerAddressMode addressModeU;
        VkSamplerAddressMode addressModeV;
        VkSamplerAddressMode addressModeW;
        float mipLodBias;
        VkBool32 anisotropyEnable;
        float maxAnisotropy;
        VkBool32 compareEnable;
        VkCompareOp compareOp;
        float minLod;
        float maxLod;
        VkBorderColor borderColor;
        VkBool32 unnormalizedCoordinates;
    };

    struct SemaphoreCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkSemaphoreCreateFlags flags;
    };

    struct ShaderModuleCreateInfo
    {
        VkStructureType sType;
        const void* pNext;
        VkShaderModuleCreateFlags flags;
        size_t codeSize;
        const uint32_t* pCode;
    };

    struct SubmitInfo
    {
        VkStructureType sType;
        const void* pNext;
        uint32_t waitSemaphoreCount;
        VkSemaphore** pWaitSemaphores;
        const VkPipelineStageFlags* pWaitDstStageMask;
        uint32_t commandBufferCount;
        VkCommandBuffer* const* pCommandBuffers;
        uint32_t signalSemaphoreCount;
        const VkSemaphore** pSignalSemaphores;
    };

    struct SubpassDependency
    {
        uint32_t srcSubpass;
        uint32_t dstSubpass;
        VkPipelineStageFlags srcStageMask;
        VkPipelineStageFlags dstStageMask;
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
        VkDependencyFlags dependencyFlags;
    };

    struct SubpassDescription
    {
        VkSubpassDescriptionFlags flags;
        VkPipelineBindPoint pipelineBindPoint;
        uint32_t inputAttachmentCount;
        const VkAttachmentReference* pInputAttachments;
        uint32_t colorAttachmentCount;
        const VkAttachmentReference* pColorAttachments;
        const VkAttachmentReference* pResolveAttachments;
        const VkAttachmentReference* pDepthStencilAttachment;
        uint32_t preserveAttachmentCount;
        const uint32_t* pPreserveAttachments;
    };

    struct WriteDescriptorSet
    {
        VkStructureType sType;
        const void* pNext;
        VkDescriptorSet* dstSet;
        uint32_t dstBinding;
        uint32_t dstArrayElement;
        uint32_t descriptorCount;
        VkDescriptorType descriptorType;
        VkDescriptorImageInfo* pImageInfo = nullptr;
        VkDescriptorBufferInfo* pBufferInfo = nullptr;
        VkBufferView* pTexelBufferView = nullptr;
    };

    struct AttachmentReference
    {
        uint32_t attachment;
        VkImageLayout layout;
    };

    struct PipelineColorBlendAttachmentState
    {
        VkBool32 blendEnable;
        VkBlendFactor srcColorBlendFactor;
        VkBlendFactor dstColorBlendFactor;
        VkBlendOp colorBlendOp;
        VkBlendFactor srcAlphaBlendFactor;
        VkBlendFactor dstAlphaBlendFactor;
        VkBlendOp alphaBlendOp;
        VkColorComponentFlags colorWriteMask;
    };

    struct Rect2D
    {
        VkOffset2D offset;
        VkExtent2D extent;
    };

    struct SpecializationInfo
    {
        uint32_t mapEntryCount;
        const VkSpecializationMapEntry** pMapEntries;
        size_t dataSize;
        const void* pData;
    };

    struct Viewport
    {
        float x;
        float y;
        float width;
        float height;
        float minDepth;
        float maxDepth;
    };

    struct RenderPassBeginInfo {
        VkStructureType sType;
        const void* pNext;
        VkRenderPass* renderPass;
        VkFramebuffer* framebuffer;
        VkRect2D renderArea;
        uint32_t clearValueCount;
        const VkClearValue* pClearValues;
    };

    struct ClearDepthStencilValue {
        float depth;
        uint32_t stencil;
    };

    union ClearColorValue {
        float float32[4];
        int32_t int32[4];
        uint32_t uint32[4];
    };

    union ClearValue {
        VkClearColorValue color;
        VkClearDepthStencilValue depthStencil;
    };

    struct ClearRect {
        VkRect2D rect;
        uint32_t baseArrayLayer;
        uint32_t layerCount;
    };

    struct ClearAttachment {
        VkImageAspectFlags aspectMask;
        uint32_t colorAttachment;
        VkClearValue clearValue;
    };

    struct SwapChainDesc
    {
        VkExtent2D extent;
        VkFormat   image_format;
        VkViewport *viewport;
        VkRect2D *scissor;
        std::vector<VkImageView> imageViews;
    };

    struct DepthImageDesc
    {
        VkImage depth_image = VK_NULL_HANDLE;
        VkImageView depth_image_view = VK_NULL_HANDLE;
        VkFormat        depth_image_format;
    };

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;
        std::optional<uint32_t> compute_family;

        bool isComplete() { return graphics_family.has_value() && present_family.has_value() && compute_family.has_value(); }//ÐÞ¸Ä¹ý
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR        capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   presentModes;
    };
}