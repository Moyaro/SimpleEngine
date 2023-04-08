#pragma once
#include "runtime/function/framework/level/level.h"
#include "runtime/function/framework/object/object.h"

namespace SimpleEngine
{
    /// <summary>
    /// 配合debug_draw
    /// </summary>
    class LevelDebugger
    {
    public:
        void tick(std::shared_ptr<Level> level) const;//查看调试器信息，做出对应回应

        void showAllBoundingBox(std::shared_ptr<Level> level) const;
        void showBoundingBox(std::shared_ptr<Level> level, GObjectID go_id) const;

        void showCameraInfo(std::shared_ptr<Level> level) const;

    private:
        void drawBoundingBox(std::shared_ptr<GObject> object) const;
        void drawCameraInfo(std::shared_ptr<GObject> object) const;
    };
}