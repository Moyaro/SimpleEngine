#pragma once

#include <stdexcept>
#include <vector>
#include "runtime/function/global/global_context.h"
#include "runtime/resource/config_manager/config_manager.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/render/interface/rhi.h"

namespace SimpleEngine
{

    class DebugDrawFont
    {
    public:
        void init(){ loadFont(); }//��������Դ�ļ�
        void destroy();

        void getCharacterTextureRect(const unsigned char character, float& x1, float& y1, float& x2, float& y2);

        VkImageView getImageView() const { return m_font_imageView; }
    private:
        const unsigned char m_range_l = 32, m_range_r = 126;

        //�ֿ��
        const int m_singleCharacterWidth = 32;
        const int m_singleCharacterHeight = 64;

        const int m_numOfCharacterInOneLine = 16;//һ�е�����
        const int m_numOfCharacter = (m_range_r - m_range_l + 1);

        const int m_bitmap_w = m_singleCharacterWidth * m_numOfCharacterInOneLine;
        const int m_bitmap_h = m_singleCharacterHeight * ((m_numOfCharacter + m_numOfCharacterInOneLine - 1) / m_numOfCharacterInOneLine);

        VkImage m_font_image;
        VkImageView m_font_imageView;
        VkDeviceMemory m_font_imageMemory;
        VmaAllocation m_allocation;

        void loadFont();

    };
}