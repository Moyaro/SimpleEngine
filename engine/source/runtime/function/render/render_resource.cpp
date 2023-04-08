#include "render_resource.h"
#include "interface/vulkan_rhi.h"
#include "render_camera.h"
#include "runtime/function/render/render_mesh.h"

namespace SimpleEngine {
    void RenderResource::uploadGlobalRenderResource(std::shared_ptr<RHI> rhi, LevelResourceDesc level_resource_desc)
    {
        // create and map global storage buffer
        createAndMapStorageBuffer(rhi);

        // sky box irradiance
        SkyBoxIrradianceMap skybox_irradiance_map = level_resource_desc.m_ibl_resource_desc.m_skybox_irradiance_map;
        std::shared_ptr<TextureData> irradiace_pos_x_map = loadTextureHDR(skybox_irradiance_map.m_positive_x_map);
        std::shared_ptr<TextureData> irradiace_neg_x_map = loadTextureHDR(skybox_irradiance_map.m_negative_x_map);
        std::shared_ptr<TextureData> irradiace_pos_y_map = loadTextureHDR(skybox_irradiance_map.m_positive_y_map);
        std::shared_ptr<TextureData> irradiace_neg_y_map = loadTextureHDR(skybox_irradiance_map.m_negative_y_map);
        std::shared_ptr<TextureData> irradiace_pos_z_map = loadTextureHDR(skybox_irradiance_map.m_positive_z_map);
        std::shared_ptr<TextureData> irradiace_neg_z_map = loadTextureHDR(skybox_irradiance_map.m_negative_z_map);

        // sky box specular
        SkyBoxSpecularMap            skybox_specular_map = level_resource_desc.m_ibl_resource_desc.m_skybox_specular_map;
        std::shared_ptr<TextureData> specular_pos_x_map = loadTextureHDR(skybox_specular_map.m_positive_x_map);
        std::shared_ptr<TextureData> specular_neg_x_map = loadTextureHDR(skybox_specular_map.m_negative_x_map);
        std::shared_ptr<TextureData> specular_pos_y_map = loadTextureHDR(skybox_specular_map.m_positive_y_map);
        std::shared_ptr<TextureData> specular_neg_y_map = loadTextureHDR(skybox_specular_map.m_negative_y_map);
        std::shared_ptr<TextureData> specular_pos_z_map = loadTextureHDR(skybox_specular_map.m_positive_z_map);
        std::shared_ptr<TextureData> specular_neg_z_map = loadTextureHDR(skybox_specular_map.m_negative_z_map);


        // brdf
        std::shared_ptr<TextureData> brdf_map = loadTextureHDR(level_resource_desc.m_ibl_resource_desc.m_brdf_map);
        // create IBL samplers
        createIBLSamplers(rhi);

        // create IBL textures, take care of the texture order
        std::array<std::shared_ptr<TextureData>, 6> irradiance_maps = { irradiace_pos_x_map,irradiace_neg_x_map,irradiace_pos_z_map,irradiace_neg_z_map,irradiace_pos_y_map,irradiace_neg_y_map };
        std::array<std::shared_ptr<TextureData>, 6> specular_maps = { specular_pos_x_map,
                                                                     specular_neg_x_map,
                                                                     specular_pos_z_map,
                                                                     specular_neg_z_map,
                                                                     specular_pos_y_map,
                                                                     specular_neg_y_map };

        createIBLTextures(rhi, irradiance_maps, specular_maps);

        
        // create brdf lut texture
        rhi->createGlobalImage(m_global_render_resource._ibl_resource._brdfLUT_texture_image,m_global_render_resource._ibl_resource._brdfLUT_texture_image_view,m_global_render_resource._ibl_resource._brdfLUT_texture_image_allocation,
            brdf_map->m_width,
            brdf_map->m_height,
            brdf_map->m_pixels,
            brdf_map->m_format);
    }

    void RenderResource::createAndMapStorageBuffer(std::shared_ptr<RHI> rhi)
    {
        VulkanRHI* raw_rhi = static_cast<VulkanRHI*>(rhi.get());
        StorageBuffer& _storage_buffer = m_global_render_resource._storage_buffer;
        uint32_t       frames_in_flight = raw_rhi->k_max_frames_in_flight;

        VkPhysicalDeviceProperties properties;
        rhi->getPhysicalDeviceProperties(&properties);

        _storage_buffer._min_uniform_buffer_offset_alignment = static_cast<uint32_t>(properties.limits.minUniformBufferOffsetAlignment);
        _storage_buffer._min_storage_buffer_offset_alignment = static_cast<uint32_t>(properties.limits.minStorageBufferOffsetAlignment);
        _storage_buffer._max_storage_buffer_range = properties.limits.maxStorageBufferRange;
        _storage_buffer._non_coherent_atom_size = properties.limits.nonCoherentAtomSize;

        // In Vulkan, the storage buffer should be pre-allocated.
        // The size is 128MB in NVIDIA D3D11
        // driver(https://developer.nvidia.com/content/constant-buffers-without-constant-pain-0).
        uint32_t global_storage_buffer_size = 1024 * 1024 * 128;
        rhi->createBuffer(global_storage_buffer_size,
            VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            _storage_buffer._global_upload_ringbuffer,
            _storage_buffer._global_upload_ringbuffer_memory);

        _storage_buffer._global_upload_ringbuffers_begin.resize(frames_in_flight);
        _storage_buffer._global_upload_ringbuffers_end.resize(frames_in_flight);
        _storage_buffer._global_upload_ringbuffers_size.resize(frames_in_flight);
        for (uint32_t i = 0; i < frames_in_flight; ++i)
        {
            _storage_buffer._global_upload_ringbuffers_begin[i] = (global_storage_buffer_size * i) / frames_in_flight;
            _storage_buffer._global_upload_ringbuffers_size[i] =
                (global_storage_buffer_size * (i + 1)) / frames_in_flight -
                (global_storage_buffer_size * i) / frames_in_flight;
        }

        // axis
        rhi->createBuffer(sizeof(AxisStorageBufferObject),
            VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            _storage_buffer._axis_inefficient_storage_buffer,
            _storage_buffer._axis_inefficient_storage_buffer_memory);

        // null descriptor
        rhi->createBuffer(64, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 0,  _storage_buffer._global_null_descriptor_storage_buffer, _storage_buffer._global_null_descriptor_storage_buffer_memory);

        // TODO: Unmap when program terminates
        rhi->mapMemory(_storage_buffer._global_upload_ringbuffer_memory,
            0,
            VK_WHOLE_SIZE,
            0,
            &_storage_buffer._global_upload_ringbuffer_memory_pointer);

        rhi->mapMemory(_storage_buffer._axis_inefficient_storage_buffer_memory,
            0,
            VK_WHOLE_SIZE,
            0,
            &_storage_buffer._axis_inefficient_storage_buffer_memory_pointer);
    }

    void RenderResource::createIBLSamplers(std::shared_ptr<RHI> rhi)
    {
        VulkanRHI* raw_rhi = static_cast<VulkanRHI*>(rhi.get());

        VkPhysicalDeviceProperties physical_device_properties{};
        rhi->getPhysicalDeviceProperties(&physical_device_properties);

        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.anisotropyEnable = VK_TRUE;                                                // close:false
        samplerInfo.maxAnisotropy = physical_device_properties.limits.maxSamplerAnisotropy; // close :1.0f
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.maxLod = 0.0f;

        if (m_global_render_resource._ibl_resource._brdfLUT_texture_sampler != VK_NULL_HANDLE)
        {
            rhi->destroySampler(m_global_render_resource._ibl_resource._brdfLUT_texture_sampler);
        }

        if (rhi->createSampler(&samplerInfo, &m_global_render_resource._ibl_resource._brdfLUT_texture_sampler) != VK_SUCCESS)
        {
            throw std::runtime_error("vk create sampler");
        }

        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = 8.0f; // TODO: irradiance_texture_miplevels
        samplerInfo.mipLodBias = 0.0f;

        if (m_global_render_resource._ibl_resource._irradiance_texture_sampler != VK_NULL_HANDLE)
        {
            rhi->destroySampler(m_global_render_resource._ibl_resource._irradiance_texture_sampler);
        }

        if (rhi->createSampler(&samplerInfo, &m_global_render_resource._ibl_resource._irradiance_texture_sampler) != VK_SUCCESS)
        {
            throw std::runtime_error("vk create sampler");
        }

        if (m_global_render_resource._ibl_resource._specular_texture_sampler != VK_NULL_HANDLE)
        {
            rhi->destroySampler(m_global_render_resource._ibl_resource._specular_texture_sampler);
        }

        if (rhi->createSampler(&samplerInfo, &m_global_render_resource._ibl_resource._specular_texture_sampler) != VK_SUCCESS)
        {
            throw std::runtime_error("vk create sampler");
        }
    }

    void RenderResource::createIBLTextures(std::shared_ptr<RHI>                        rhi,
        std::array<std::shared_ptr<TextureData>, 6> irradiance_maps,
        std::array<std::shared_ptr<TextureData>, 6> specular_maps)
    {
        // assume all textures have same width, height and format
        uint32_t irradiance_cubemap_miplevels =
            static_cast<uint32_t>(
                std::floor(log2(std::max(irradiance_maps[0]->m_width, irradiance_maps[0]->m_height)))) +
            1;
        rhi->createCubeMap(
            m_global_render_resource._ibl_resource._irradiance_texture_image,
            m_global_render_resource._ibl_resource._irradiance_texture_image_view,
            m_global_render_resource._ibl_resource._irradiance_texture_image_allocation,
            irradiance_maps[0]->m_width,
            irradiance_maps[0]->m_height,
            { irradiance_maps[0]->m_pixels,
             irradiance_maps[1]->m_pixels,
             irradiance_maps[2]->m_pixels,
             irradiance_maps[3]->m_pixels,
             irradiance_maps[4]->m_pixels,
             irradiance_maps[5]->m_pixels },
            irradiance_maps[0]->m_format,
            irradiance_cubemap_miplevels);

        uint32_t specular_cubemap_miplevels =
            static_cast<uint32_t>(
                std::floor(log2(std::max(specular_maps[0]->m_width, specular_maps[0]->m_height)))) +
            1;
        rhi->createCubeMap(
            m_global_render_resource._ibl_resource._specular_texture_image,
            m_global_render_resource._ibl_resource._specular_texture_image_view,
            m_global_render_resource._ibl_resource._specular_texture_image_allocation,
            specular_maps[0]->m_width,
            specular_maps[0]->m_height,
            { specular_maps[0]->m_pixels,
             specular_maps[1]->m_pixels,
             specular_maps[2]->m_pixels,
             specular_maps[3]->m_pixels,
             specular_maps[4]->m_pixels,
             specular_maps[5]->m_pixels },
            specular_maps[0]->m_format,
            specular_cubemap_miplevels);
    }

	void RenderResource::updateIndexBuffer(std::shared_ptr<RHI> rhi, uint32_t index_buffer_size, void* index_buffer_data, VulkanMesh& now_mesh) {
        VulkanRHI* vulkan_context = static_cast<VulkanRHI*>(rhi.get());

        //创建暂存缓冲
        VkDeviceSize buffer_size = index_buffer_size;
        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        rhi->createBuffer(buffer_size,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,staging_buffer,staging_buffer_memory);

        void* staging_buffer_data;
        rhi->mapMemory(staging_buffer_memory, 0, buffer_size, 0, &staging_buffer_data);
        memcpy(staging_buffer_data, index_buffer_data, (size_t)buffer_size);//数据存入缓冲
        rhi->unmapMemory(staging_buffer_memory);

        // 用vmaAllocator分配索引缓冲的内存
        VkBufferCreateInfo buffer_info = {};
        buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_info.size = buffer_size;
        buffer_info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        VmaAllocationCreateInfo alloc_info = {};
        alloc_info.usage = VMA_MEMORY_USAGE_GPU_ONLY;//内存只能被GPU使用

        rhi->createBufferVMA(vulkan_context->m_assets_allocator,&buffer_info,&alloc_info,&now_mesh.mesh_index_buffer,&now_mesh.mesh_index_buffer_allocation,nullptr);

        //复制暂存缓冲数据到索引缓冲
        rhi->copyBuffer(staging_buffer, now_mesh.mesh_index_buffer, 0, 0, buffer_size);

        //销毁暂存缓冲
        rhi->destroyBuffer(staging_buffer);
        rhi->freeMemory(staging_buffer_memory);
	}

    void RenderResource::updateVertexBuffer(std::shared_ptr<RHI> rhi,uint32_t vertex_buffer_size, struct MeshVertexDataDefinition const* vertex_buffer_data, uint32_t index_buffer_size, uint16_t* index_buffer_data, VulkanMesh& now_mesh) {
        VulkanRHI* vulkan_context = static_cast<VulkanRHI*>(rhi.get());
        assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));
        uint32_t vertex_count = vertex_buffer_size / sizeof(MeshVertexDataDefinition);//获取顶点数

        //获取顶点位置、变化混合、变化缓存大小
        VkDeviceSize vertex_position_buffer_size = sizeof(MeshVertex::MeshVertexPostition) * vertex_count;
        VkDeviceSize vertex_varying_enable_blending_buffer_size = sizeof(MeshVertex::VulkanMeshVertexVaryingEnableBlending) * vertex_count;
        VkDeviceSize vertex_varying_buffer_size = sizeof(MeshVertex::MeshVertexVarying) * vertex_count;

        VkDeviceSize vertex_position_buffer_offset = 0;
        VkDeviceSize vertex_varying_enable_blending_buffer_offset = vertex_position_buffer_offset + vertex_position_buffer_size;
        VkDeviceSize vertex_varying_buffer_offset = vertex_varying_enable_blending_buffer_offset + vertex_varying_enable_blending_buffer_size;

       //暂存缓冲
        VkDeviceSize staging_buffer_size = vertex_position_buffer_size + vertex_varying_enable_blending_buffer_size + vertex_varying_buffer_size;
        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        rhi->createBuffer(staging_buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,staging_buffer,staging_buffer_memory);
        void* staging_buffer_data;
        rhi->mapMemory(staging_buffer_memory,0,VK_WHOLE_SIZE,0,&staging_buffer_data);
        MeshVertex::MeshVertexPostition* mesh_vertex_positions = reinterpret_cast<MeshVertex::MeshVertexPostition*>(reinterpret_cast<uintptr_t>(staging_buffer_data) + vertex_position_buffer_offset);
        MeshVertex::VulkanMeshVertexVaryingEnableBlending* mesh_vertex_blending_varyings = reinterpret_cast<MeshVertex::VulkanMeshVertexVaryingEnableBlending*>( reinterpret_cast<uintptr_t>(staging_buffer_data) + vertex_varying_enable_blending_buffer_offset);
        MeshVertex::MeshVertexVarying* mesh_vertex_varyings = reinterpret_cast<MeshVertex::MeshVertexVarying*>(reinterpret_cast<uintptr_t>(staging_buffer_data) + vertex_varying_buffer_offset);

        for (uint32_t vertex_index = 0; vertex_index < vertex_count; ++vertex_index)
        {    
           Vector3 normal = Vector3(vertex_buffer_data[vertex_index].nx,vertex_buffer_data[vertex_index].ny,vertex_buffer_data[vertex_index].nz);
           Vector3 tangent = Vector3(vertex_buffer_data[vertex_index].tx,vertex_buffer_data[vertex_index].ty,vertex_buffer_data[vertex_index].tz);

           mesh_vertex_positions[vertex_index].position = Vector3(vertex_buffer_data[vertex_index].x,vertex_buffer_data[vertex_index].y,vertex_buffer_data[vertex_index].z);
           mesh_vertex_blending_varyings[vertex_index].normal = normal;
           mesh_vertex_blending_varyings[vertex_index].tangent = tangent;
           mesh_vertex_varyings[vertex_index].texcoord = Vector2(vertex_buffer_data[vertex_index].u, vertex_buffer_data[vertex_index].v);     
        }        

        rhi->unmapMemory(staging_buffer_memory);

            // use the vmaAllocator to allocate asset vertex buffer
        VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

        bufferInfo.size = vertex_position_buffer_size;
        rhi->createBufferVMA(vulkan_context->m_assets_allocator,&bufferInfo,&allocInfo,&now_mesh.mesh_vertex_position_buffer,&now_mesh.mesh_vertex_position_buffer_allocation,NULL);
        bufferInfo.size = vertex_varying_enable_blending_buffer_size;
        rhi->createBufferVMA(vulkan_context->m_assets_allocator, &bufferInfo, &allocInfo, &now_mesh.mesh_vertex_varying_enable_blending_buffer, &now_mesh.mesh_vertex_varying_enable_blending_buffer_allocation, NULL);
        bufferInfo.size = vertex_varying_buffer_size;
        rhi->createBufferVMA(vulkan_context->m_assets_allocator,&bufferInfo,&allocInfo,&now_mesh.mesh_vertex_varying_buffer,&now_mesh.mesh_vertex_varying_buffer_allocation,NULL);

            // use the data from staging buffer
         rhi->copyBuffer(staging_buffer,now_mesh.mesh_vertex_position_buffer,vertex_position_buffer_offset,0,vertex_position_buffer_size);
         rhi->copyBuffer(staging_buffer, now_mesh.mesh_vertex_varying_enable_blending_buffer, vertex_varying_enable_blending_buffer_offset, 0, vertex_varying_enable_blending_buffer_size);
         rhi->copyBuffer(staging_buffer,now_mesh.mesh_vertex_varying_buffer,vertex_varying_buffer_offset,0,vertex_varying_buffer_size);

         // release staging buffer
         rhi->destroyBuffer(staging_buffer);
         rhi->freeMemory(staging_buffer_memory);

         // update descriptor set
         VkDescriptorSetAllocateInfo mesh_vertex_blending_per_mesh_descriptor_set_alloc_info; 
         mesh_vertex_blending_per_mesh_descriptor_set_alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
         mesh_vertex_blending_per_mesh_descriptor_set_alloc_info.pNext = NULL;
         mesh_vertex_blending_per_mesh_descriptor_set_alloc_info.descriptorPool = vulkan_context->m_descriptor_pool;
         mesh_vertex_blending_per_mesh_descriptor_set_alloc_info.descriptorSetCount = 1;
         mesh_vertex_blending_per_mesh_descriptor_set_alloc_info.pSetLayouts = m_mesh_descriptor_set_layout;

         if (VK_SUCCESS != rhi->allocateDescriptorSets(
             &mesh_vertex_blending_per_mesh_descriptor_set_alloc_info,
             &now_mesh.mesh_vertex_blending_descriptor_set))
         {
             throw std::runtime_error("allocate mesh vertex blending per mesh descriptor set");
         }

         VkDescriptorBufferInfo mesh_vertex_Joint_binding_storage_buffer_info = {};
         mesh_vertex_Joint_binding_storage_buffer_info.offset = 0;
         mesh_vertex_Joint_binding_storage_buffer_info.range = 1;
         mesh_vertex_Joint_binding_storage_buffer_info.buffer =
             m_global_render_resource._storage_buffer._global_null_descriptor_storage_buffer;
         assert(mesh_vertex_Joint_binding_storage_buffer_info.range <
             m_global_render_resource._storage_buffer._max_storage_buffer_range);

         VkDescriptorSet descriptor_set_to_write = now_mesh.mesh_vertex_blending_descriptor_set;

         VkWriteDescriptorSet descriptor_writes[1];

         VkWriteDescriptorSet& mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info =
             descriptor_writes[0];
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.sType =
             VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.pNext = NULL;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.dstSet = descriptor_set_to_write;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.dstBinding = 0;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.dstArrayElement = 0;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.descriptorType =
             VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.descriptorCount = 1;
         mesh_vertex_blending_vertex_Joint_binding_storage_buffer_write_info.pBufferInfo =
             &mesh_vertex_Joint_binding_storage_buffer_info;

         rhi->updateDescriptorSets((sizeof(descriptor_writes) / sizeof(descriptor_writes[0])),
             descriptor_writes,
             0,
             NULL);
     }
    

    void RenderResource::updatePerFrameBuffer(std::shared_ptr<RenderScene>  render_scene, std::shared_ptr<RenderCamera> camera)
    {
        //获取投影视图矩阵
        Matrix4x4 view_matrix = camera->getViewMatrix();
        Matrix4x4 proj_matrix = camera->getPersProjMatrix();
        Vector3 camera_position = camera->position();
        Matrix4x4 proj_view_matrix = proj_matrix * view_matrix;

        // ambient light
        Vector3  ambient_light = render_scene->m_ambient_light.m_irradiance;
        uint32_t point_light_num = static_cast<uint32_t>(render_scene->m_point_light_list.m_lights.size());
        
        //存进每帧的缓冲
        m_mesh_perframe_storage_buffer_object.proj_view_matrix = proj_view_matrix;
        m_mesh_perframe_storage_buffer_object.camera_position = camera_position;
        m_mesh_perframe_storage_buffer_object.ambient_light = ambient_light;
        m_mesh_perframe_storage_buffer_object.point_light_num = point_light_num;

        m_mesh_point_light_shadow_perframe_storage_buffer_object.point_light_num = point_light_num;
        // point lights
        for (uint32_t i = 0; i < point_light_num; i++)
        {
            Vector3 point_light_position = render_scene->m_point_light_list.m_lights[i].m_position;
            Vector3 point_light_intensity =
                render_scene->m_point_light_list.m_lights[i].m_flux / (4.0f * Math_PI);

            float radius = render_scene->m_point_light_list.m_lights[i].calculateRadius();

            m_mesh_perframe_storage_buffer_object.scene_point_lights[i].position = point_light_position;
            m_mesh_perframe_storage_buffer_object.scene_point_lights[i].radius = radius;
            m_mesh_perframe_storage_buffer_object.scene_point_lights[i].intensity = point_light_intensity;

            m_mesh_point_light_shadow_perframe_storage_buffer_object.point_lights_position_and_radius[i] =
                Vector4(point_light_position, radius);
        }

        // directional light
        m_mesh_perframe_storage_buffer_object.scene_directional_light.direction =
            render_scene->m_directional_light.m_direction.normalisedCopy();
        m_mesh_perframe_storage_buffer_object.scene_directional_light.color = render_scene->m_directional_light.m_color;

        // pick pass view projection matrix
        m_mesh_inefficient_pick_perframe_storage_buffer_object.proj_view_matrix = proj_view_matrix;
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMeshData mesh_data,RenderMaterialData material_data)
    {
        getOrCreateVulkanMesh(rhi, render_entity, mesh_data);
        getOrCreateVulkanMaterial(rhi, render_entity, material_data);
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMeshData mesh_data)
    {
        getOrCreateVulkanMesh(rhi, render_entity, mesh_data);
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,RenderEntity render_entity,RenderMaterialData material_data)
    {
        getOrCreateVulkanMaterial(rhi, render_entity, material_data);
    }

    void RenderResource::updateMeshData(std::shared_ptr<RHI> rhi, uint32_t index_buffer_size, void* index_buffer_data, uint32_t vertex_buffer_size, struct MeshVertexDataDefinition const* vertex_buffer_data, VulkanMesh& now_mesh) {
        assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));
        now_mesh.mesh_vertex_count = vertex_buffer_size / sizeof(MeshVertexDataDefinition);
        updateVertexBuffer(rhi,vertex_buffer_size,vertex_buffer_data,index_buffer_size,reinterpret_cast<uint16_t*>(index_buffer_data),now_mesh);
        assert(0 == (index_buffer_size % sizeof(uint16_t)));
        now_mesh.mesh_index_count = index_buffer_size / sizeof(uint16_t);
        updateIndexBuffer(rhi, index_buffer_size, index_buffer_data, now_mesh);
    }

    VulkanMesh& RenderResource::getOrCreateVulkanMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data)
    {
        size_t assetid = entity.m_mesh_asset_id;

        //如果缓存中有该网格id，直接返回
        auto it = m_vulkan_meshes.find(assetid);
        if (it != m_vulkan_meshes.end()){
            return it->second;
        }
        else{
            VulkanMesh temp;
            auto res = m_vulkan_meshes.insert(std::make_pair(assetid, std::move(temp)));
            assert(res.second);//成功返回true

            //获取索引、顶点缓冲数据大小和数据
            uint32_t index_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_index_buffer->m_size);
            void* index_buffer_data = mesh_data.m_static_mesh_data.m_index_buffer->m_data;
            uint32_t vertex_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_size);
            MeshVertexDataDefinition* vertex_buffer_data = reinterpret_cast<MeshVertexDataDefinition*>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_data);

            VulkanMesh& now_mesh = res.first->second;
            updateMeshData(rhi,index_buffer_size,index_buffer_data,vertex_buffer_size,vertex_buffer_data,now_mesh);

            return now_mesh;
        }
    }

    VulkanPBRMaterial& RenderResource::getOrCreateVulkanMaterial(std::shared_ptr<RHI> rhi,
        RenderEntity         entity,
        RenderMaterialData   material_data)
    {
        VulkanRHI* vulkan_context = static_cast<VulkanRHI*>(rhi.get());

        size_t assetid = entity.m_material_asset_id;

        auto it = m_vulkan_pbr_materials.find(assetid);
        if (it != m_vulkan_pbr_materials.end())
        {
            return it->second;
        }
        else
        {
            VulkanPBRMaterial temp;
            auto              res = m_vulkan_pbr_materials.insert(std::make_pair(assetid, std::move(temp)));
            assert(res.second);

            float empty_image[] = { 0.5f, 0.5f, 0.5f, 0.5f };

            void* base_color_image_pixels = empty_image;
            uint32_t           base_color_image_width = 1;
            uint32_t           base_color_image_height = 1;
            VkFormat base_color_image_format = VK_FORMAT_R8G8B8A8_SRGB;
            if (material_data.m_base_color_texture)
            {
                base_color_image_pixels = material_data.m_base_color_texture->m_pixels;
                base_color_image_width = static_cast<uint32_t>(material_data.m_base_color_texture->m_width);
                base_color_image_height = static_cast<uint32_t>(material_data.m_base_color_texture->m_height);
                base_color_image_format = material_data.m_base_color_texture->m_format;
            }

            void* metallic_roughness_image_pixels = empty_image;
            uint32_t metallic_roughness_width = 1;
            uint32_t metallic_roughness_height = 1;
            VkFormat metallic_roughness_format = VK_FORMAT_R8G8B8A8_UNORM;
            if (material_data.m_metallic_roughness_texture)
            {
                metallic_roughness_image_pixels = material_data.m_metallic_roughness_texture->m_pixels;
                metallic_roughness_width = static_cast<uint32_t>(material_data.m_metallic_roughness_texture->m_width);
                metallic_roughness_height = static_cast<uint32_t>(material_data.m_metallic_roughness_texture->m_height);
                metallic_roughness_format = material_data.m_metallic_roughness_texture->m_format;
            }

            void* normal_roughness_image_pixels = empty_image;
            uint32_t normal_roughness_width = 1;
            uint32_t normal_roughness_height = 1;
            VkFormat normal_roughness_format = VK_FORMAT_R8G8B8A8_UNORM;
            if (material_data.m_normal_texture)
            {
                normal_roughness_image_pixels = material_data.m_normal_texture->m_pixels;
                normal_roughness_width = static_cast<uint32_t>(material_data.m_normal_texture->m_width);
                normal_roughness_height = static_cast<uint32_t>(material_data.m_normal_texture->m_height);
                normal_roughness_format = material_data.m_normal_texture->m_format;
            }

            void* occlusion_image_pixels = empty_image;
            uint32_t occlusion_image_width = 1;
            uint32_t occlusion_image_height = 1;
            VkFormat occlusion_image_format = VK_FORMAT_R8G8B8A8_UNORM;
            if (material_data.m_occlusion_texture)
            {
                occlusion_image_pixels = material_data.m_occlusion_texture->m_pixels;
                occlusion_image_width = static_cast<uint32_t>(material_data.m_occlusion_texture->m_width);
                occlusion_image_height = static_cast<uint32_t>(material_data.m_occlusion_texture->m_height);
                occlusion_image_format = material_data.m_occlusion_texture->m_format;
            }

            void* emissive_image_pixels = empty_image;
            uint32_t emissive_image_width = 1;
            uint32_t emissive_image_height = 1;
            VkFormat emissive_image_format = VK_FORMAT_R8G8B8A8_UNORM;
            if (material_data.m_emissive_texture)
            {
                emissive_image_pixels = material_data.m_emissive_texture->m_pixels;
                emissive_image_width = static_cast<uint32_t>(material_data.m_emissive_texture->m_width);
                emissive_image_height = static_cast<uint32_t>(material_data.m_emissive_texture->m_height);
                emissive_image_format = material_data.m_emissive_texture->m_format;
            }

            VulkanPBRMaterial& now_material = res.first->second;

            {
                // temporary staging buffer
                VkDeviceSize buffer_size = sizeof(MeshPerMaterialUniformBufferObject);
                VkBuffer staging_buffer;
                VkDeviceMemory staging_buffer_memory;
                rhi->createBuffer(buffer_size,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,staging_buffer,staging_buffer_memory);
                void* staging_buffer_data = nullptr;
                rhi->mapMemory(staging_buffer_memory,0,buffer_size,0,&staging_buffer_data);

                MeshPerMaterialUniformBufferObject& material_uniform_buffer_info = (*static_cast<MeshPerMaterialUniformBufferObject*>(staging_buffer_data));
                material_uniform_buffer_info.is_blend = entity.m_blend;
                material_uniform_buffer_info.is_double_sided = entity.m_double_sided;
                material_uniform_buffer_info.baseColorFactor = entity.m_base_color_factor;
                material_uniform_buffer_info.metallicFactor = entity.m_metallic_factor;
                material_uniform_buffer_info.roughnessFactor = entity.m_roughness_factor;
                material_uniform_buffer_info.normalScale = entity.m_normal_scale;
                material_uniform_buffer_info.occlusionStrength = entity.m_occlusion_strength;
                material_uniform_buffer_info.emissiveFactor = entity.m_emissive_factor;

                rhi->unmapMemory(staging_buffer_memory);

                // use the vmaAllocator to allocate asset uniform buffer
                VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
                bufferInfo.size = buffer_size;
                bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

                VmaAllocationCreateInfo allocInfo = {};
                allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

                rhi->createBufferWithAlignmentVMA(vulkan_context->m_assets_allocator,&bufferInfo,&allocInfo,m_global_render_resource._storage_buffer._min_uniform_buffer_offset_alignment,&now_material.material_uniform_buffer,&now_material.material_uniform_buffer_allocation,NULL);

                // use the data from staging buffer
                rhi->copyBuffer(staging_buffer, now_material.material_uniform_buffer, 0, 0, buffer_size);

                // release staging buffer
                rhi->destroyBuffer(staging_buffer);
                rhi->freeMemory(staging_buffer_memory);
            }

            TextureDataToUpdate update_texture_data;
            update_texture_data.base_color_image_pixels = base_color_image_pixels;
            update_texture_data.base_color_image_width = base_color_image_width;
            update_texture_data.base_color_image_height = base_color_image_height;
            update_texture_data.base_color_image_format = base_color_image_format;
            update_texture_data.metallic_roughness_image_pixels = metallic_roughness_image_pixels;
            update_texture_data.metallic_roughness_image_width = metallic_roughness_width;
            update_texture_data.metallic_roughness_image_height = metallic_roughness_height;
            update_texture_data.metallic_roughness_image_format = metallic_roughness_format;
            update_texture_data.normal_roughness_image_pixels = normal_roughness_image_pixels;
            update_texture_data.normal_roughness_image_width = normal_roughness_width;
            update_texture_data.normal_roughness_image_height = normal_roughness_height;
            update_texture_data.normal_roughness_image_format = normal_roughness_format;
            update_texture_data.occlusion_image_pixels = occlusion_image_pixels;
            update_texture_data.occlusion_image_width = occlusion_image_width;
            update_texture_data.occlusion_image_height = occlusion_image_height;
            update_texture_data.occlusion_image_format = occlusion_image_format;
            update_texture_data.emissive_image_pixels = emissive_image_pixels;
            update_texture_data.emissive_image_width = emissive_image_width;
            update_texture_data.emissive_image_height = emissive_image_height;
            update_texture_data.emissive_image_format = emissive_image_format;
            update_texture_data.now_material = &now_material;

            updateTextureImageData(rhi, update_texture_data);

            VkDescriptorSetAllocateInfo material_descriptor_set_alloc_info;
            material_descriptor_set_alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            material_descriptor_set_alloc_info.pNext = NULL;
            material_descriptor_set_alloc_info.descriptorPool = vulkan_context->m_descriptor_pool;
            material_descriptor_set_alloc_info.descriptorSetCount = 1;
            material_descriptor_set_alloc_info.pSetLayouts = m_material_descriptor_set_layout;

            if (VK_SUCCESS != rhi->allocateDescriptorSets(&material_descriptor_set_alloc_info,&now_material.material_descriptor_set))
            {
                throw std::runtime_error("allocate material descriptor set");
            }

            VkDescriptorBufferInfo material_uniform_buffer_info = {};
            material_uniform_buffer_info.offset = 0;
            material_uniform_buffer_info.range = sizeof(MeshPerMaterialUniformBufferObject);
            material_uniform_buffer_info.buffer = now_material.material_uniform_buffer;

            VkDescriptorImageInfo base_color_image_info = {};
            base_color_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            base_color_image_info.imageView = now_material.base_color_image_view;
            base_color_image_info.sampler = rhi->getOrCreateMipmapSampler(base_color_image_width,
                base_color_image_height);

            VkDescriptorImageInfo metallic_roughness_image_info = {};
            metallic_roughness_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            metallic_roughness_image_info.imageView = now_material.metallic_roughness_image_view;
            metallic_roughness_image_info.sampler = rhi->getOrCreateMipmapSampler(metallic_roughness_width,
                metallic_roughness_height);

            VkDescriptorImageInfo normal_roughness_image_info = {};
            normal_roughness_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            normal_roughness_image_info.imageView = now_material.normal_image_view;
            normal_roughness_image_info.sampler = rhi->getOrCreateMipmapSampler(normal_roughness_width,
                normal_roughness_height);

            VkDescriptorImageInfo occlusion_image_info = {};
            occlusion_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            occlusion_image_info.imageView = now_material.occlusion_image_view;
            occlusion_image_info.sampler = rhi->getOrCreateMipmapSampler(occlusion_image_width, occlusion_image_height);

            VkDescriptorImageInfo emissive_image_info = {};
            emissive_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            emissive_image_info.imageView = now_material.emissive_image_view;
            emissive_image_info.sampler = rhi->getOrCreateMipmapSampler(emissive_image_width, emissive_image_height);

            VkWriteDescriptorSet mesh_descriptor_writes_info[6];

            mesh_descriptor_writes_info[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            mesh_descriptor_writes_info[0].pNext = NULL;
            mesh_descriptor_writes_info[0].dstSet = now_material.material_descriptor_set;
            mesh_descriptor_writes_info[0].dstBinding = 0;
            mesh_descriptor_writes_info[0].dstArrayElement = 0;
            mesh_descriptor_writes_info[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            mesh_descriptor_writes_info[0].descriptorCount = 1;
            mesh_descriptor_writes_info[0].pBufferInfo = &material_uniform_buffer_info;

            mesh_descriptor_writes_info[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            mesh_descriptor_writes_info[1].pNext = NULL;
            mesh_descriptor_writes_info[1].dstSet = now_material.material_descriptor_set;
            mesh_descriptor_writes_info[1].dstBinding = 1;
            mesh_descriptor_writes_info[1].dstArrayElement = 0;
            mesh_descriptor_writes_info[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            mesh_descriptor_writes_info[1].descriptorCount = 1;
            mesh_descriptor_writes_info[1].pImageInfo = &base_color_image_info;

            mesh_descriptor_writes_info[2] = mesh_descriptor_writes_info[1];
            mesh_descriptor_writes_info[2].dstBinding = 2;
            mesh_descriptor_writes_info[2].pImageInfo = &metallic_roughness_image_info;

            mesh_descriptor_writes_info[3] = mesh_descriptor_writes_info[1];
            mesh_descriptor_writes_info[3].dstBinding = 3;
            mesh_descriptor_writes_info[3].pImageInfo = &normal_roughness_image_info;

            mesh_descriptor_writes_info[4] = mesh_descriptor_writes_info[1];
            mesh_descriptor_writes_info[4].dstBinding = 4;
            mesh_descriptor_writes_info[4].pImageInfo = &occlusion_image_info;

            mesh_descriptor_writes_info[5] = mesh_descriptor_writes_info[1];
            mesh_descriptor_writes_info[5].dstBinding = 5;
            mesh_descriptor_writes_info[5].pImageInfo = &emissive_image_info;

            rhi->updateDescriptorSets(6, mesh_descriptor_writes_info, 0, nullptr);

            return now_material;
        }
    }

    void RenderResource::updateTextureImageData(std::shared_ptr<RHI> rhi, const TextureDataToUpdate& texture_data)
    {
        rhi->createGlobalImage(texture_data.now_material->base_color_texture_image,texture_data.now_material->base_color_image_view,texture_data.now_material->base_color_image_allocation,texture_data.base_color_image_width,texture_data.base_color_image_height,texture_data.base_color_image_pixels,texture_data.base_color_image_format);
        rhi->createGlobalImage(texture_data.now_material->metallic_roughness_texture_image,texture_data.now_material->metallic_roughness_image_view,texture_data.now_material->metallic_roughness_image_allocation,texture_data.metallic_roughness_image_width,texture_data.metallic_roughness_image_height,texture_data.metallic_roughness_image_pixels,texture_data.metallic_roughness_image_format);
        rhi->createGlobalImage(texture_data.now_material->normal_texture_image,texture_data.now_material->normal_image_view,texture_data.now_material->normal_image_allocation,texture_data.normal_roughness_image_width,texture_data.normal_roughness_image_height,texture_data.normal_roughness_image_pixels,texture_data.normal_roughness_image_format);
        rhi->createGlobalImage(texture_data.now_material->occlusion_texture_image,texture_data.now_material->occlusion_image_view,texture_data.now_material->occlusion_image_allocation,texture_data.occlusion_image_width,texture_data.occlusion_image_height,texture_data.occlusion_image_pixels,texture_data.occlusion_image_format);
        rhi->createGlobalImage(texture_data.now_material->emissive_texture_image,texture_data.now_material->emissive_image_view,texture_data.now_material->emissive_image_allocation,texture_data.emissive_image_width,texture_data.emissive_image_height,texture_data.emissive_image_pixels,texture_data.emissive_image_format);
    }

    //****************************获取实体网格、材质*************************//
    VulkanMesh& RenderResource::getEntityMesh(RenderEntity entity){
        size_t assetid = entity.m_mesh_asset_id;

        auto it = m_vulkan_meshes.find(assetid);
        if (it != m_vulkan_meshes.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("failed to get entity mesh");
        }
    }

    VulkanPBRMaterial& RenderResource::getEntityMaterial(RenderEntity entity){
        size_t assetid = entity.m_material_asset_id;

        auto it = m_vulkan_pbr_materials.find(assetid);
        if (it != m_vulkan_pbr_materials.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("failed to get entity material");
        }
    }

    void RenderResource::resetRingBufferOffset(uint8_t current_frame_index)
    {
        m_global_render_resource._storage_buffer._global_upload_ringbuffers_end[current_frame_index] = m_global_render_resource._storage_buffer._global_upload_ringbuffers_begin[current_frame_index];
    }
}