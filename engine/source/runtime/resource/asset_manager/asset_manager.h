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
    /// ��ȡ/������Դ�ļ�
    /// </summary>
    class AssetManager
    {
    public:
        template<typename AssetType>
        bool loadAsset(const std::string& asset_url, AssetType& out_asset) const
        {
            //���ļ�
            std::filesystem::path asset_path = getFullPath(asset_url);
            std::ifstream asset_json_file(asset_path);
            if (!asset_json_file)
            {
                std::cout<<"�ļ���ʧ�ܣ�"<<asset_path.generic_string()<<std::endl;
                return false;
            }

            //���ļ����ݸ�buffer
            std::stringstream buffer;
            buffer << asset_json_file.rdbuf();

            //text->string->json->C++����
            std::string asset_json_text(buffer.str());
            std::string error;
            auto&& asset_json = Json::parse(asset_json_text, error);
            if (!error.empty())
            {
                std::cout << "JSON�ļ�����ʧ�ܣ�" << asset_url << std::endl;
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
                std::cout << "�ļ���ʧ�ܣ�" << asset_url << std::endl;
                return false;
            }

            //��������->json->string->text
            auto&& asset_json = Serializer::write(out_asset);
            std::string&& asset_json_text = asset_json.dump();

            //д���ļ�
            asset_json_file << asset_json_text;
            asset_json_file.flush();

            return true;
        }

        //��ȡ����·��
        std::filesystem::path getFullPath(const std::string& relative_path) const {
            return std::filesystem::absolute(g_runtime_global_context.m_config_manager->getRootFolder() / relative_path);
        }

    };
}