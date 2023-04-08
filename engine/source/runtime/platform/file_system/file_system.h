#pragma once

#include <filesystem>
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// 文件管理：获取对应目录下所有文件的路径
    /// </summary>
    class FileSystem
    {
    public:
        std::vector<std::filesystem::path> getFiles(const std::filesystem::path& directory) {
            std::vector<std::filesystem::path> files;
            for (auto const& directory_entry : std::filesystem::recursive_directory_iterator{ directory })//遍历路径中所有文件
            {
                if (directory_entry.is_regular_file())//文件存在就保存进files中
                {
                    files.push_back(directory_entry);
                }
            }
            return files;
        }
    };
}