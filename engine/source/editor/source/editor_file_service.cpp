#include "editor/include/editor_file_service.h"

#include "runtime/platform/file_system/file_system.h"
#include "runtime/platform/path/path.h"

#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/resource/config_manager/config_manager.h"

#include "runtime/function/global/global_context.h"
#include "core/base/macro.h"

namespace SimpleEngine
{
    //�ü��������input string������Ӵ�,Ȼ������Ӵ�
    std::vector<std::string> splitString(std::string input_string, const std::string& separator, const std::string& filter_string = "")
    {
        std::vector<std::string> output_string;
        int                      pos = input_string.find(separator);//�����λ��
        std::string              add_string;//Ҫ�ӵ�output_string�����ַ���

        //���λ�ô��ڣ��ͰѼ����֮ǰ���ַ���Ϊ�Ӵ����Ӵ���Ϊ�վͷŵ����������
        while (pos != std::string::npos)
        {
            add_string = input_string.substr(0, pos);
            if (!add_string.empty())
            {
                if (!filter_string.empty() && add_string == filter_string)
                {
                    //�����Ӵ�
                }
                else
                {
                    output_string.push_back(add_string);
                }
            }
            input_string.erase(0, pos + 1);//��pos֮ǰ������pos��������ɾ��
            pos = input_string.find(separator);
        }
        //û�м�������ͽ�ʣ����ַ������ݷ���add_string
        add_string = input_string;
        if (!add_string.empty())
        {
            output_string.push_back(add_string);
        }
        return output_string;
    }

    void EditorFileService::buildEngineFileTree()
    {
        //��ȡasset�ļ����µ������ļ�·����Ȼ���ȡ���·���������·����ÿ��Ŀ¼�����鱣�浽all_file_segments
        std::string                              asset_folder = g_runtime_global_context.m_config_manager->getAssetFolder().generic_string();
        const std::vector<std::filesystem::path> file_paths = g_runtime_global_context.m_file_system->getFiles(asset_folder);
        std::vector<std::vector<std::string>>    all_file_segments;
        for (const auto& path : file_paths)
        {
            const std::filesystem::path& relative_path = Path::getRelativePath(asset_folder, path);
            all_file_segments.emplace_back(Path::getPathSegments(relative_path));
        }

        std::vector<std::shared_ptr<EditorFileNode>> node_array;//�ļ��������

        //���ø����Ϊasset
        m_file_node_array.clear();
        auto root_node = std::make_shared<EditorFileNode>();
        *root_node = m_root_node;
        m_file_node_array.push_back(root_node);

        //�����ļ�·��
        int all_file_segments_count = all_file_segments.size();
        for (int file_index = 0; file_index < all_file_segments_count; file_index++)
        {
            //�����Ϊasset�����-1
            node_array.clear();
            node_array.push_back(root_node);

            int depth = 0;
            //����ÿһ��Ŀ¼
            int file_segment_count = all_file_segments[file_index].size();
            for (int file_segment_index = 0; file_segment_index < file_segment_count; file_segment_index++)
            {
                auto file_node = std::make_shared<EditorFileNode>();
                file_node->m_file_name = all_file_segments[file_index][file_segment_index];//��ȡ�ļ���

                if (depth < file_segment_count - 1)//���С���ļ���-1�Ķ����ļ���
                {
                    file_node->m_file_type = "Folder";
                }
                else
                {
                    //���ú�׺Ϊ�ļ�����
                    const auto& extensions = Path::getFileExtensions(file_paths[file_index]);
                    file_node->m_file_type = std::get<0>(extensions);
                    if (file_node->m_file_type.size() == 0)
                        continue;

                    //��׺Ϊ.jsonʱ���Զ�����չ��Ϊ�ļ�����
                    if (file_node->m_file_type.compare(".json") == 0)
                    {
                        file_node->m_file_type = std::get<1>(extensions);
                        if (file_node->m_file_type.compare(".component") == 0)//��.component����������չ + ������չ���ļ�����
                        {
                            file_node->m_file_type = std::get<2>(extensions) + std::get<1>(extensions);
                        }
                    }
                    file_node->m_file_type = file_node->m_file_type.substr(1);//����ǰ���.ȥ��
                    file_node->m_file_path = file_paths[file_index].generic_string();//�ļ�·����asset�����·��
                }
                file_node->m_node_depth = depth;
                node_array.push_back(file_node);

                //�鿴�ýڵ��Ƿ��������У����ھͽ�����
                bool node_exists = checkFileArray(file_node.get());
                if (node_exists == false)
                {
                    m_file_node_array.push_back(file_node);
                }
                //�ҵ�����㣬�ѽ������ӽ���б�
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
        //����������飬�鿴�Ƿ�����file_node
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