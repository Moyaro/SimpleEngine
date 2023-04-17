#pragma once

#include "runtime/core/math/vector3.h"

#include "runtime/resource/res_type/components/camera.h"

#include "runtime/function/framework/component/component.h"

namespace SimpleEngine
{
    class RenderCamera;

    enum class CameraMode : unsigned char
    {
        third_person,//第三人称
        first_person,//第一人称
        free,//自由视角
        invalid
    };

    REFLECTION_TYPE(CameraComponent)
    CLASS(CameraComponent : public Component, WhiteListFields)
    {
        REFLECTION_BODY(CameraComponent)

    public:
        CameraComponent() = default;

        void postLoadResource(std::weak_ptr<GObject> parent_object) override;

        void tick(float delta_time) override;

        CameraMode getCameraMode() const { return m_camera_mode; }
        void setCameraMode(CameraMode mode) { m_camera_mode = mode; }
        Vector3 getPosition() const { return m_position; }
        Vector3 getForward() const { return m_forward; }

    private:
        void tickFirstPersonCamera(float delta_time);
        void tickThirdPersonCamera(float delta_time);
        void tickFreeCamera(float delta_time);

        META(Enable)
        CameraComponentRes m_camera_res;//相机资源
        CameraMode m_camera_mode {CameraMode::invalid};//相机模式
        Vector3 m_position;//位置

        Vector3 m_forward {Vector3::NEGATIVE_UNIT_Y};
        Vector3 m_up {Vector3::UNIT_Z};
        Vector3 m_left {Vector3::UNIT_X};
    };
} // namespace Piccolo
