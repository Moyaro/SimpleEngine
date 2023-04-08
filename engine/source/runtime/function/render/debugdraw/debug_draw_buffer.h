#pragma once

#include <vulkan/vulkan.h>
#include "../interface/rhi.h"
#include "../interface/rhi_struct.h"
#include "../../../core/math/math_headers.h"
#include "debug_draw_primitive.h"
#include "debug_draw_font.h"
#include <queue>
namespace SimpleEngine {

    //UBO
    struct UniformBufferObject
    {
        Matrix4x4 proj_view_matrix;
    };

    struct alignas(256) UniformBufferDynamicObject
    {
        Matrix4x4 model_matrix;
        Vector4 color;
    };

    //缓冲资源
    struct Resource
    {
        VkBuffer buffer;
        VkDeviceMemory memory;
    };

    //描述集
    struct Descriptor
    {
        VkDescriptorSetLayout layout;
        std::vector<VkDescriptorSet> descriptor_set;
    };

    class DebugDrawAllocator
    {
    public:
        void init(DebugDrawFont* font);//获取rhi，设置字体，开启描述集
        void allocator();//分配缓冲区

        void tick();//每帧检查待删队列是否有需要删除的内容
        void destory();//清理缓冲区+所有暂存数据+模型数据
        void clear();//清理缓冲区+所有暂存数据
        void clearBuffer();//清理缓冲区，把内容放入待删列表

        //记录数据到缓存
        void cacheUniformObject(Matrix4x4 proj_view_matrix);
        size_t cacheUniformDynamicObject(const std::vector<std::pair<Matrix4x4, Vector4> >& model_colors);
        size_t cacheVertexs(const std::vector<DebugDrawVertex>& vertexs);//记录顶点数据到缓存，返回当前缓存大小

        //获取暂存数据大小
        size_t getVertexCacheOffset() const { return m_vertex_cache.size(); }
        size_t getUniformDynamicCacheOffset() const { return m_uniform_buffer_dynamic_object_cache.size(); }
        size_t getSizeOfUniformBufferObject() const{ return sizeof(UniformBufferDynamicObject); }

        //获取缓冲区
        VkBuffer getVertexBuffer() { return m_vertex_resource.buffer; }
        VkBuffer getSphereVertexBuffer();
        VkBuffer getCylinderVertexBuffer();
        VkBuffer getCapsuleVertexBuffer();

        VkDescriptorSet& getDescriptorSet() { return m_descriptor.descriptor_set[m_rhi->getCurrentFrameIndex()]; }

        const size_t getSphereVertexBufferSize() const { return ((m_circle_sample_count * 2 + 2) * (m_circle_sample_count * 2) * 2 + (m_circle_sample_count * 2 + 1) * (m_circle_sample_count * 2) * 2); }
        const size_t getCylinderVertexBufferSize() const{ return (m_circle_sample_count * 2) * 5 * 2; }
        const size_t getCapsuleVertexBufferSize() const{ return (m_circle_sample_count * 2) * m_circle_sample_count * 4 + (2 * m_circle_sample_count) * 2 + (2 * m_circle_sample_count) * m_circle_sample_count * 4; }
        const size_t getCapsuleVertexBufferUpSize() const{ return (m_circle_sample_count * 2) * m_circle_sample_count * 4; }
        const size_t getCapsuleVertexBufferMidSize() const{ return 2 * m_circle_sample_count * 2; }
        const size_t getCapsuleVertexBufferDownSize() const{ return 2 * m_circle_sample_count * m_circle_sample_count * 4; }

        
    private:
        std::shared_ptr<RHI> m_rhi;

        //描述集（布局、描述集数组）
        Descriptor m_descriptor;

        //顶点缓冲
        Resource m_vertex_resource;//顶点缓冲
        std::vector<DebugDrawVertex> m_vertex_cache;//顶点数据的暂存点

        //UBO缓冲
        Resource m_uniform_resource;
        UniformBufferObject m_uniform_buffer_object_cache;
        Resource m_uniform_dynamic_resource;
        std::vector<UniformBufferDynamicObject> m_uniform_buffer_dynamic_object_cache;

        //字体资源
        DebugDrawFont* m_font = nullptr;

        //静态模型资源
        Resource m_sphere_resource;
        Resource m_cylinder_resource;
        Resource m_capsule_resource;

        //待删队列
        static const uint32_t k_deferred_delete_resource_frame_count = 5;//the count means after count-1 frame will be delete
        uint32_t m_current_frame = 0;
        std::queue<Resource> m_deffer_delete_queue[k_deferred_delete_resource_frame_count];//之后要删除的缓冲区

    private:
        //描述符集
        void setupDescriptorSet();
        void prepareDescriptorSet();
        void updateDescriptorSet();
        
        //加载模型缓冲
        void loadSphereMeshBuffer();
        void loadCylinderMeshBuffer();
        void loadCapsuleMeshBuffer();

        void unloadMeshBuffer();
        void flushPendingDelete();
        const int m_circle_sample_count = 10;
    };
}