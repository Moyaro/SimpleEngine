#pragma once

#include "runtime/function/framework/component/component.h"

#include "runtime/resource/res_type/components/mesh.h"

#include "runtime/function/render/render_object.h"

#include <vector>

namespace SimpleEngine
{
    class RenderSwapContext;

    REFLECTION_TYPE(MeshComponent)
        CLASS(MeshComponent : public Component, WhiteListFields)
    {
        REFLECTION_BODY(MeshComponent)
    public:
        MeshComponent() {};

        void postLoadResource(std::weak_ptr<GObject> parent_object) override;//设置父物体，遍历所有网格资源,从中获取信息后放入网格描述信息里

        const std::vector<GameObjectPartDesc>& getRawMeshes() const { return m_raw_meshes; }

        void tick(float delta_time) override;

    private:
        META(Enable)
            MeshComponentRes m_mesh_res;//网格组件资源：子网格vector
        std::vector<GameObjectPartDesc> m_raw_meshes;//一堆网格组件信息
    };
}