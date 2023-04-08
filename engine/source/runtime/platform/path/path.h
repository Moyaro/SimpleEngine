#pragma once
#include <filesystem>
#include <string>
#include <tuple>
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// 对文件名、路径的各种处理函数
    /// </summary>
    class Path
    {
    public:
        //获取相对于file_path的directory的路径
        static const std::filesystem::path getRelativePath(const std::filesystem::path& directory,const std::filesystem::path& file_path);
        //获取每级目录的片段
        static const std::vector<std::string> getPathSegments(const std::filesystem::path& file_path);
        //获取各级文件后缀
        static const std::tuple<std::string, std::string, std::string> getFileExtensions(const std::filesystem::path& file_path);
        //获取文件名（无后缀）
        static const std::string getFilePureName(const std::string);
    };
}