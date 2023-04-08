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

    //������Դ
    struct Resource
    {
        VkBuffer buffer;
        VkDeviceMemory memory;
    };

    //������
    struct Descriptor
    {
        VkDescriptorSetLayout layout;
        std::vector<VkDescriptorSet> descriptor_set;
    };

    class DebugDrawAllocator
    {
    public:
        void init(DebugDrawFont* font);//��ȡrhi���������壬����������
        void allocator();//���仺����

        void tick();//ÿ֡����ɾ�����Ƿ�����Ҫɾ��������
        void destory();//��������+�����ݴ�����+ģ������
        void clear();//��������+�����ݴ�����
        void clearBuffer();//���������������ݷ����ɾ�б�

        //��¼���ݵ�����
        void cacheUniformObject(Matrix4x4 proj_view_matrix);
        size_t cacheUniformDynamicObject(const std::vector<std::pair<Matrix4x4, Vector4> >& model_colors);
        size_t cacheVertexs(const std::vector<DebugDrawVertex>& vertexs);//��¼�������ݵ����棬���ص�ǰ�����С

        //��ȡ�ݴ����ݴ�С
        size_t getVertexCacheOffset() const { return m_vertex_cache.size(); }
        size_t getUniformDynamicCacheOffset() const { return m_uniform_buffer_dynamic_object_cache.size(); }
        size_t getSizeOfUniformBufferObject() const{ return sizeof(UniformBufferDynamicObject); }

        //��ȡ������
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

        //�����������֡����������飩
        Descriptor m_descriptor;

        //���㻺��
        Resource m_vertex_resource;//���㻺��
        std::vector<DebugDrawVertex> m_vertex_cache;//�������ݵ��ݴ��

        //UBO����
        Resource m_uniform_resource;
        UniformBufferObject m_uniform_buffer_object_cache;
        Resource m_uniform_dynamic_resource;
        std::vector<UniformBufferDynamicObject> m_uniform_buffer_dynamic_object_cache;

        //������Դ
        DebugDrawFont* m_font = nullptr;

        //��̬ģ����Դ
        Resource m_sphere_resource;
        Resource m_cylinder_resource;
        Resource m_capsule_resource;

        //��ɾ����
        static const uint32_t k_deferred_delete_resource_frame_count = 5;//the count means after count-1 frame will be delete
        uint32_t m_current_frame = 0;
        std::queue<Resource> m_deffer_delete_queue[k_deferred_delete_resource_frame_count];//֮��Ҫɾ���Ļ�����

    private:
        //��������
        void setupDescriptorSet();
        void prepareDescriptorSet();
        void updateDescriptorSet();
        
        //����ģ�ͻ���
        void loadSphereMeshBuffer();
        void loadCylinderMeshBuffer();
        void loadCapsuleMeshBuffer();

        void unloadMeshBuffer();
        void flushPendingDelete();
        const int m_circle_sample_count = 10;
    };
}