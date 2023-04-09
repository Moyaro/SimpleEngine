#include "level_debugger.h"
#include "runtime/core/meta/reflection/reflection.h"
#include "runtime/engine.h"
#include "runtime/function/framework/component/camera/camera_component.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/function/framework/component/transform/transform_component.h"

#include "runtime/resource/asset_manager/asset_manager.h"

#include "runtime/function/global/global_context.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/function/render/render_debug_config.h"

namespace SimpleEngine {

    void LevelDebugger::tick(std::shared_ptr<Level> level) const
    {
        if (g_is_editor_mode) return;
        if (g_runtime_global_context.m_render_debug_config->gameObject.show_bounding_box) showAllBoundingBox(level);
        if (g_runtime_global_context.m_render_debug_config->camera.show_runtime_info) showCameraInfo(level);
    }

    void LevelDebugger::showAllBoundingBox(std::shared_ptr<Level> level) const
    {
        const LevelObjectsMap& go_map = level->getAllGObjects();
        for (const auto& gobject_pair : go_map)
        {
            drawBoundingBox(gobject_pair.second);
        }
    }

    void LevelDebugger::showBoundingBox(std::shared_ptr<Level> level, GObjectID go_id) const
    {
        std::shared_ptr<GObject> gobject = level->getGObjectByID(go_id).lock();
        drawBoundingBox(gobject);
    }

    void LevelDebugger::showCameraInfo(std::shared_ptr<Level> level) const
    {
        //std::shared_ptr<GObject> gobject = level->getCurrentActiveCharacter().lock()->getObject().lock();
        std::shared_ptr<GObject> cameraGobject = level->getCameraObject();
        drawCameraInfo(cameraGobject);
    }

    void LevelDebugger::drawBoundingBox(std::shared_ptr<GObject> object) const
    {
        //const RigidBodyComponent* rigidbody_component = object->tryGetComponentConst<RigidBodyComponent>("RigidBodyComponent");
        //if (rigidbody_component == nullptr)
        //    return;

        //std::vector<AxisAlignedBox> bounding_boxes;
        //rigidbody_component->getShapeBoundingBoxes(bounding_boxes);
        //for (size_t bounding_box_index = 0; bounding_box_index < bounding_boxes.size(); bounding_box_index++)
        //{
        //    AxisAlignedBox  bounding_box = bounding_boxes[bounding_box_index];
        //    DebugDrawGroup* debug_draw_group =
        //        g_runtime_global_context.m_debugdraw_manager->tryGetOrCreateDebugDrawGroup("bounding box");
        //    Vector3 center =
        //        Vector3(bounding_box.getCenter().x, bounding_box.getCenter().y, bounding_box.getCenter().z);
        //    Vector3 halfExtent =
        //        Vector3(bounding_box.getHalfExtent().x, bounding_box.getHalfExtent().y, bounding_box.getHalfExtent().z);

        //    debug_draw_group->addBox(center, halfExtent, Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        //}
    }

    void LevelDebugger::drawCameraInfo(std::shared_ptr<GObject> object) const
    {
        const CameraComponent* camera_component = object->tryGetComponentConst<CameraComponent>("CameraComponent");
        if (camera_component == nullptr)
            return;

        DebugDrawGroup* debug_draw_group =
            g_runtime_global_context.m_debugdraw_manager->tryGetOrCreateDebugDrawGroup("show camera info");

        std::ostringstream buffer;
        buffer << "camera mode: ";
        switch (camera_component->getCameraMode())
        {
        case CameraMode::first_person:
            buffer << "first person";
            break;
        case CameraMode::third_person:
            buffer << "third person";
            break;
        case CameraMode::free:
            buffer << "free";
            break;
        case CameraMode::invalid:
            buffer << "invalid";
            break;
        }
        buffer << std::endl;

        Vector3 position = camera_component->getPosition();
        Vector3 forward = camera_component->getForward();
        Vector3 direction = forward - position;
        buffer << "camera position: (" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
        buffer << "camera direction : (" << direction.x << "," << direction.y << "," << direction.z << ")";
        debug_draw_group->addText(buffer.str(), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector3(-1.0f, -0.2f, 0.0f), 10, true);
    }
}