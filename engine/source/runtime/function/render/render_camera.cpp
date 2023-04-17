#include "render_camera.h"

namespace SimpleEngine {
    void RenderCamera::setCurrentCameraType(RenderCameraType type)
    {
        std::lock_guard<std::mutex> lock_guard(m_mutex);
        m_current_camera_type = type;
    }

    void RenderCamera::setMainViewMatrix(const Matrix4x4& view_matrix, RenderCameraType type)
    {
        std::lock_guard<std::mutex> lock_guard(m_mutex);
        m_current_camera_type = type;
        m_view_matrices[MAIN_VIEW_MATRIX_INDEX] = view_matrix;

        Vector3 s = Vector3(view_matrix[0][0], view_matrix[0][1], view_matrix[0][2]);
        Vector3 u = Vector3(view_matrix[1][0], view_matrix[1][1], view_matrix[1][2]);
        Vector3 f = Vector3(-view_matrix[2][0], -view_matrix[2][1], -view_matrix[2][2]);
        m_position = s * (-view_matrix[0][3]) + u * (-view_matrix[1][3]) + f * view_matrix[2][3];
    }

    Matrix4x4 RenderCamera::getViewMatrix()
    {
        std::lock_guard<std::mutex> lock_guard(m_mutex);
        auto view_matrix = Matrix4x4::IDENTITY;
        switch (m_current_camera_type)
        {
        case RenderCameraType::Editor:
            view_matrix = Math::makeLookAtMatrix(position(), position() + forward(), up());//观察者位置，目标位置，向上向量
            break;
        case RenderCameraType::Motor:
            view_matrix = m_view_matrices[MAIN_VIEW_MATRIX_INDEX];
            break;
        default:
            break;
        }
        return view_matrix;
    }

    Matrix4x4 RenderCamera::getPersProjMatrix() const
    {
        Matrix4x4 fix_mat(1, 0, 0, 0,  0, -1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);//修正裁剪坐标Y轴是反转的问题
        Matrix4x4 proj_mat = fix_mat * Math::makePerspectiveMatrix(Radian(Degree(m_fovy)), m_aspect, m_znear, m_zfar);
        //Matrix4x4 proj_mat = fix_mat * Math::makeOrthographicProjectionMatrix(100,100,100,100,m_znear, m_zfar);

        return proj_mat;
    }

    void RenderCamera::setAspect(float aspect)
    {
        m_aspect = aspect;

        // 1 / tan(fovy * 0.5) / aspect = 1 / tan(fovx * 0.5)
        // 1 / tan(fovy * 0.5) = aspect / tan(fovx * 0.5)
        // tan(fovy * 0.5) = tan(fovx * 0.5) / aspect

        m_fovy = Radian(Math::atan(Math::tan(Radian(Degree(m_fovx) * 0.5f)) / m_aspect) * 2.0f).valueDegrees();
    }

    void RenderCamera::lookAt(const Vector3& position, const Vector3& target, const Vector3& up)
    {
        m_position = position;
        Vector3 forward = (target - position).normalisedCopy();//计算出相机朝向，并归一化
        m_rotation = forward.getRotationTo(Y);//朝向->Y轴的旋转矩阵

        Vector3 right = forward.crossProduct(up.normalisedCopy()).normalisedCopy();//通过叉积、归一化获取右方向向量
        Vector3 orthUp = right.crossProduct(forward);//上方向向量

        Quaternion upRotation = (m_rotation * orthUp).getRotationTo(Z);//

        //得到最终旋转矩阵
        m_rotation = Quaternion(upRotation) * m_rotation;
        m_invRotation = m_rotation.conjugate();
    }

    //*************************************移动**************************************************//
    void RenderCamera::rotate(Vector2 delta)
    {
        // rotation around x, y axis
        delta = Vector2(Radian(Degree(delta.x)).valueRadians(), Radian(Degree(delta.y)).valueRadians());

        // limit pitch
        float dot = m_up_axis.dotProduct(forward());
        if ((dot < -0.99f && delta.x > 0.0f) || // angle nearing 180 degrees
            (dot > 0.99f && delta.x < 0.0f))    // angle nearing 0 degrees
            delta.x = 0.0f;

        // pitch is relative to current sideways rotation
        // yaw happens independently
        // this prevents roll
        Quaternion pitch, yaw;
        pitch.fromAngleAxis(Radian(delta.x), X);
        yaw.fromAngleAxis(Radian(delta.y), Z);

        m_rotation = pitch * m_rotation * yaw;

        m_invRotation = m_rotation.conjugate();
    }

    void RenderCamera::zoom(float offset)
    {
        // > 0 = zoom in (decrease FOV by <offset> angles)
        m_fovx = Math::clamp(m_fovx - offset, MIN_FOV, MAX_FOV);
    }
}