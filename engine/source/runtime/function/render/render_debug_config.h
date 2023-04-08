#pragma once

namespace SimpleEngine
{
    /// <summary>
    /// 调试用配置信息
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