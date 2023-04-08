#pragma once
#include "runtime/core/meta/reflection/reflection.h"
#include "_generated/serializer/all_serializer.h"
#include "_generated\reflection\quaternion.reflection.gen.h"
#include "_generated\reflection\axis_aligned.reflection.gen.h"
#include "_generated\reflection\vector3.reflection.gen.h"
#include "_generated\reflection\transform.reflection.gen.h"
#include "_generated\reflection\color.reflection.gen.h"
#include "_generated\reflection\vector4.reflection.gen.h"
#include "_generated\reflection\skeleton_data.reflection.gen.h"
#include "_generated\reflection\vector2.reflection.gen.h"
#include "_generated\reflection\skeleton_mask.reflection.gen.h"
#include "_generated\reflection\matrix4.reflection.gen.h"
#include "_generated\reflection\component.reflection.gen.h"
#include "_generated\reflection\meta_example.reflection.gen.h"
#include "_generated\reflection\camera.reflection.gen.h"
#include "_generated\reflection\camera_component.reflection.gen.h"
#include "_generated\reflection\material.reflection.gen.h"
#include "_generated\reflection\mesh_component.reflection.gen.h"
#include "_generated\reflection\mesh.reflection.gen.h"
#include "_generated\reflection\render_object.reflection.gen.h"
#include "_generated\reflection\object.reflection.gen.h"
#include "_generated\reflection\level.reflection.gen.h"
#include "_generated\reflection\transform_component.reflection.gen.h"
#include "_generated\reflection\world.reflection.gen.h"
#include "_generated\reflection\camera_config.reflection.gen.h"
#include "_generated\reflection\global_rendering.reflection.gen.h"
#include "_generated\reflection\animation_skeleton_node_map.reflection.gen.h"
#include "_generated\reflection\basic_shape.reflection.gen.h"
#include "_generated\reflection\rigid_body.reflection.gen.h"
#include "_generated\reflection\mesh_data.reflection.gen.h"
#include "_generated\reflection\animation_clip.reflection.gen.h"
#include "_generated\reflection\global_particle.reflection.gen.h"
#include "_generated\reflection\blend_state.reflection.gen.h"
#include "_generated\reflection\emitter.reflection.gen.h"
#include "_generated\reflection\animation.reflection.gen.h"
#include "_generated\reflection\motor.reflection.gen.h"

namespace SimpleEngine{
namespace Reflection{
    void TypeMetaRegister::metaRegister(){
TypeWrappersRegister::Quaternion();
TypeWrappersRegister::AxisAligned();
TypeWrappersRegister::Vector3();
TypeWrappersRegister::Transform();
TypeWrappersRegister::Color();
TypeWrappersRegister::Vector4();
TypeWrappersRegister::SkeletonData();
TypeWrappersRegister::Vector2();
TypeWrappersRegister::SkeletonMask();
TypeWrappersRegister::Matrix4();
TypeWrappersRegister::Component();
TypeWrappersRegister::MetaExample();
TypeWrappersRegister::Camera();
TypeWrappersRegister::CameraComponent();
TypeWrappersRegister::Material();
TypeWrappersRegister::MeshComponent();
TypeWrappersRegister::Mesh();
TypeWrappersRegister::RenderObject();
TypeWrappersRegister::Object();
TypeWrappersRegister::Level();
TypeWrappersRegister::TransformComponent();
TypeWrappersRegister::World();
TypeWrappersRegister::CameraConfig();
TypeWrappersRegister::GlobalRendering();
TypeWrappersRegister::AnimationSkeletonNodeMap();
TypeWrappersRegister::BasicShape();
TypeWrappersRegister::RigidBody();
TypeWrappersRegister::MeshData();
TypeWrappersRegister::AnimationClip();
TypeWrappersRegister::GlobalParticle();
TypeWrappersRegister::BlendState();
TypeWrappersRegister::Emitter();
TypeWrappersRegister::Animation();
TypeWrappersRegister::Motor();
    }
}
}

