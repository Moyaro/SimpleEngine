#pragma once
#include "render_resource_base.h"
#include "render_common.h"

namespace SimpleEngine {

    struct IBLResource
    {
        VkImage _brdfLUT_texture_image;
        VkImageView _brdfLUT_texture_image_view;
        VkSampler _brdfLUT_texture_sampler{nullptr};
        VmaAllocation _brdfLUT_texture_image_allocation;

        VkImage _irradiance_texture_image;
        VkImageView _irradiance_texture_image_view;
        VkSampler _irradiance_texture_sampler{ nullptr };
        VmaAllocation _irradiance_texture_image_allocation;

        VkImage _specular_texture_image;
        VkImageView _specular_texture_image_view;
        VkSampler _specular_texture_sampler{ nullptr };
        VmaAllocation _specular_texture_image_allocation;
    };

    struct IBLResourceData
    {
        void* _brdfLUT_texture_image_pixels;
        uint32_t             _brdfLUT_texture_image_width;
        uint32_t             _brdfLUT_texture_image_height;
        VkFormat   _brdfLUT_texture_image_format;
        std::array<void*, 6> _irradiance_texture_image_pixels;
        uint32_t             _irradiance_texture_image_width;
        uint32_t             _irradiance_texture_image_height;
        VkFormat   _irradiance_texture_image_format;
        std::array<void*, 6> _specular_texture_image_pixels;
        uint32_t             _specular_texture_image_width;
        uint32_t             _specular_texture_image_height;
        VkFormat   _specular_texture_image_format;
    };

    struct StorageBuffer
    {
        // limits
        uint32_t _min_uniform_buffer_offset_alignment{ 256 };
        uint32_t _min_storage_buffer_offset_alignment{ 256 };
        uint32_t _max_storage_buffer_range{ 1 << 27 };
        uint32_t _non_coherent_atom_size{ 256 };

        VkBuffer _global_upload_ringbuffer;
        VkDeviceMemory _global_upload_ringbuffer_memory;
        void* _global_upload_ringbuffer_memory_pointer;
        std::vector<uint32_t> _global_upload_ringbuffers_begin;
        std::vector<uint32_t> _global_upload_ringbuffers_end;
        std::vector<uint32_t> _global_upload_ringbuffers_size;

        VkBuffer _global_null_descriptor_storage_buffer;
        VkDeviceMemory _global_null_descriptor_storage_buffer_memory;

        // axis
        VkBuffer _axis_inefficient_storage_buffer;
        VkDeviceMemory _axis_inefficient_storage_buffer_memory;
        void* _axis_inefficient_storage_buffer_memory_pointer;
    };

	struct GlobalRenderResource
	{
		IBLResource          _ibl_resource;
		StorageBuffer        _storage_buffer;
	};

	class RenderResource : public RenderResourceBase
	{
	public:
		RenderResource() {}
		~RenderResource(){}
		void clear() override{}

		virtual void updatePerFrameBuffer(std::shared_ptr<RenderScene> render_scene,std::shared_ptr<RenderCamera> camera) override;

		virtual void uploadGlobalRenderResource(std::shared_ptr<RHI> rhi,LevelResourceDesc level_resource_desc) override;

		//加载go渲染资源
		virtual void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMeshData mesh_data,RenderMaterialData material_data) override;
		virtual void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMeshData mesh_data) override;
		virtual void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMaterialData material_data) override;



		//网格、材质的缓存
		std::map<size_t, VulkanMesh>        m_vulkan_meshes;
		std::map<size_t, VulkanPBRMaterial> m_vulkan_pbr_materials;

        VulkanMesh& getEntityMesh(RenderEntity entity);
        VulkanPBRMaterial& getEntityMaterial(RenderEntity entity);
        void resetRingBufferOffset(uint8_t current_frame_index);

		// descriptor set layout in main camera pass will be used when uploading resource
	    VkDescriptorSetLayout* m_mesh_descriptor_set_layout;
		VkDescriptorSetLayout* m_material_descriptor_set_layout;

		GlobalRenderResource m_global_render_resource;

		MeshPerframeStorageBufferObject  m_mesh_perframe_storage_buffer_object;
        MeshInefficientPickPerframeStorageBufferObject m_mesh_inefficient_pick_perframe_storage_buffer_object;
        AxisStorageBufferObject m_axis_storage_buffer_object;
        MeshPointLightShadowPerframeStorageBufferObject m_mesh_point_light_shadow_perframe_storage_buffer_object;
        MeshDirectionalLightShadowPerframeStorageBufferObject m_mesh_directional_light_shadow_perframe_storage_buffer_object;
	private:
        void createAndMapStorageBuffer(std::shared_ptr<RHI> rhi);
        void createIBLSamplers(std::shared_ptr<RHI> rhi);
        void createIBLTextures(std::shared_ptr<RHI> rhi,std::array<std::shared_ptr<TextureData>, 6> irradiance_maps,std::array<std::shared_ptr<TextureData>, 6> specular_maps);

        //获取/创建网格、材质
        VulkanMesh& getOrCreateVulkanMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data);
        VulkanPBRMaterial& getOrCreateVulkanMaterial(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMaterialData material_data);

		void updateVertexBuffer(std::shared_ptr<RHI> rhi, uint32_t vertex_buffer_size, struct MeshVertexDataDefinition const* vertex_buffer_data, uint32_t index_buffer_size, uint16_t* index_buffer_data, VulkanMesh& now_mesh);
		void updateIndexBuffer(std::shared_ptr<RHI> rhi,uint32_t index_buffer_size,void* index_buffer_data,VulkanMesh& now_mesh);
		void updateMeshData(std::shared_ptr<RHI> rhi,uint32_t index_buffer_size,void* index_buffer_data,uint32_t vertex_buffer_size,struct MeshVertexDataDefinition const* vertex_buffer_data,VulkanMesh& now_mesh);

        void updateTextureImageData(std::shared_ptr<RHI> rhi, const TextureDataToUpdate& texture_data);//更新纹理数据,创建新的图像
	};
}