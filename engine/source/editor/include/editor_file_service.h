#pragma once

#include <memory>
#include <string>
#include <vector>

namespace SimpleEngine
{
    class EditorFileNode;
    using EditorFileNodeArray = std::vector<std::shared_ptr<EditorFileNode>>;

    struct EditorFileNode
    {
        //文件名称、类型、路径、深度、子节点
        std::string         m_file_name;
        std::string         m_file_type;
        std::string         m_file_path;
        int                 m_node_depth;
        EditorFileNodeArray m_child_nodes;

        EditorFileNode() = default;
        EditorFileNode(const std::string& name, const std::string& type, const std::string& path, int depth) :
            m_file_name(name), m_file_type(type), m_file_path(path), m_node_depth(depth)
        {}
    };

    class EditorFileService
    {
        EditorFileNodeArray m_file_node_array;//文件结点数组
        EditorFileNode      m_root_node{ "asset", "Folder", "asset", -1 };//根结点：asset文件夹

    private:
        EditorFileNode* getParentNodePtr(EditorFileNode* file_node);//获取父结点指针
        bool            checkFileArray(EditorFileNode* file_node);//检查数组中是否有该结点

    public:
        EditorFileNode* getEditorRootNode() { return m_file_node_array.empty() ? nullptr : m_file_node_array[0].get(); }//获取根结点

        void buildEngineFileTree();//构建文件树
    };
}
