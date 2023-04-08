#pragma once
#include "interface/rhi.h"
#include "core/math/math_headers.h"

namespace SimpleEngine {
    
    static const uint32_t s_point_light_shadow_map_dimension = 2048;
    static const uint32_t s_directional_light_shadow_map_dimension = 4096;

    static uint32_t const s_mesh_per_drawcall_max_instance_count = 64;
    static uint32_t const s_max_point_light_count = 15;

    struct VulkanMeshInstance
    {
        Matrix4x4 model_matrix;
    };

    struct MeshPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct VulkanMesh
    {

        uint32_t mesh_vertex_count;//顶点数

        //顶点缓冲
        VkBuffer mesh_vertex_position_buffer;
        VmaAllocation mesh_vertex_position_buffer_allocation;

        VkBuffer mesh_vertex_varying_buffer;
        VmaAllocation mesh_vertex_varying_buffer_allocation;

        VkDescriptorSet mesh_vertex_blending_descriptor_set;

        VkBuffer mesh_vertex_varying_enable_blending_buffer;
        VmaAllocation mesh_vertex_varying_enable_blending_buffer_allocation;

        uint32_t mesh_index_count;//索引数

        //索引缓冲
        VkBuffer mesh_index_buffer;
        VmaAllocation mesh_index_buffer_allocation;
    };

    struct VulkanSceneDirectionalLight
    {
        Vector3 direction;
        float   _padding_direction;
        Vector3 color;
        float   _padding_color;
    };

    struct VulkanScenePointLight
    {
        Vector3 position;
        float   radius;
        Vector3 intensity;
        float   _padding_intensity;
    };

    struct MeshPerframeStorageBufferObject
    {
        Matrix4x4                   proj_view_matrix;//投影视图矩阵
        Vector3                     camera_position;
        float                       _padding_camera_position;
        Vector3                     ambient_light;
        float                       _padding_ambient_light;
        uint32_t                    point_light_num;
        uint32_t                    _padding_point_light_num_1;
        uint32_t                    _padding_point_light_num_2;
        uint32_t                    _padding_point_light_num_3;
        VulkanScenePointLight       scene_point_lights[s_max_point_light_count];
        VulkanSceneDirectionalLight scene_directional_light;
        Matrix4x4                   directional_light_proj_view;
    };

    //PBR材质图像、图像视图，缓冲区，描述集
    struct VulkanPBRMaterial
    {
        VkImage base_color_texture_image;
        VkImageView base_color_image_view;
        VmaAllocation   base_color_image_allocation;

        VkImage metallic_roughness_texture_image;
        VkImageView metallic_roughness_image_view;
        VmaAllocation   metallic_roughness_image_allocation;

        VkImage normal_texture_image;
        VkImageView normal_image_view;
        VmaAllocation   normal_image_allocation;

        VkImage occlusion_texture_image;
        VkImageView occlusion_image_view;
        VmaAllocation   occlusion_image_allocation;

        VkImage emissive_texture_image;
        VkImageView emissive_image_view;
        VmaAllocation   emissive_image_allocation;

        VkBuffer material_uniform_buffer;
        VmaAllocation   material_uniform_buffer_allocation;

        VkDescriptorSet material_descriptor_set;
    };

    //网格节点
    struct RenderMeshNode
    {
        const Matrix4x4* model_matrix{ nullptr };
        VulkanMesh* ref_mesh{ nullptr };
        VulkanPBRMaterial* ref_material{ nullptr };
        uint32_t node_id;
    };
    //轴节点
    struct RenderAxisNode
    {
        Matrix4x4   model_matrix{ Matrix4x4::IDENTITY };
        VulkanMesh* ref_mesh{ nullptr };
        uint32_t    node_id;
    };

    struct MeshPointLightShadowPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshDirectionalLightShadowPerframeStorageBufferObject
    {
        Matrix4x4 light_proj_view;
    };
    struct MeshDirectionalLightShadowPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshPointLightShadowPerframeStorageBufferObject
    {
        uint32_t point_light_num;
        uint32_t _padding_point_light_num_1;
        uint32_t _padding_point_light_num_2;
        uint32_t _padding_point_light_num_3;
        Vector4  point_lights_position_and_radius[s_max_point_light_count];
    };

    //*************************用于resource**************************//

    struct MeshPerMaterialUniformBufferObject
    {
        Vector4 baseColorFactor{ 0.0f, 0.0f, 0.0f, 0.0f };

        float metallicFactor = 0.0f;
        float roughnessFactor = 0.0f;
        float normalScale = 0.0f;
        float occlusionStrength = 0.0f;

        Vector3  emissiveFactor = { 0.0f, 0.0f, 0.0f };
        uint32_t is_blend = 0;
        uint32_t is_double_sided = 0;
    };

    /// <summary>
    /// 纹理的像素、宽高、格式，材质
    /// </summary>
    struct TextureDataToUpdate
    {
        void* base_color_image_pixels;
        uint32_t base_color_image_width;
        uint32_t base_color_image_height;
        VkFormat base_color_image_format;

        void* metallic_roughness_image_pixels;
        uint32_t metallic_roughness_image_width;
        uint32_t metallic_roughness_image_height;
        VkFormat metallic_roughness_image_format;

        void* normal_roughness_image_pixels;
        uint32_t normal_roughness_image_width;
        uint32_t normal_roughness_image_height;
        VkFormat normal_roughness_image_format;

        void* occlusion_image_pixels;
        uint32_t occlusion_image_width;
        uint32_t occlusion_image_height;
        VkFormat occlusion_image_format;

        void* emissive_image_pixels;
        uint32_t emissive_image_width;
        uint32_t emissive_image_height;
        VkFormat emissive_image_format;

        VulkanPBRMaterial* now_material;
    };

    struct AxisStorageBufferObject
    {
        Matrix4x4 model_matrix = Matrix4x4::IDENTITY;
        uint32_t  selected_axis = 3;
    };

    struct MeshInefficientPickPerframeStorageBufferObject
    {
        Matrix4x4 proj_view_matrix;
        uint32_t  rt_width;
        uint32_t  rt_height;
    };

    struct MeshInefficientPickPerdrawcallStorageBufferObject
    {
        Matrix4x4 model_matrices[s_mesh_per_drawcall_max_instance_count];
        uint32_t  node_ids[s_mesh_per_drawcall_max_instance_count];
    };

}