#include "config_manager.h"
#include "runtime/engine.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
namespace SimpleEngine {
    void ConfigManager::init(const std::filesystem::path& config_file_path)
    {
        //读配置文件
        std::ifstream config_file(config_file_path);
        std::string config_line;
        while (std::getline(config_file, config_line))
        {
            size_t seperate_pos = config_line.find_first_of('=');//找到分隔符位置
            if (seperate_pos > 0 && seperate_pos < (config_line.length() - 1))//如果等号后有内容
            {
                std::string name = config_line.substr(0, seperate_pos);
                std::string value = config_line.substr(seperate_pos + 1, config_line.length() - seperate_pos - 1);
                if (name == "BinaryRootFolder")
                {
                    m_root_folder = config_file_path.parent_path() / value;//追加路径
                }
                else if (name == "AssetFolder")
                {
                    m_asset_folder = m_root_folder / value;
                }
                else if (name == "DefaultWorld")
                {
                    m_default_world_url = value;
                }
                else if (name == "GlobalRenderingRes")
                {
                    m_global_rendering_res_url = value;
                }
                else if (name == "BigIconFile")
                {
                    m_editor_big_icon_path = m_root_folder / value;
                }
                else if (name == "SmallIconFile")
                {
                    m_editor_small_icon_path = m_root_folder / value;
                }
                else if (name == "FontFile")
                {
                    m_editor_font_path = m_root_folder / value;
                }
                else if (name == "TestFile")
                {
                    m_test_picture_path = m_root_folder / value;
                }
            }
        }
    }
}