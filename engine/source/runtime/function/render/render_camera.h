#pragma once

#include "runtime/core/math/math_headers.h"
#include <mutex>

namespace SimpleEngine {
    enum class RenderCameraType : int
    {
        Editor,//编辑模式
        Motor//运动模式
    };

    class RenderCamera
    {
    public:
        //相机类型
        RenderCameraType m_current_camera_type{ RenderCameraType::Editor };
        void setCurrentCameraType(RenderCameraType type);

        static const Vector3 X, Y, Z;//轴

        Vector3    m_position{ 0.0f, 0.0f, 0.0f };//位置
        Quaternion m_rotation{ Quaternion::IDENTITY };//旋转矩阵
        Quaternion m_invRotation{ Quaternion::IDENTITY };//旋转矩阵的逆矩阵

        //获取位置、旋转信息
        Vector3    position() const { return m_position; }
        Quaternion rotation() const { return m_rotation; }

        //近和远裁剪平面离相机的远近
        float      m_znear{ 0.1f };
        float      m_zfar{ 1000.0f };

        //表示上的轴
        Vector3    m_up_axis{ Z };

        //视锥体竖直方向的张开角度
        static constexpr float MIN_FOV{ 10.0f };
        static constexpr float MAX_FOV{ 89.0f };

        static constexpr int   MAIN_VIEW_MATRIX_INDEX{ 0 };//主观察矩阵索引
        std::vector<Matrix4x4> m_view_matrices{ Matrix4x4::IDENTITY };//观察矩阵数组
        void setMainViewMatrix(const Matrix4x4& view_matrix, RenderCameraType type = RenderCameraType::Editor);//设置主观察矩阵

        //Motor模式用
        void move(Vector3 delta) { m_position += delta; }//移动
        void rotate(Vector2 delta);//旋转
        void zoom(float offset);//调整相机视角
        void lookAt(const Vector3& position, const Vector3& target, const Vector3& up);//设置相机朝向

        void setAspect(float aspect);//设置宽高比
        void setFOVx(float fovx) { m_fovx = fovx; }//设置相机水平视角

        //右：X轴，前：Y轴，上：Z轴
        Vector3  forward() const { return (m_invRotation * Y); }
        Vector3  up() const { return (m_invRotation * Z); }
        Vector3  right() const { return (m_invRotation * X); }


        Vector2  getFOV() const { return { m_fovx, m_fovy }; }
        float getFovYDeprecated() const { return m_fovy; }

        //获取矩阵
        Matrix4x4 getViewMatrix();
        Matrix4x4 getPersProjMatrix() const;
        Matrix4x4 getLookAtMatrix() const { return Math::makeLookAtMatrix(position(), position() + forward(), up()); }

        

    protected:
        float m_aspect{ 0.f };//宽高比
        float m_fovx{ Degree(89.f).valueDegrees() };
        float m_fovy{ 0.f };

        std::mutex m_mutex;
    };

    inline const Vector3 RenderCamera::X = { 1.0f, 0.0f, 0.0f };
    inline const Vector3 RenderCamera::Y = { 0.0f, 1.0f, 0.0f };
    inline const Vector3 RenderCamera::Z = { 0.0f, 0.0f, 1.0f };
}