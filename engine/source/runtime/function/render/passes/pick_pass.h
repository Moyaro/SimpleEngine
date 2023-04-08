#pragma once

#include "runtime/core/math/vector2.h"
#include "runtime/function/render/render_pass.h"

namespace SimpleEngine
{
    class RenderResourceBase;

    struct PickPassInitInfo : RenderPassInitInfo
    {
        VkDescriptorSetLayout per_mesh_layout;
    };

    class PickPass : public RenderPass
    {
    public:
        void init(const RenderPassInitInfo* init_info) override final;
        void postInitialize() override final;
        void preparePassData(std::shared_ptr<RenderResourceBase> render_resource) override final;
        void draw() override final;

        uint32_t pick(const Vector2& picked_uv);
        void     recreateFramebuffer();

        MeshInefficientPickPerframeStorageBufferObject _mesh_inefficient_pick_perframe_storage_buffer_object;

    private:
        void setupAttachments();
        void setupRenderPass();
        void setupFramebuffer();
        void setupDescriptorSetLayout();
        void setupPipelines();
        void setupDescriptorSet();

    private:
        VkImage        _object_id_image;
        VkDeviceMemory _object_id_image_memory;
        VkImageView      _object_id_image_view;

        VkDescriptorSetLayout _per_mesh_layout;
    };
} // namespace Piccolo
