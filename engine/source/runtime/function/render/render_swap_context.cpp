#include "render_swap_context.h"

#include <utility>

namespace SimpleEngine {
    void SwapData::addDirtyGameObject(GameObjectDesc&& desc)
    {
        if (m_game_object_resource_desc.has_value())
        {
            m_game_object_resource_desc->add(desc);
        }
        else
        {
            GameObjectResourceDesc go_descs;
            go_descs.add(desc);
            m_game_object_resource_desc = go_descs;
        }
    }

    void SwapData::addDeleteGameObject(GameObjectDesc&& desc)
    {
        if (m_game_object_to_delete.has_value())
        {
            m_game_object_to_delete->add(desc);
        }
        else
        {
            GameObjectResourceDesc go_descs;
            go_descs.add(desc);
            m_game_object_to_delete = go_descs;
        }
    }

	bool RenderSwapContext::isReadyToSwap() {
		return !(m_swap_data[m_render_swap_data_index].m_level_resource_desc.has_value() ||
			m_swap_data[m_render_swap_data_index].m_game_object_resource_desc.has_value() ||
			m_swap_data[m_render_swap_data_index].m_game_object_to_delete.has_value() ||
			m_swap_data[m_render_swap_data_index].m_camera_swap_data.has_value());
	}

	void RenderSwapContext::swapLogicRenderData() {
		if (isReadyToSwap()) {
            resetLevelResourceSwapData();
			resetGameObjectResourceSwapData();
			resetGameObjectToDelete();
			resetCameraSwapData();
			std::swap(m_logic_swap_data_index, m_render_swap_data_index);
		}
	}
}