#pragma once

#include "runtime/function/render/render_pass.h"

namespace SimpleEngine
{
    struct CombineUIPassInitInfo : RenderPassInitInfo
    {
        VkRenderPass render_pass;
        VkImageView  scene_input_attachment;
        VkImageView ui_input_attachment;
    };

    class CombineUIPass : public RenderPass
    {
    public:
        void init(const RenderPassInitInfo* init_info) override final;
        void draw() override final;

        void updateAfterFramebufferRecreate(VkImageView scene_input_attachment, VkImageView ui_input_attachment);

    private:
        void setupDescriptorSetLayout();
        void setupPipelines();
        void setupDescriptorSet();
    };
} // namespace Piccolo
