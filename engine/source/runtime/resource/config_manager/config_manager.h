#pragma once

#include <filesystem>
#include <string>

namespace SimpleEngine {

    /// <summary>
    /// �������ļ�����ȡ��Դ�ļ���·��
    /// </summary>
    class ConfigManager
    {
    public:
        void init(const std::filesystem::path& config_file_path);

        const std::filesystem::path& getRootFolder() const { return m_root_folder; }
        const std::filesystem::path& getAssetFolder() const { return m_asset_folder; }
        const std::string& getDefaultWorldUrl() const { return m_default_world_url; }
        const std::string& getGlobalRenderingResUrl() const { return m_global_rendering_res_url; }

        //����icon
        const std::filesystem::path& getEditorBigIconPath() const { return m_editor_big_icon_path; }
        const std::filesystem::path& getEditorSmallIconPath() const { return m_editor_small_icon_path; }

        //����
        const std::filesystem::path& getEditorFontPath() const{ return m_editor_font_path; }

        //����ͼƬ
        const std::filesystem::path& getTestPicturePath() const { return m_test_picture_path; }
    private:
        std::filesystem::path m_root_folder;
        std::filesystem::path m_asset_folder;

        std::filesystem::path m_editor_big_icon_path;
        std::filesystem::path m_editor_small_icon_path;
        std::filesystem::path m_editor_font_path;

        std::filesystem::path m_test_picture_path;
        std::string m_default_world_url;
        std::string m_global_rendering_res_url;
    };
}