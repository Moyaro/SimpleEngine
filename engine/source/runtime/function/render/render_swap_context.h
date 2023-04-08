#pragma once
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_object.h"
#include "runtime/resource/res_type/global/global_rendering.h"

#include <cstdint>
#include <deque>
#include <optional>
#include <string>
namespace SimpleEngine {

	//环境光
	struct LevelIBLResourceDesc
	{
		SkyBoxIrradianceMap m_skybox_irradiance_map;
		SkyBoxSpecularMap   m_skybox_specular_map;
		std::string         m_brdf_map;
	};

	//颜色渐变
	struct LevelColorGradingResourceDesc
	{
		std::string m_color_grading_map;
	};

	//层级资源：天空盒
	struct LevelResourceDesc
	{
		LevelIBLResourceDesc          m_ibl_resource_desc;
	};

	//相机交换数据
	struct CameraSwapData
	{
		std::optional<float>            m_fov_x;
		std::optional<RenderCameraType> m_camera_type;
		std::optional<Matrix4x4>        m_view_matrix;
	};

	//所有物体
	struct GameObjectResourceDesc
	{
		std::deque<GameObjectDesc> m_game_object_descs;

		void add(GameObjectDesc& desc) { m_game_object_descs.push_back(desc); }
		void pop() { m_game_object_descs.pop_front(); }

		bool isEmpty() const { return m_game_object_descs.empty(); }

		GameObjectDesc& getNextProcessObject() { return m_game_object_descs.front(); }//获取下一个要处理的物体
	};

	struct SwapData
	{
		std::optional<LevelResourceDesc>       m_level_resource_desc;//层级资源
		std::optional<GameObjectResourceDesc>  m_game_object_resource_desc;//现有物体资源
		std::optional<GameObjectResourceDesc>  m_game_object_to_delete;//需要删除的物体
		std::optional<CameraSwapData>          m_camera_swap_data;//相机交换数据

		void addDirtyGameObject(GameObjectDesc&& desc);//增加要处理的物体
		void addDeleteGameObject(GameObjectDesc&& desc);//增加需要删除的物体
	};

	/// <summary>
	/// 交换渲染和逻辑数据
	/// </summary>
	class RenderSwapContext
	{
	public:
		//获取交换数据
		SwapData& getLogicSwapData() { return m_swap_data[m_logic_swap_data_index]; }
		SwapData& getRenderSwapData() { return m_swap_data[m_render_swap_data_index]; }

		void swapLogicRenderData();//如果渲染交换数据为空，重置渲染数据，然后交换逻辑和渲染的索引

		//重置渲染要交换的数据
		void resetLevelResourceSwapData() { m_swap_data[m_render_swap_data_index].m_level_resource_desc.reset(); }
		void resetGameObjectResourceSwapData() { m_swap_data[m_render_swap_data_index].m_game_object_resource_desc.reset(); }
		void resetGameObjectToDelete() { m_swap_data[m_render_swap_data_index].m_game_object_to_delete.reset(); }
		void resetCameraSwapData() { m_swap_data[m_render_swap_data_index].m_camera_swap_data.reset(); }

	private:
		uint8_t m_logic_swap_data_index{ 0 };
		uint8_t m_render_swap_data_index{ 1 };
		SwapData m_swap_data[2];

		bool isReadyToSwap();
	};
}