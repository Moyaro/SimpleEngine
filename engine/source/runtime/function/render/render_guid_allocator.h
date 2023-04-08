#pragma once

#include <unordered_map>

namespace SimpleEngine
{
    static const size_t s_invalid_guid = 0;//无效GUID

    /// <summary>
    /// GUID分配器：给任意类型的元素分配唯一的GUID
    /// </summary>
    template<typename T>
    class GuidAllocator
    {
    public:
        //查看GUID是否有效
        static bool isValidGuid(size_t guid) { return guid != s_invalid_guid; }

        //分配GUID给T类型
        size_t allocGuid(const T& t){
            auto find_it = m_elements_guid_map.find(t);
            if (find_it != m_elements_guid_map.end())//如果找到t的ID，直接返回ID
            {
                return find_it->second;
            }

            //如果没找到t的id，找一个没有分配的GUID，分配给t,成功后返回ID
            for (size_t i = 0; i < m_guid_elements_map.size() + 1; i++)
            {
                size_t guid = i + 1;
                if (m_guid_elements_map.find(guid) == m_guid_elements_map.end())
                {
                    m_guid_elements_map.insert(std::make_pair(guid, t));
                    m_elements_guid_map.insert(std::make_pair(t, guid));
                    return guid;
                }
            }

            return s_invalid_guid;
        }

        //根据GUID找对应元素
        bool getGuidRelatedElement(size_t guid, T& t)
        {
            auto find_it = m_guid_elements_map.find(guid);
            if (find_it != m_guid_elements_map.end())
            {
                t = find_it->second;
                return true;
            }
            return false;
        }

        //根据元素查对应的GUID
        bool getElementGuid(const T& t, size_t& guid)
        {
            auto find_it = m_elements_guid_map.find(t);
            if (find_it != m_elements_guid_map.end())
            {
                guid = find_it->second;
                return true;
            }
            return false;
        }

        bool hasElement(const T& t) { return m_elements_guid_map.find(t) != m_elements_guid_map.end(); }//查询是否有这个元素

        //删掉GUID,同时也删掉对应元素
        void freeGuid(size_t guid)
        {
            auto find_it = m_guid_elements_map.find(guid);
            if (find_it != m_guid_elements_map.end())
            {
                const auto& ele = find_it->second;
                m_elements_guid_map.erase(ele);
                m_guid_elements_map.erase(guid);
            }
        }
        void freeElement(const T& t)
        {
            auto find_it = m_elements_guid_map.find(t);
            if (find_it != m_elements_guid_map.end())
            {
                const auto& guid = find_it->second;
                m_elements_guid_map.erase(t);
                m_guid_elements_map.erase(guid);
            }
        }

        //返回T类型的所有GUID
        std::vector<size_t> getAllocatedGuids() const
        {
            std::vector<size_t> allocated_guids;
            for (const auto& ele : m_guid_elements_map)
            {
                allocated_guids.push_back(ele.first);
            }
            return allocated_guids;
        }

        //清除map
        void clear()
        {
            m_elements_guid_map.clear();
            m_guid_elements_map.clear();
        }

    private:
        std::unordered_map<T, size_t> m_elements_guid_map;
        std::unordered_map<size_t, T> m_guid_elements_map;
    };

}