#pragma once

#include "render_pipeline_base.h"
#include "render_resource_base.h"

namespace SimpleEngine {
	class RenderPipeline : public RenderPipelineBase
	{
	public:
		void clear() override{}

		void init(RenderPipelineInitInfo init_info) override;

		void forwardRender(std::shared_ptr<RenderResourceBase> render_resource) override;

		void passUpdateAfterRecreateSwapchain();

		virtual uint32_t getGuidOfPickedMesh(const Vector2& picked_uv) override;

		//…Ë÷√÷·◊¥Ã¨
		void setAxisVisibleState(bool state);
		void setSelectedAxis(size_t selected_axis);

	private:

	};
}