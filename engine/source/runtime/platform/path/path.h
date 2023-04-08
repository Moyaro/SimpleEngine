#pragma once
#include <filesystem>
#include <string>
#include <tuple>
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// ���ļ�����·���ĸ��ִ�����
    /// </summary>
    class Path
    {
    public:
        //��ȡ�����file_path��directory��·��
        static const std::filesystem::path getRelativePath(const std::filesystem::path& directory,const std::filesystem::path& file_path);
        //��ȡÿ��Ŀ¼��Ƭ��
        static const std::vector<std::string> getPathSegments(const std::filesystem::path& file_path);
        //��ȡ�����ļ���׺
        static const std::tuple<std::string, std::string, std::string> getFileExtensions(const std::filesystem::path& file_path);
        //��ȡ�ļ������޺�׺��
        static const std::string getFilePureName(const std::string);
    };
}