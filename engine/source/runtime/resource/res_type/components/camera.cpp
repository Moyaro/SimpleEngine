#include "runtime/resource/res_type/components/camera.h"


namespace SimpleEngine
{
    CameraComponentRes::CameraComponentRes(const CameraComponentRes& res)
    {
        const std::string& camera_type_name = res.m_parameter.getTypeName();
        if (camera_type_name == "FirstPersonCameraParameter")
        {
            m_parameter = ENGINE_REFLECTION_NEW(FirstPersonCameraParameter);
            ENGINE_REFLECTION_DEEP_COPY(FirstPersonCameraParameter, m_parameter, res.m_parameter);
        }
        else if (camera_type_name == "ThirdPersonCameraParameter")
        {
            m_parameter = ENGINE_REFLECTION_NEW(ThirdPersonCameraParameter);
            ENGINE_REFLECTION_DEEP_COPY(ThirdPersonCameraParameter, m_parameter, res.m_parameter);
        }
        else if (camera_type_name == "FreeCameraParameter")
        {
            m_parameter = ENGINE_REFLECTION_NEW(FreeCameraParameter);
            ENGINE_REFLECTION_DEEP_COPY(FreeCameraParameter, m_parameter, res.m_parameter);
        }
        else
        {
            
        }
    }

    CameraComponentRes::~CameraComponentRes() { ENGINE_REFLECTION_DELETE(m_parameter); }
} // namespace SimpleEngine