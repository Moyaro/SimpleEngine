#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace SimpleEngine
{
    //原始类型
    enum class PrimitiveType
    {
        point,
        line,
        triangle,
        quad
    };

    //顶点缓冲
    struct RawVertexBuffer
    {
        uint32_t           vertex_count{ 0 };
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> tangents;
        std::vector<float> uvs;
    };
    //索引缓冲
    struct RawIndexBuffer
    {
        PrimitiveType         primitive_type{ PrimitiveType::triangle };
        uint32_t              primitive_count{ 0 };
        std::vector<uint32_t> indices;
    };

    //材质纹理
    struct MaterialTexture
    {
        std::string base_color;
        std::string metallic_roughness;
        std::string normal;
    };

    //静态网格数据
    struct StaticMeshData
    {
        RawVertexBuffer vertex_buffer;
        RawIndexBuffer  index_buffer;
        MaterialTexture material_texture;
    };
}