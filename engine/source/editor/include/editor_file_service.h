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
        //�ļ����ơ����͡�·������ȡ��ӽڵ�
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
        EditorFileNodeArray m_file_node_array;//�ļ��������
        EditorFileNode      m_root_node{ "asset", "Folder", "asset", -1 };//����㣺asset�ļ���

    private:
        EditorFileNode* getParentNodePtr(EditorFileNode* file_node);//��ȡ�����ָ��
        bool            checkFileArray(EditorFileNode* file_node);//����������Ƿ��иý��

    public:
        EditorFileNode* getEditorRootNode() { return m_file_node_array.empty() ? nullptr : m_file_node_array[0].get(); }//��ȡ�����

        void buildEngineFileTree();//�����ļ���
    };
}
