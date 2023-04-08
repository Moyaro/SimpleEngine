#pragma once

#include "runtime/core/math/math_headers.h"
#include <mutex>

namespace SimpleEngine {
    enum class RenderCameraType : int
    {
        Editor,//�༭ģʽ
        Motor//�˶�ģʽ
    };

    class RenderCamera
    {
    public:
        //�������
        RenderCameraType m_current_camera_type{ RenderCameraType::Editor };
        void setCurrentCameraType(RenderCameraType type);

        static const Vector3 X, Y, Z;//��

        Vector3    m_position{ 0.0f, 0.0f, 0.0f };//λ��
        Quaternion m_rotation{ Quaternion::IDENTITY };//��ת����
        Quaternion m_invRotation{ Quaternion::IDENTITY };//��ת����������

        //��ȡλ�á���ת��Ϣ
        Vector3    position() const { return m_position; }
        Quaternion rotation() const { return m_rotation; }

        //����Զ�ü�ƽ���������Զ��
        float      m_znear{ 0.1f };
        float      m_zfar{ 1000.0f };

        //��ʾ�ϵ���
        Vector3    m_up_axis{ Z };

        //��׶����ֱ������ſ��Ƕ�
        static constexpr float MIN_FOV{ 10.0f };
        static constexpr float MAX_FOV{ 89.0f };

        static constexpr int   MAIN_VIEW_MATRIX_INDEX{ 0 };//���۲��������
        std::vector<Matrix4x4> m_view_matrices{ Matrix4x4::IDENTITY };//�۲��������
        void setMainViewMatrix(const Matrix4x4& view_matrix, RenderCameraType type = RenderCameraType::Editor);//�������۲����

        //Motorģʽ��
        void move(Vector3 delta) { m_position += delta; }//�ƶ�
        void rotate(Vector2 delta);//��ת
        void zoom(float offset);//��������ӽ�
        void lookAt(const Vector3& position, const Vector3& target, const Vector3& up);//�����������

        void setAspect(float aspect);//���ÿ�߱�
        void setFOVx(float fovx) { m_fovx = fovx; }//�������ˮƽ�ӽ�

        //�ң�X�ᣬǰ��Y�ᣬ�ϣ�Z��
        Vector3  forward() const { return (m_invRotation * Y); }
        Vector3  up() const { return (m_invRotation * Z); }
        Vector3  right() const { return (m_invRotation * X); }


        Vector2  getFOV() const { return { m_fovx, m_fovy }; }
        float getFovYDeprecated() const { return m_fovy; }

        //��ȡ����
        Matrix4x4 getViewMatrix();
        Matrix4x4 getPersProjMatrix() const;
        Matrix4x4 getLookAtMatrix() const { return Math::makeLookAtMatrix(position(), position() + forward(), up()); }

        

    protected:
        float m_aspect{ 0.f };//��߱�
        float m_fovx{ Degree(89.f).valueDegrees() };
        float m_fovy{ 0.f };

        std::mutex m_mutex;
    };

    inline const Vector3 RenderCamera::X = { 1.0f, 0.0f, 0.0f };
    inline const Vector3 RenderCamera::Y = { 0.0f, 1.0f, 0.0f };
    inline const Vector3 RenderCamera::Z = { 0.0f, 0.0f, 1.0f };
}