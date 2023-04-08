#pragma once

namespace SimpleEngine
{
    /// <summary>
    /// ������������Ϣ
    /// </summary>
    class RenderDebugConfig
    {
    public:
        struct Camera
        {
            bool show_runtime_info = false;
        };
        struct GameObject
        {
            bool show_bounding_box = false;
        };

        Camera camera;
        GameObject gameObject;
    };
}