#pragma once

#include <filesystem>
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// �ļ�������ȡ��ӦĿ¼�������ļ���·��
    /// </summary>
    class FileSystem
    {
    public:
        std::vector<std::filesystem::path> getFiles(const std::filesystem::path& directory) {
            std::vector<std::filesystem::path> files;
            for (auto const& directory_entry : std::filesystem::recursive_directory_iterator{ directory })//����·���������ļ�
            {
                if (directory_entry.is_regular_file())//�ļ����ھͱ����files��
                {
                    files.push_back(directory_entry);
                }
            }
            return files;
        }
    };
}