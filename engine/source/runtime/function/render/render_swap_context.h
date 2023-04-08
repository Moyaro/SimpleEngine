#pragma once
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_object.h"
#include "runtime/resource/res_type/global/global_rendering.h"

#include <cstdint>
#include <deque>
#include <optional>
#include <string>
namespace SimpleEngine {

	//������
	struct LevelIBLResourceDesc
	{
		SkyBoxIrradianceMap m_skybox_irradiance_map;
		SkyBoxSpecularMap   m_skybox_specular_map;
		std::string         m_brdf_map;
	};

	//��ɫ����
	struct LevelColorGradingResourceDesc
	{
		std::string m_color_grading_map;
	};

	//�㼶��Դ����պ�
	struct LevelResourceDesc
	{
		LevelIBLResourceDesc          m_ibl_resource_desc;
	};

	//�����������
	struct CameraSwapData
	{
		std::optional<float>            m_fov_x;
		std::optional<RenderCameraType> m_camera_type;
		std::optional<Matrix4x4>        m_view_matrix;
	};

	//��������
	struct GameObjectResourceDesc
	{
		std::deque<GameObjectDesc> m_game_object_descs;

		void add(GameObjectDesc& desc) { m_game_object_descs.push_back(desc); }
		void pop() { m_game_object_descs.pop_front(); }

		bool isEmpty() const { return m_game_object_descs.empty(); }

		GameObjectDesc& getNextProcessObject() { return m_game_object_descs.front(); }//��ȡ��һ��Ҫ���������
	};

	struct SwapData
	{
		std::optional<LevelResourceDesc>       m_level_resource_desc;//�㼶��Դ
		std::optional<GameObjectResourceDesc>  m_game_object_resource_desc;//����������Դ
		std::optional<GameObjectResourceDesc>  m_game_object_to_delete;//��Ҫɾ��������
		std::optional<CameraSwapData>          m_camera_swap_data;//�����������

		void addDirtyGameObject(GameObjectDesc&& desc);//����Ҫ���������
		void addDeleteGameObject(GameObjectDesc&& desc);//������Ҫɾ��������
	};

	/// <summary>
	/// ������Ⱦ���߼�����
	/// </summary>
	class RenderSwapContext
	{
	public:
		//��ȡ��������
		SwapData& getLogicSwapData() { return m_swap_data[m_logic_swap_data_index]; }
		SwapData& getRenderSwapData() { return m_swap_data[m_render_swap_data_index]; }

		void swapLogicRenderData();//�����Ⱦ��������Ϊ�գ�������Ⱦ���ݣ�Ȼ�󽻻��߼�����Ⱦ������

		//������ȾҪ����������
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