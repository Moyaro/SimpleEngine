#pragma once
#include <filesystem>
#include "runtime/core/meta/serializer/serializer.h"
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <iostream>

#include "_generated/serializer/all_serializer.h"
#include "runtime/function/global/global_context.h"
#include "resource/config_manager/config_manager.h"

namespace SimpleEngine {
    /// <summary>
    /// 读取/保存资源文件
    /// </summary>
    class AssetManager
    {
    public:
        template<typename AssetType>
        bool loadAsset(const std::string& asset_url, AssetType& out_asset) const
        {
            //打开文件
            std::filesystem::path asset_path = getFullPath(asset_url);
            std::ifstream asset_json_file(asset_path);
            if (!asset_json_file)
            {
                std::cout<<"文件打开失败："<<asset_path.generic_string()<<std::endl;
                return false;
            }

            //把文件内容给buffer
            std::stringstream buffer;
            buffer << asset_json_file.rdbuf();

            //text->string->json->C++类型
            std::string asset_json_text(buffer.str());
            std::string error;
            auto&& asset_json = Json::parse(asset_json_text, error);
            if (!error.empty())
            {
                std::cout << "JSON文件解析失败：" << asset_url << std::endl;
                return false;
            }

            Serializer::read(asset_json, out_asset);
            return true;
        }

        template<typename AssetType>
        bool saveAsset(const AssetType& out_asset, const std::string& asset_url) const
        {
            std::ofstream asset_json_file(getFullPath(asset_url));
            if (!asset_json_file)
            {
                std::cout << "文件打开失败：" << asset_url << std::endl;
                return false;
            }

            //其他类型->json->string->text
            auto&& asset_json = Serializer::write(out_asset);
            std::string&& asset_json_text = asset_json.dump();

            //写入文件
            asset_json_file << asset_json_text;
            asset_json_file.flush();

            return true;
        }

        //获取绝对路径
        std::filesystem::path getFullPath(const std::string& relative_path) const {
            return std::filesystem::absolute(g_runtime_global_context.m_config_manager->getRootFolder() / relative_path);
        }

    };
}