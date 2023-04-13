#include "editor/include/editor_file_service.h"

#include "runtime/platform/file_system/file_system.h"
#include "runtime/platform/path/path.h"

#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/resource/config_manager/config_manager.h"

#include "runtime/function/global/global_context.h"
#include "core/base/macro.h"

namespace SimpleEngine
{
    //用间隔符来把input string分离成子串,然后过滤子串
    std::vector<std::string> splitString(std::string input_string, const std::string& separator, const std::string& filter_string = "")
    {
        std::vector<std::string> output_string;
        int                      pos = input_string.find(separator);//间隔符位置
        std::string              add_string;//要加到output_string的子字符串

        //如果位置存在，就把间隔符之前的字符作为子串，子串不为空就放到输出数组里
        while (pos != std::string::npos)
        {
            add_string = input_string.substr(0, pos);
            if (!add_string.empty())
            {
                if (!filter_string.empty() && add_string == filter_string)
                {
                    //过滤子串
                }
                else
                {
                    output_string.push_back(add_string);
                }
            }
            input_string.erase(0, pos + 1);//把pos之前（包括pos）的内容删掉
            pos = input_string.find(separator);
        }
        //没有间隔符，就将剩余的字符串内容放入add_string
        add_string = input_string;
        if (!add_string.empty())
        {
            output_string.push_back(add_string);
        }
        return output_string;
    }

    void EditorFileService::buildEngineFileTree()
    {
        //获取asset文件夹下的所有文件路径，然后获取相对路径，把相对路径的每级目录的数组保存到all_file_segments
        std::string                              asset_folder = g_runtime_global_context.m_config_manager->getAssetFolder().generic_string();
        const std::vector<std::filesystem::path> file_paths = g_runtime_global_context.m_file_system->getFiles(asset_folder);
        std::vector<std::vector<std::string>>    all_file_segments;
        for (const auto& path : file_paths)
        {
            const std::filesystem::path& relative_path = Path::getRelativePath(asset_folder, path);
            all_file_segments.emplace_back(Path::getPathSegments(relative_path));
        }

        std::vector<std::shared_ptr<EditorFileNode>> node_array;//文件结点数组

        //设置根结点为asset
        m_file_node_array.clear();
        auto root_node = std::make_shared<EditorFileNode>();
        *root_node = m_root_node;
        m_file_node_array.push_back(root_node);

        //遍历文件路径
        int all_file_segments_count = all_file_segments.size();
        for (int file_index = 0; file_index < all_file_segments_count; file_index++)
        {
            //根结点为asset，深度-1
            node_array.clear();
            node_array.push_back(root_node);

            int depth = 0;
            //遍历每一级目录
            int file_segment_count = all_file_segments[file_index].size();
            for (int file_segment_index = 0; file_segment_index < file_segment_count; file_segment_index++)
            {
                auto file_node = std::make_shared<EditorFileNode>();
                file_node->m_file_name = all_file_segments[file_index][file_segment_index];//获取文件名

                if (depth < file_segment_count - 1)//深度小于文件数-1的都是文件夹
                {
                    file_node->m_file_type = "Folder";
                }
                else
                {
                    //设置后缀为文件类型
                    const auto& extensions = Path::getFileExtensions(file_paths[file_index]);
                    file_node->m_file_type = std::get<0>(extensions);
                    if (file_node->m_file_type.size() == 0)
                        continue;

                    //后缀为.json时，以二级扩展名为文件类型
                    if (file_node->m_file_type.compare(".json") == 0)
                    {
                        file_node->m_file_type = std::get<1>(extensions);
                        if (file_node->m_file_type.compare(".component") == 0)//是.component就用三级扩展 + 二级扩展当文件类型
                        {
                            file_node->m_file_type = std::get<2>(extensions) + std::get<1>(extensions);
                        }
                    }
                    file_node->m_file_type = file_node->m_file_type.substr(1);//把最前面的.去掉
                    file_node->m_file_path = file_paths[file_index].generic_string();//文件路径即asset的相对路径
                }
                file_node->m_node_depth = depth;
                node_array.push_back(file_node);

                //查看该节点是否在数组中，不在就进数组
                bool node_exists = checkFileArray(file_node.get());
                if (node_exists == false)
                {
                    m_file_node_array.push_back(file_node);
                }
                //找到父结点，把结点放入子结点列表
                EditorFileNode* parent_node_ptr = getParentNodePtr(node_array[depth].get());
                if (parent_node_ptr != nullptr && node_exists == false)
                {
                    parent_node_ptr->m_child_nodes.push_back(file_node);
                }
                depth++;
            }
        }
    }

    bool EditorFileService::checkFileArray(EditorFileNode* file_node)
    {
        //遍历结点数组，查看是否已有file_node
        int editor_node_count = m_file_node_array.size();
        for (int file_node_index = 0; file_node_index < editor_node_count; file_node_index++)
        {
            if (m_file_node_array[file_node_index]->m_file_name == file_node->m_file_name &&
                m_file_node_array[file_node_index]->m_node_depth == file_node->m_node_depth)
            {
                return true;
            }
        }
        return false;
    }

    EditorFileNode* EditorFileService::getParentNodePtr(EditorFileNode* file_node)
    {
        int editor_node_count = m_file_node_array.size();
        for (int file_node_index = 0; file_node_index < editor_node_count; file_node_index++)
        {
            if (m_file_node_array[file_node_index]->m_file_name == file_node->m_file_name &&
                m_file_node_array[file_node_index]->m_node_depth == file_node->m_node_depth)
            {
                return m_file_node_array[file_node_index].get();
            }
        }
        return nullptr;
    }
}