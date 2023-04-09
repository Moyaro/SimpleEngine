#pragma once
#include "_generated\serializer\motor.serializer.gen.h"
#include "_generated\serializer\quaternion.serializer.gen.h"
#include "_generated\serializer\vector3.serializer.gen.h"
#include "_generated\serializer\axis_aligned.serializer.gen.h"
#include "_generated\serializer\transform.serializer.gen.h"
#include "_generated\serializer\color.serializer.gen.h"
#include "_generated\serializer\vector4.serializer.gen.h"
#include "_generated\serializer\animation_skeleton_node_map.serializer.gen.h"
#include "_generated\serializer\matrix4.serializer.gen.h"
#include "_generated\serializer\vector2.serializer.gen.h"
#include "_generated\serializer\meta_example.serializer.gen.h"
#include "_generated\serializer\camera.serializer.gen.h"
#include "_generated\serializer\component.serializer.gen.h"
#include "_generated\serializer\material.serializer.gen.h"
#include "_generated\serializer\camera_component.serializer.gen.h"
#include "_generated\serializer\mesh.serializer.gen.h"
#include "_generated\serializer\animation.serializer.gen.h"
#include "_generated\serializer\render_object.serializer.gen.h"
#include "_generated\serializer\mesh_component.serializer.gen.h"
#include "_generated\serializer\object.serializer.gen.h"
#include "_generated\serializer\transform_component.serializer.gen.h"
#include "_generated\serializer\world.serializer.gen.h"
#include "_generated\serializer\camera_config.serializer.gen.h"
#include "_generated\serializer\emitter.serializer.gen.h"
#include "_generated\serializer\global_rendering.serializer.gen.h"
#include "_generated\serializer\basic_shape.serializer.gen.h"
#include "_generated\serializer\animation_clip.serializer.gen.h"
#include "_generated\serializer\blend_state.serializer.gen.h"
#include "_generated\serializer\skeleton_data.serializer.gen.h"
#include "_generated\serializer\skeleton_mask.serializer.gen.h"
#include "_generated\serializer\level.serializer.gen.h"
#include "_generated\serializer\rigid_body.serializer.gen.h"
#include "_generated\serializer\mesh_data.serializer.gen.h"
#include "_generated\serializer\global_particle.serializer.gen.h"
namespace SimpleEngine{
    template<>
    Json Serializer::write(const ControllerConfig& instance){
        Json::object  ret_context;
        
        
        return  Json(ret_context);
    }
    template<>
    ControllerConfig& Serializer::read(const Json& json_context, ControllerConfig& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    Json Serializer::write(const PhysicsControllerConfig& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::ControllerConfig*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("capsule_shape", Serializer::write(instance.m_capsule_shape));
        return  Json(ret_context);
    }
    template<>
    PhysicsControllerConfig& Serializer::read(const Json& json_context, PhysicsControllerConfig& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::ControllerConfig*)&instance);
        if(!json_context["capsule_shape"].is_null()){
            Serializer::read(json_context["capsule_shape"], instance.m_capsule_shape);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const MotorComponentRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("move_speed", Serializer::write(instance.m_move_speed));
        ret_context.insert_or_assign("jump_height", Serializer::write(instance.m_jump_height));
        ret_context.insert_or_assign("max_move_speed_ratio", Serializer::write(instance.m_max_move_speed_ratio));
        ret_context.insert_or_assign("max_sprint_speed_ratio", Serializer::write(instance.m_max_sprint_speed_ratio));
        ret_context.insert_or_assign("move_acceleration", Serializer::write(instance.m_move_acceleration));
        ret_context.insert_or_assign("sprint_acceleration", Serializer::write(instance.m_sprint_acceleration));
        ret_context.insert_or_assign("controller_config", Serializer::write(instance.m_controller_config));
        return  Json(ret_context);
    }
    template<>
    MotorComponentRes& Serializer::read(const Json& json_context, MotorComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["move_speed"].is_null()){
            Serializer::read(json_context["move_speed"], instance.m_move_speed);
        }
        if(!json_context["jump_height"].is_null()){
            Serializer::read(json_context["jump_height"], instance.m_jump_height);
        }
        if(!json_context["max_move_speed_ratio"].is_null()){
            Serializer::read(json_context["max_move_speed_ratio"], instance.m_max_move_speed_ratio);
        }
        if(!json_context["max_sprint_speed_ratio"].is_null()){
            Serializer::read(json_context["max_sprint_speed_ratio"], instance.m_max_sprint_speed_ratio);
        }
        if(!json_context["move_acceleration"].is_null()){
            Serializer::read(json_context["move_acceleration"], instance.m_move_acceleration);
        }
        if(!json_context["sprint_acceleration"].is_null()){
            Serializer::read(json_context["sprint_acceleration"], instance.m_sprint_acceleration);
        }
        if(!json_context["controller_config"].is_null()){
            Serializer::read(json_context["controller_config"], instance.m_controller_config);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Quaternion& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("w", Serializer::write(instance.w));
        ret_context.insert_or_assign("x", Serializer::write(instance.x));
        ret_context.insert_or_assign("y", Serializer::write(instance.y));
        ret_context.insert_or_assign("z", Serializer::write(instance.z));
        return  Json(ret_context);
    }
    template<>
    Quaternion& Serializer::read(const Json& json_context, Quaternion& instance){
        assert(json_context.is_object());
        
        if(!json_context["w"].is_null()){
            Serializer::read(json_context["w"], instance.w);
        }
        if(!json_context["x"].is_null()){
            Serializer::read(json_context["x"], instance.x);
        }
        if(!json_context["y"].is_null()){
            Serializer::read(json_context["y"], instance.y);
        }
        if(!json_context["z"].is_null()){
            Serializer::read(json_context["z"], instance.z);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Vector3& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("x", Serializer::write(instance.x));
        ret_context.insert_or_assign("y", Serializer::write(instance.y));
        ret_context.insert_or_assign("z", Serializer::write(instance.z));
        return  Json(ret_context);
    }
    template<>
    Vector3& Serializer::read(const Json& json_context, Vector3& instance){
        assert(json_context.is_object());
        
        if(!json_context["x"].is_null()){
            Serializer::read(json_context["x"], instance.x);
        }
        if(!json_context["y"].is_null()){
            Serializer::read(json_context["y"], instance.y);
        }
        if(!json_context["z"].is_null()){
            Serializer::read(json_context["z"], instance.z);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AxisAlignedBox& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("center", Serializer::write(instance.m_center));
        ret_context.insert_or_assign("half_extent", Serializer::write(instance.m_half_extent));
        ret_context.insert_or_assign("min_corner", Serializer::write(instance.m_min_corner));
        ret_context.insert_or_assign("max_corner", Serializer::write(instance.m_max_corner));
        return  Json(ret_context);
    }
    template<>
    AxisAlignedBox& Serializer::read(const Json& json_context, AxisAlignedBox& instance){
        assert(json_context.is_object());
        
        if(!json_context["center"].is_null()){
            Serializer::read(json_context["center"], instance.m_center);
        }
        if(!json_context["half_extent"].is_null()){
            Serializer::read(json_context["half_extent"], instance.m_half_extent);
        }
        if(!json_context["min_corner"].is_null()){
            Serializer::read(json_context["min_corner"], instance.m_min_corner);
        }
        if(!json_context["max_corner"].is_null()){
            Serializer::read(json_context["max_corner"], instance.m_max_corner);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Transform& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("position", Serializer::write(instance.m_position));
        ret_context.insert_or_assign("scale", Serializer::write(instance.m_scale));
        ret_context.insert_or_assign("rotation", Serializer::write(instance.m_rotation));
        return  Json(ret_context);
    }
    template<>
    Transform& Serializer::read(const Json& json_context, Transform& instance){
        assert(json_context.is_object());
        
        if(!json_context["position"].is_null()){
            Serializer::read(json_context["position"], instance.m_position);
        }
        if(!json_context["scale"].is_null()){
            Serializer::read(json_context["scale"], instance.m_scale);
        }
        if(!json_context["rotation"].is_null()){
            Serializer::read(json_context["rotation"], instance.m_rotation);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Color& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("r", Serializer::write(instance.r));
        ret_context.insert_or_assign("g", Serializer::write(instance.g));
        ret_context.insert_or_assign("b", Serializer::write(instance.b));
        return  Json(ret_context);
    }
    template<>
    Color& Serializer::read(const Json& json_context, Color& instance){
        assert(json_context.is_object());
        
        if(!json_context["r"].is_null()){
            Serializer::read(json_context["r"], instance.r);
        }
        if(!json_context["g"].is_null()){
            Serializer::read(json_context["g"], instance.g);
        }
        if(!json_context["b"].is_null()){
            Serializer::read(json_context["b"], instance.b);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Vector4& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("x", Serializer::write(instance.x));
        ret_context.insert_or_assign("y", Serializer::write(instance.y));
        ret_context.insert_or_assign("z", Serializer::write(instance.z));
        ret_context.insert_or_assign("w", Serializer::write(instance.w));
        return  Json(ret_context);
    }
    template<>
    Vector4& Serializer::read(const Json& json_context, Vector4& instance){
        assert(json_context.is_object());
        
        if(!json_context["x"].is_null()){
            Serializer::read(json_context["x"], instance.x);
        }
        if(!json_context["y"].is_null()){
            Serializer::read(json_context["y"], instance.y);
        }
        if(!json_context["z"].is_null()){
            Serializer::read(json_context["z"], instance.z);
        }
        if(!json_context["w"].is_null()){
            Serializer::read(json_context["w"], instance.w);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimSkelMap& instance){
        Json::object  ret_context;
        
        Json::array convert_json;
        for (auto& item : instance.convert){
            convert_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("convert",convert_json);
        
        return  Json(ret_context);
    }
    template<>
    AnimSkelMap& Serializer::read(const Json& json_context, AnimSkelMap& instance){
        assert(json_context.is_object());
        
        if(!json_context["convert"].is_null()){
            assert(json_context["convert"].is_array());
            Json::array array_convert = json_context["convert"].array_items();
            instance.convert.resize(array_convert.size());
            for (size_t index=0; index < array_convert.size();++index){
                Serializer::read(array_convert[index], instance.convert[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Matrix4x4_& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("v0", Serializer::write(instance.v0));
        ret_context.insert_or_assign("v1", Serializer::write(instance.v1));
        ret_context.insert_or_assign("v2", Serializer::write(instance.v2));
        ret_context.insert_or_assign("v3", Serializer::write(instance.v3));
        ret_context.insert_or_assign("v4", Serializer::write(instance.v4));
        ret_context.insert_or_assign("v5", Serializer::write(instance.v5));
        ret_context.insert_or_assign("v6", Serializer::write(instance.v6));
        ret_context.insert_or_assign("v7", Serializer::write(instance.v7));
        ret_context.insert_or_assign("v8", Serializer::write(instance.v8));
        ret_context.insert_or_assign("v9", Serializer::write(instance.v9));
        ret_context.insert_or_assign("v10", Serializer::write(instance.v10));
        ret_context.insert_or_assign("v11", Serializer::write(instance.v11));
        ret_context.insert_or_assign("v12", Serializer::write(instance.v12));
        ret_context.insert_or_assign("v13", Serializer::write(instance.v13));
        ret_context.insert_or_assign("v14", Serializer::write(instance.v14));
        ret_context.insert_or_assign("v15", Serializer::write(instance.v15));
        return  Json(ret_context);
    }
    template<>
    Matrix4x4_& Serializer::read(const Json& json_context, Matrix4x4_& instance){
        assert(json_context.is_object());
        
        if(!json_context["v0"].is_null()){
            Serializer::read(json_context["v0"], instance.v0);
        }
        if(!json_context["v1"].is_null()){
            Serializer::read(json_context["v1"], instance.v1);
        }
        if(!json_context["v2"].is_null()){
            Serializer::read(json_context["v2"], instance.v2);
        }
        if(!json_context["v3"].is_null()){
            Serializer::read(json_context["v3"], instance.v3);
        }
        if(!json_context["v4"].is_null()){
            Serializer::read(json_context["v4"], instance.v4);
        }
        if(!json_context["v5"].is_null()){
            Serializer::read(json_context["v5"], instance.v5);
        }
        if(!json_context["v6"].is_null()){
            Serializer::read(json_context["v6"], instance.v6);
        }
        if(!json_context["v7"].is_null()){
            Serializer::read(json_context["v7"], instance.v7);
        }
        if(!json_context["v8"].is_null()){
            Serializer::read(json_context["v8"], instance.v8);
        }
        if(!json_context["v9"].is_null()){
            Serializer::read(json_context["v9"], instance.v9);
        }
        if(!json_context["v10"].is_null()){
            Serializer::read(json_context["v10"], instance.v10);
        }
        if(!json_context["v11"].is_null()){
            Serializer::read(json_context["v11"], instance.v11);
        }
        if(!json_context["v12"].is_null()){
            Serializer::read(json_context["v12"], instance.v12);
        }
        if(!json_context["v13"].is_null()){
            Serializer::read(json_context["v13"], instance.v13);
        }
        if(!json_context["v14"].is_null()){
            Serializer::read(json_context["v14"], instance.v14);
        }
        if(!json_context["v15"].is_null()){
            Serializer::read(json_context["v15"], instance.v15);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Vector2& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("x", Serializer::write(instance.x));
        ret_context.insert_or_assign("y", Serializer::write(instance.y));
        return  Json(ret_context);
    }
    template<>
    Vector2& Serializer::read(const Json& json_context, Vector2& instance){
        assert(json_context.is_object());
        
        if(!json_context["x"].is_null()){
            Serializer::read(json_context["x"], instance.x);
        }
        if(!json_context["y"].is_null()){
            Serializer::read(json_context["y"], instance.y);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const BaseTest& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("int", Serializer::write(instance.m_int));
        Json::array m_int_vector_json;
        for (auto& item : instance.m_int_vector){
            m_int_vector_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("int_vector",m_int_vector_json);
        
        return  Json(ret_context);
    }
    template<>
    BaseTest& Serializer::read(const Json& json_context, BaseTest& instance){
        assert(json_context.is_object());
        
        if(!json_context["int"].is_null()){
            Serializer::read(json_context["int"], instance.m_int);
        }
        if(!json_context["int_vector"].is_null()){
            assert(json_context["int_vector"].is_array());
            Json::array array_m_int_vector = json_context["int_vector"].array_items();
            instance.m_int_vector.resize(array_m_int_vector.size());
            for (size_t index=0; index < array_m_int_vector.size();++index){
                Serializer::read(array_m_int_vector[index], instance.m_int_vector[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Test1& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::BaseTest*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("char", Serializer::write(instance.m_char));
        return  Json(ret_context);
    }
    template<>
    Test1& Serializer::read(const Json& json_context, Test1& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::BaseTest*)&instance);
        if(!json_context["char"].is_null()){
            Serializer::read(json_context["char"], instance.m_char);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Test2& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::BaseTest*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        Json::array m_test_base_array_json;
        for (auto& item : instance.m_test_base_array){
            m_test_base_array_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("test_base_array",m_test_base_array_json);
        
        return  Json(ret_context);
    }
    template<>
    Test2& Serializer::read(const Json& json_context, Test2& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::BaseTest*)&instance);
        if(!json_context["test_base_array"].is_null()){
            assert(json_context["test_base_array"].is_array());
            Json::array array_m_test_base_array = json_context["test_base_array"].array_items();
            instance.m_test_base_array.resize(array_m_test_base_array.size());
            for (size_t index=0; index < array_m_test_base_array.size();++index){
                Serializer::read(array_m_test_base_array[index], instance.m_test_base_array[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const CameraParameter& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("fov", Serializer::write(instance.m_fov));
        return  Json(ret_context);
    }
    template<>
    CameraParameter& Serializer::read(const Json& json_context, CameraParameter& instance){
        assert(json_context.is_object());
        
        if(!json_context["fov"].is_null()){
            Serializer::read(json_context["fov"], instance.m_fov);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const FirstPersonCameraParameter& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::CameraParameter*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("vertical_offset", Serializer::write(instance.m_vertical_offset));
        return  Json(ret_context);
    }
    template<>
    FirstPersonCameraParameter& Serializer::read(const Json& json_context, FirstPersonCameraParameter& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::CameraParameter*)&instance);
        if(!json_context["vertical_offset"].is_null()){
            Serializer::read(json_context["vertical_offset"], instance.m_vertical_offset);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const ThirdPersonCameraParameter& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::CameraParameter*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("horizontal_offset", Serializer::write(instance.m_horizontal_offset));
        ret_context.insert_or_assign("vertical_offset", Serializer::write(instance.m_vertical_offset));
        return  Json(ret_context);
    }
    template<>
    ThirdPersonCameraParameter& Serializer::read(const Json& json_context, ThirdPersonCameraParameter& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::CameraParameter*)&instance);
        if(!json_context["horizontal_offset"].is_null()){
            Serializer::read(json_context["horizontal_offset"], instance.m_horizontal_offset);
        }
        if(!json_context["vertical_offset"].is_null()){
            Serializer::read(json_context["vertical_offset"], instance.m_vertical_offset);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const FreeCameraParameter& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::CameraParameter*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("speed", Serializer::write(instance.m_speed));
        return  Json(ret_context);
    }
    template<>
    FreeCameraParameter& Serializer::read(const Json& json_context, FreeCameraParameter& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::CameraParameter*)&instance);
        if(!json_context["speed"].is_null()){
            Serializer::read(json_context["speed"], instance.m_speed);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const CameraComponentRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("parameter", Serializer::write(instance.m_parameter));
        return  Json(ret_context);
    }
    template<>
    CameraComponentRes& Serializer::read(const Json& json_context, CameraComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["parameter"].is_null()){
            Serializer::read(json_context["parameter"], instance.m_parameter);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Component& instance){
        Json::object  ret_context;
        
        
        return  Json(ret_context);
    }
    template<>
    Component& Serializer::read(const Json& json_context, Component& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    Json Serializer::write(const MaterialRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("base_colour_texture_file", Serializer::write(instance.m_base_colour_texture_file));
        ret_context.insert_or_assign("metallic_roughness_texture_file", Serializer::write(instance.m_metallic_roughness_texture_file));
        ret_context.insert_or_assign("normal_texture_file", Serializer::write(instance.m_normal_texture_file));
        ret_context.insert_or_assign("occlusion_texture_file", Serializer::write(instance.m_occlusion_texture_file));
        ret_context.insert_or_assign("emissive_texture_file", Serializer::write(instance.m_emissive_texture_file));
        return  Json(ret_context);
    }
    template<>
    MaterialRes& Serializer::read(const Json& json_context, MaterialRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["base_colour_texture_file"].is_null()){
            Serializer::read(json_context["base_colour_texture_file"], instance.m_base_colour_texture_file);
        }
        if(!json_context["metallic_roughness_texture_file"].is_null()){
            Serializer::read(json_context["metallic_roughness_texture_file"], instance.m_metallic_roughness_texture_file);
        }
        if(!json_context["normal_texture_file"].is_null()){
            Serializer::read(json_context["normal_texture_file"], instance.m_normal_texture_file);
        }
        if(!json_context["occlusion_texture_file"].is_null()){
            Serializer::read(json_context["occlusion_texture_file"], instance.m_occlusion_texture_file);
        }
        if(!json_context["emissive_texture_file"].is_null()){
            Serializer::read(json_context["emissive_texture_file"], instance.m_emissive_texture_file);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const CameraComponent& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Component*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("camera_res", Serializer::write(instance.m_camera_res));
        return  Json(ret_context);
    }
    template<>
    CameraComponent& Serializer::read(const Json& json_context, CameraComponent& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Component*)&instance);
        if(!json_context["camera_res"].is_null()){
            Serializer::read(json_context["camera_res"], instance.m_camera_res);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const SubMeshRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("obj_file_ref", Serializer::write(instance.m_obj_file_ref));
        ret_context.insert_or_assign("transform", Serializer::write(instance.m_transform));
        ret_context.insert_or_assign("material", Serializer::write(instance.m_material));
        return  Json(ret_context);
    }
    template<>
    SubMeshRes& Serializer::read(const Json& json_context, SubMeshRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["obj_file_ref"].is_null()){
            Serializer::read(json_context["obj_file_ref"], instance.m_obj_file_ref);
        }
        if(!json_context["transform"].is_null()){
            Serializer::read(json_context["transform"], instance.m_transform);
        }
        if(!json_context["material"].is_null()){
            Serializer::read(json_context["material"], instance.m_material);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const MeshComponentRes& instance){
        Json::object  ret_context;
        
        Json::array m_sub_meshes_json;
        for (auto& item : instance.m_sub_meshes){
            m_sub_meshes_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("sub_meshes",m_sub_meshes_json);
        
        return  Json(ret_context);
    }
    template<>
    MeshComponentRes& Serializer::read(const Json& json_context, MeshComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["sub_meshes"].is_null()){
            assert(json_context["sub_meshes"].is_array());
            Json::array array_m_sub_meshes = json_context["sub_meshes"].array_items();
            instance.m_sub_meshes.resize(array_m_sub_meshes.size());
            for (size_t index=0; index < array_m_sub_meshes.size();++index){
                Serializer::read(array_m_sub_meshes[index], instance.m_sub_meshes[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationResultElement& instance){
        Json::object  ret_context;
        
        
        return  Json(ret_context);
    }
    template<>
    AnimationResultElement& Serializer::read(const Json& json_context, AnimationResultElement& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationResult& instance){
        Json::object  ret_context;
        
        Json::array node_json;
        for (auto& item : instance.node){
            node_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("node",node_json);
        
        return  Json(ret_context);
    }
    template<>
    AnimationResult& Serializer::read(const Json& json_context, AnimationResult& instance){
        assert(json_context.is_object());
        
        if(!json_context["node"].is_null()){
            assert(json_context["node"].is_array());
            Json::array array_node = json_context["node"].array_items();
            instance.node.resize(array_node.size());
            for (size_t index=0; index < array_node.size();++index){
                Serializer::read(array_node[index], instance.node[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationComponentRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("skeleton_file_path", Serializer::write(instance.skeleton_file_path));
        ret_context.insert_or_assign("blend_state", Serializer::write(instance.blend_state));
        ret_context.insert_or_assign("frame_position", Serializer::write(instance.frame_position));
        return  Json(ret_context);
    }
    template<>
    AnimationComponentRes& Serializer::read(const Json& json_context, AnimationComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["skeleton_file_path"].is_null()){
            Serializer::read(json_context["skeleton_file_path"], instance.skeleton_file_path);
        }
        if(!json_context["blend_state"].is_null()){
            Serializer::read(json_context["blend_state"], instance.blend_state);
        }
        if(!json_context["frame_position"].is_null()){
            Serializer::read(json_context["frame_position"], instance.frame_position);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const GameObjectMeshDesc& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("mesh_file", Serializer::write(instance.m_mesh_file));
        return  Json(ret_context);
    }
    template<>
    GameObjectMeshDesc& Serializer::read(const Json& json_context, GameObjectMeshDesc& instance){
        assert(json_context.is_object());
        
        if(!json_context["mesh_file"].is_null()){
            Serializer::read(json_context["mesh_file"], instance.m_mesh_file);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const GameObjectMaterialDesc& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("base_color_texture_file", Serializer::write(instance.m_base_color_texture_file));
        ret_context.insert_or_assign("metallic_roughness_texture_file", Serializer::write(instance.m_metallic_roughness_texture_file));
        ret_context.insert_or_assign("normal_texture_file", Serializer::write(instance.m_normal_texture_file));
        ret_context.insert_or_assign("occlusion_texture_file", Serializer::write(instance.m_occlusion_texture_file));
        ret_context.insert_or_assign("emissive_texture_file", Serializer::write(instance.m_emissive_texture_file));
        ret_context.insert_or_assign("with_texture", Serializer::write(instance.m_with_texture));
        return  Json(ret_context);
    }
    template<>
    GameObjectMaterialDesc& Serializer::read(const Json& json_context, GameObjectMaterialDesc& instance){
        assert(json_context.is_object());
        
        if(!json_context["base_color_texture_file"].is_null()){
            Serializer::read(json_context["base_color_texture_file"], instance.m_base_color_texture_file);
        }
        if(!json_context["metallic_roughness_texture_file"].is_null()){
            Serializer::read(json_context["metallic_roughness_texture_file"], instance.m_metallic_roughness_texture_file);
        }
        if(!json_context["normal_texture_file"].is_null()){
            Serializer::read(json_context["normal_texture_file"], instance.m_normal_texture_file);
        }
        if(!json_context["occlusion_texture_file"].is_null()){
            Serializer::read(json_context["occlusion_texture_file"], instance.m_occlusion_texture_file);
        }
        if(!json_context["emissive_texture_file"].is_null()){
            Serializer::read(json_context["emissive_texture_file"], instance.m_emissive_texture_file);
        }
        if(!json_context["with_texture"].is_null()){
            Serializer::read(json_context["with_texture"], instance.m_with_texture);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const GameObjectTransformDesc& instance){
        Json::object  ret_context;
        
        
        return  Json(ret_context);
    }
    template<>
    GameObjectTransformDesc& Serializer::read(const Json& json_context, GameObjectTransformDesc& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    Json Serializer::write(const GameObjectPartDesc& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("mesh_desc", Serializer::write(instance.m_mesh_desc));
        ret_context.insert_or_assign("material_desc", Serializer::write(instance.m_material_desc));
        ret_context.insert_or_assign("transform_desc", Serializer::write(instance.m_transform_desc));
        ret_context.insert_or_assign("with_animation", Serializer::write(instance.m_with_animation));
        return  Json(ret_context);
    }
    template<>
    GameObjectPartDesc& Serializer::read(const Json& json_context, GameObjectPartDesc& instance){
        assert(json_context.is_object());
        
        if(!json_context["mesh_desc"].is_null()){
            Serializer::read(json_context["mesh_desc"], instance.m_mesh_desc);
        }
        if(!json_context["material_desc"].is_null()){
            Serializer::read(json_context["material_desc"], instance.m_material_desc);
        }
        if(!json_context["transform_desc"].is_null()){
            Serializer::read(json_context["transform_desc"], instance.m_transform_desc);
        }
        if(!json_context["with_animation"].is_null()){
            Serializer::read(json_context["with_animation"], instance.m_with_animation);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const MeshComponent& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Component*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("mesh_res", Serializer::write(instance.m_mesh_res));
        return  Json(ret_context);
    }
    template<>
    MeshComponent& Serializer::read(const Json& json_context, MeshComponent& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Component*)&instance);
        if(!json_context["mesh_res"].is_null()){
            Serializer::read(json_context["mesh_res"], instance.m_mesh_res);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const ComponentDefinitionRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("type_name", Serializer::write(instance.m_type_name));
        ret_context.insert_or_assign("component", Serializer::write(instance.m_component));
        return  Json(ret_context);
    }
    template<>
    ComponentDefinitionRes& Serializer::read(const Json& json_context, ComponentDefinitionRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["type_name"].is_null()){
            Serializer::read(json_context["type_name"], instance.m_type_name);
        }
        if(!json_context["component"].is_null()){
            Serializer::read(json_context["component"], instance.m_component);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const ObjectDefinitionRes& instance){
        Json::object  ret_context;
        
        Json::array m_components_json;
        for (auto& item : instance.m_components){
            m_components_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("components",m_components_json);
        
        return  Json(ret_context);
    }
    template<>
    ObjectDefinitionRes& Serializer::read(const Json& json_context, ObjectDefinitionRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["components"].is_null()){
            assert(json_context["components"].is_array());
            Json::array array_m_components = json_context["components"].array_items();
            instance.m_components.resize(array_m_components.size());
            for (size_t index=0; index < array_m_components.size();++index){
                Serializer::read(array_m_components[index], instance.m_components[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const ObjectInstanceRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("name", Serializer::write(instance.m_name));
        ret_context.insert_or_assign("definition", Serializer::write(instance.m_definition));
        Json::array m_instanced_components_json;
        for (auto& item : instance.m_instanced_components){
            m_instanced_components_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("instanced_components",m_instanced_components_json);
        
        return  Json(ret_context);
    }
    template<>
    ObjectInstanceRes& Serializer::read(const Json& json_context, ObjectInstanceRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["name"].is_null()){
            Serializer::read(json_context["name"], instance.m_name);
        }
        if(!json_context["definition"].is_null()){
            Serializer::read(json_context["definition"], instance.m_definition);
        }
        if(!json_context["instanced_components"].is_null()){
            assert(json_context["instanced_components"].is_array());
            Json::array array_m_instanced_components = json_context["instanced_components"].array_items();
            instance.m_instanced_components.resize(array_m_instanced_components.size());
            for (size_t index=0; index < array_m_instanced_components.size();++index){
                Serializer::read(array_m_instanced_components[index], instance.m_instanced_components[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const TransformComponent& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Component*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("transform", Serializer::write(instance.m_transform));
        return  Json(ret_context);
    }
    template<>
    TransformComponent& Serializer::read(const Json& json_context, TransformComponent& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Component*)&instance);
        if(!json_context["transform"].is_null()){
            Serializer::read(json_context["transform"], instance.m_transform);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const WorldRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("name", Serializer::write(instance.m_name));
        Json::array m_level_urls_json;
        for (auto& item : instance.m_level_urls){
            m_level_urls_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("level_urls",m_level_urls_json);
        
        ret_context.insert_or_assign("default_level_url", Serializer::write(instance.m_default_level_url));
        return  Json(ret_context);
    }
    template<>
    WorldRes& Serializer::read(const Json& json_context, WorldRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["name"].is_null()){
            Serializer::read(json_context["name"], instance.m_name);
        }
        if(!json_context["level_urls"].is_null()){
            assert(json_context["level_urls"].is_array());
            Json::array array_m_level_urls = json_context["level_urls"].array_items();
            instance.m_level_urls.resize(array_m_level_urls.size());
            for (size_t index=0; index < array_m_level_urls.size();++index){
                Serializer::read(array_m_level_urls[index], instance.m_level_urls[index]);
            }
        }
        if(!json_context["default_level_url"].is_null()){
            Serializer::read(json_context["default_level_url"], instance.m_default_level_url);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const CameraPose& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("position", Serializer::write(instance.m_position));
        ret_context.insert_or_assign("target", Serializer::write(instance.m_target));
        ret_context.insert_or_assign("up", Serializer::write(instance.m_up));
        return  Json(ret_context);
    }
    template<>
    CameraPose& Serializer::read(const Json& json_context, CameraPose& instance){
        assert(json_context.is_object());
        
        if(!json_context["position"].is_null()){
            Serializer::read(json_context["position"], instance.m_position);
        }
        if(!json_context["target"].is_null()){
            Serializer::read(json_context["target"], instance.m_target);
        }
        if(!json_context["up"].is_null()){
            Serializer::read(json_context["up"], instance.m_up);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const CameraConfig& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("pose", Serializer::write(instance.m_pose));
        ret_context.insert_or_assign("aspect", Serializer::write(instance.m_aspect));
        ret_context.insert_or_assign("z_far", Serializer::write(instance.m_z_far));
        ret_context.insert_or_assign("z_near", Serializer::write(instance.m_z_near));
        return  Json(ret_context);
    }
    template<>
    CameraConfig& Serializer::read(const Json& json_context, CameraConfig& instance){
        assert(json_context.is_object());
        
        if(!json_context["pose"].is_null()){
            Serializer::read(json_context["pose"], instance.m_pose);
        }
        if(!json_context["aspect"].is_null()){
            Serializer::read(json_context["aspect"], instance.m_aspect);
        }
        if(!json_context["z_far"].is_null()){
            Serializer::read(json_context["z_far"], instance.m_z_far);
        }
        if(!json_context["z_near"].is_null()){
            Serializer::read(json_context["z_near"], instance.m_z_near);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const ParticleComponentRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("local_translation", Serializer::write(instance.m_local_translation));
        ret_context.insert_or_assign("local_rotation", Serializer::write(instance.m_local_rotation));
        ret_context.insert_or_assign("velocity", Serializer::write(instance.m_velocity));
        ret_context.insert_or_assign("acceleration", Serializer::write(instance.m_acceleration));
        ret_context.insert_or_assign("size", Serializer::write(instance.m_size));
        ret_context.insert_or_assign("emitter_type", Serializer::write(instance.m_emitter_type));
        ret_context.insert_or_assign("life", Serializer::write(instance.m_life));
        ret_context.insert_or_assign("color", Serializer::write(instance.m_color));
        return  Json(ret_context);
    }
    template<>
    ParticleComponentRes& Serializer::read(const Json& json_context, ParticleComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["local_translation"].is_null()){
            Serializer::read(json_context["local_translation"], instance.m_local_translation);
        }
        if(!json_context["local_rotation"].is_null()){
            Serializer::read(json_context["local_rotation"], instance.m_local_rotation);
        }
        if(!json_context["velocity"].is_null()){
            Serializer::read(json_context["velocity"], instance.m_velocity);
        }
        if(!json_context["acceleration"].is_null()){
            Serializer::read(json_context["acceleration"], instance.m_acceleration);
        }
        if(!json_context["size"].is_null()){
            Serializer::read(json_context["size"], instance.m_size);
        }
        if(!json_context["emitter_type"].is_null()){
            Serializer::read(json_context["emitter_type"], instance.m_emitter_type);
        }
        if(!json_context["life"].is_null()){
            Serializer::read(json_context["life"], instance.m_life);
        }
        if(!json_context["color"].is_null()){
            Serializer::read(json_context["color"], instance.m_color);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const SkyBoxIrradianceMap& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("negative_x_map", Serializer::write(instance.m_negative_x_map));
        ret_context.insert_or_assign("positive_x_map", Serializer::write(instance.m_positive_x_map));
        ret_context.insert_or_assign("negative_y_map", Serializer::write(instance.m_negative_y_map));
        ret_context.insert_or_assign("positive_y_map", Serializer::write(instance.m_positive_y_map));
        ret_context.insert_or_assign("negative_z_map", Serializer::write(instance.m_negative_z_map));
        ret_context.insert_or_assign("positive_z_map", Serializer::write(instance.m_positive_z_map));
        return  Json(ret_context);
    }
    template<>
    SkyBoxIrradianceMap& Serializer::read(const Json& json_context, SkyBoxIrradianceMap& instance){
        assert(json_context.is_object());
        
        if(!json_context["negative_x_map"].is_null()){
            Serializer::read(json_context["negative_x_map"], instance.m_negative_x_map);
        }
        if(!json_context["positive_x_map"].is_null()){
            Serializer::read(json_context["positive_x_map"], instance.m_positive_x_map);
        }
        if(!json_context["negative_y_map"].is_null()){
            Serializer::read(json_context["negative_y_map"], instance.m_negative_y_map);
        }
        if(!json_context["positive_y_map"].is_null()){
            Serializer::read(json_context["positive_y_map"], instance.m_positive_y_map);
        }
        if(!json_context["negative_z_map"].is_null()){
            Serializer::read(json_context["negative_z_map"], instance.m_negative_z_map);
        }
        if(!json_context["positive_z_map"].is_null()){
            Serializer::read(json_context["positive_z_map"], instance.m_positive_z_map);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const SkyBoxSpecularMap& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("negative_x_map", Serializer::write(instance.m_negative_x_map));
        ret_context.insert_or_assign("positive_x_map", Serializer::write(instance.m_positive_x_map));
        ret_context.insert_or_assign("negative_y_map", Serializer::write(instance.m_negative_y_map));
        ret_context.insert_or_assign("positive_y_map", Serializer::write(instance.m_positive_y_map));
        ret_context.insert_or_assign("negative_z_map", Serializer::write(instance.m_negative_z_map));
        ret_context.insert_or_assign("positive_z_map", Serializer::write(instance.m_positive_z_map));
        return  Json(ret_context);
    }
    template<>
    SkyBoxSpecularMap& Serializer::read(const Json& json_context, SkyBoxSpecularMap& instance){
        assert(json_context.is_object());
        
        if(!json_context["negative_x_map"].is_null()){
            Serializer::read(json_context["negative_x_map"], instance.m_negative_x_map);
        }
        if(!json_context["positive_x_map"].is_null()){
            Serializer::read(json_context["positive_x_map"], instance.m_positive_x_map);
        }
        if(!json_context["negative_y_map"].is_null()){
            Serializer::read(json_context["negative_y_map"], instance.m_negative_y_map);
        }
        if(!json_context["positive_y_map"].is_null()){
            Serializer::read(json_context["positive_y_map"], instance.m_positive_y_map);
        }
        if(!json_context["negative_z_map"].is_null()){
            Serializer::read(json_context["negative_z_map"], instance.m_negative_z_map);
        }
        if(!json_context["positive_z_map"].is_null()){
            Serializer::read(json_context["positive_z_map"], instance.m_positive_z_map);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const DirectionalLight& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("direction", Serializer::write(instance.m_direction));
        ret_context.insert_or_assign("color", Serializer::write(instance.m_color));
        return  Json(ret_context);
    }
    template<>
    DirectionalLight& Serializer::read(const Json& json_context, DirectionalLight& instance){
        assert(json_context.is_object());
        
        if(!json_context["direction"].is_null()){
            Serializer::read(json_context["direction"], instance.m_direction);
        }
        if(!json_context["color"].is_null()){
            Serializer::read(json_context["color"], instance.m_color);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const GlobalRenderingRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("enable_fxaa", Serializer::write(instance.m_enable_fxaa));
        ret_context.insert_or_assign("skybox_irradiance_map", Serializer::write(instance.m_skybox_irradiance_map));
        ret_context.insert_or_assign("skybox_specular_map", Serializer::write(instance.m_skybox_specular_map));
        ret_context.insert_or_assign("brdf_map", Serializer::write(instance.m_brdf_map));
        ret_context.insert_or_assign("color_grading_map", Serializer::write(instance.m_color_grading_map));
        ret_context.insert_or_assign("sky_color", Serializer::write(instance.m_sky_color));
        ret_context.insert_or_assign("ambient_light", Serializer::write(instance.m_ambient_light));
        ret_context.insert_or_assign("camera_config", Serializer::write(instance.m_camera_config));
        ret_context.insert_or_assign("directional_light", Serializer::write(instance.m_directional_light));
        return  Json(ret_context);
    }
    template<>
    GlobalRenderingRes& Serializer::read(const Json& json_context, GlobalRenderingRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["enable_fxaa"].is_null()){
            Serializer::read(json_context["enable_fxaa"], instance.m_enable_fxaa);
        }
        if(!json_context["skybox_irradiance_map"].is_null()){
            Serializer::read(json_context["skybox_irradiance_map"], instance.m_skybox_irradiance_map);
        }
        if(!json_context["skybox_specular_map"].is_null()){
            Serializer::read(json_context["skybox_specular_map"], instance.m_skybox_specular_map);
        }
        if(!json_context["brdf_map"].is_null()){
            Serializer::read(json_context["brdf_map"], instance.m_brdf_map);
        }
        if(!json_context["color_grading_map"].is_null()){
            Serializer::read(json_context["color_grading_map"], instance.m_color_grading_map);
        }
        if(!json_context["sky_color"].is_null()){
            Serializer::read(json_context["sky_color"], instance.m_sky_color);
        }
        if(!json_context["ambient_light"].is_null()){
            Serializer::read(json_context["ambient_light"], instance.m_ambient_light);
        }
        if(!json_context["camera_config"].is_null()){
            Serializer::read(json_context["camera_config"], instance.m_camera_config);
        }
        if(!json_context["directional_light"].is_null()){
            Serializer::read(json_context["directional_light"], instance.m_directional_light);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Geometry& instance){
        Json::object  ret_context;
        
        
        return  Json(ret_context);
    }
    template<>
    Geometry& Serializer::read(const Json& json_context, Geometry& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    Json Serializer::write(const Box& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Geometry*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("half_extents", Serializer::write(instance.m_half_extents));
        return  Json(ret_context);
    }
    template<>
    Box& Serializer::read(const Json& json_context, Box& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Geometry*)&instance);
        if(!json_context["half_extents"].is_null()){
            Serializer::read(json_context["half_extents"], instance.m_half_extents);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Sphere& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Geometry*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("radius", Serializer::write(instance.m_radius));
        return  Json(ret_context);
    }
    template<>
    Sphere& Serializer::read(const Json& json_context, Sphere& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Geometry*)&instance);
        if(!json_context["radius"].is_null()){
            Serializer::read(json_context["radius"], instance.m_radius);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Capsule& instance){
        Json::object  ret_context;
        auto&&  json_context_0 = Serializer::write(*(SimpleEngine::Geometry*)&instance);
        assert(json_context_0.is_object());
        auto&& json_context_map_0 = json_context_0.object_items();
        ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
        ret_context.insert_or_assign("radius", Serializer::write(instance.m_radius));
        ret_context.insert_or_assign("half_height", Serializer::write(instance.m_half_height));
        return  Json(ret_context);
    }
    template<>
    Capsule& Serializer::read(const Json& json_context, Capsule& instance){
        assert(json_context.is_object());
        Serializer::read(json_context,*(SimpleEngine::Geometry*)&instance);
        if(!json_context["radius"].is_null()){
            Serializer::read(json_context["radius"], instance.m_radius);
        }
        if(!json_context["half_height"].is_null()){
            Serializer::read(json_context["half_height"], instance.m_half_height);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimNodeMap& instance){
        Json::object  ret_context;
        
        Json::array convert_json;
        for (auto& item : instance.convert){
            convert_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("convert",convert_json);
        
        return  Json(ret_context);
    }
    template<>
    AnimNodeMap& Serializer::read(const Json& json_context, AnimNodeMap& instance){
        assert(json_context.is_object());
        
        if(!json_context["convert"].is_null()){
            assert(json_context["convert"].is_array());
            Json::array array_convert = json_context["convert"].array_items();
            instance.convert.resize(array_convert.size());
            for (size_t index=0; index < array_convert.size();++index){
                Serializer::read(array_convert[index], instance.convert[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationChannel& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("name", Serializer::write(instance.name));
        Json::array position_keys_json;
        for (auto& item : instance.position_keys){
            position_keys_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("position_keys",position_keys_json);
        
        Json::array rotation_keys_json;
        for (auto& item : instance.rotation_keys){
            rotation_keys_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("rotation_keys",rotation_keys_json);
        
        Json::array scaling_keys_json;
        for (auto& item : instance.scaling_keys){
            scaling_keys_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("scaling_keys",scaling_keys_json);
        
        return  Json(ret_context);
    }
    template<>
    AnimationChannel& Serializer::read(const Json& json_context, AnimationChannel& instance){
        assert(json_context.is_object());
        
        if(!json_context["name"].is_null()){
            Serializer::read(json_context["name"], instance.name);
        }
        if(!json_context["position_keys"].is_null()){
            assert(json_context["position_keys"].is_array());
            Json::array array_position_keys = json_context["position_keys"].array_items();
            instance.position_keys.resize(array_position_keys.size());
            for (size_t index=0; index < array_position_keys.size();++index){
                Serializer::read(array_position_keys[index], instance.position_keys[index]);
            }
        }
        if(!json_context["rotation_keys"].is_null()){
            assert(json_context["rotation_keys"].is_array());
            Json::array array_rotation_keys = json_context["rotation_keys"].array_items();
            instance.rotation_keys.resize(array_rotation_keys.size());
            for (size_t index=0; index < array_rotation_keys.size();++index){
                Serializer::read(array_rotation_keys[index], instance.rotation_keys[index]);
            }
        }
        if(!json_context["scaling_keys"].is_null()){
            assert(json_context["scaling_keys"].is_array());
            Json::array array_scaling_keys = json_context["scaling_keys"].array_items();
            instance.scaling_keys.resize(array_scaling_keys.size());
            for (size_t index=0; index < array_scaling_keys.size();++index){
                Serializer::read(array_scaling_keys[index], instance.scaling_keys[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationClip& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("total_frame", Serializer::write(instance.total_frame));
        ret_context.insert_or_assign("node_count", Serializer::write(instance.node_count));
        Json::array node_channels_json;
        for (auto& item : instance.node_channels){
            node_channels_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("node_channels",node_channels_json);
        
        return  Json(ret_context);
    }
    template<>
    AnimationClip& Serializer::read(const Json& json_context, AnimationClip& instance){
        assert(json_context.is_object());
        
        if(!json_context["total_frame"].is_null()){
            Serializer::read(json_context["total_frame"], instance.total_frame);
        }
        if(!json_context["node_count"].is_null()){
            Serializer::read(json_context["node_count"], instance.node_count);
        }
        if(!json_context["node_channels"].is_null()){
            assert(json_context["node_channels"].is_array());
            Json::array array_node_channels = json_context["node_channels"].array_items();
            instance.node_channels.resize(array_node_channels.size());
            for (size_t index=0; index < array_node_channels.size();++index){
                Serializer::read(array_node_channels[index], instance.node_channels[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const AnimationAsset& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("node_map", Serializer::write(instance.node_map));
        ret_context.insert_or_assign("clip_data", Serializer::write(instance.clip_data));
        ret_context.insert_or_assign("skeleton_file_path", Serializer::write(instance.skeleton_file_path));
        return  Json(ret_context);
    }
    template<>
    AnimationAsset& Serializer::read(const Json& json_context, AnimationAsset& instance){
        assert(json_context.is_object());
        
        if(!json_context["node_map"].is_null()){
            Serializer::read(json_context["node_map"], instance.node_map);
        }
        if(!json_context["clip_data"].is_null()){
            Serializer::read(json_context["clip_data"], instance.clip_data);
        }
        if(!json_context["skeleton_file_path"].is_null()){
            Serializer::read(json_context["skeleton_file_path"], instance.skeleton_file_path);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const BoneBlendWeight& instance){
        Json::object  ret_context;
        
        Json::array blend_weight_json;
        for (auto& item : instance.blend_weight){
            blend_weight_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_weight",blend_weight_json);
        
        return  Json(ret_context);
    }
    template<>
    BoneBlendWeight& Serializer::read(const Json& json_context, BoneBlendWeight& instance){
        assert(json_context.is_object());
        
        if(!json_context["blend_weight"].is_null()){
            assert(json_context["blend_weight"].is_array());
            Json::array array_blend_weight = json_context["blend_weight"].array_items();
            instance.blend_weight.resize(array_blend_weight.size());
            for (size_t index=0; index < array_blend_weight.size();++index){
                Serializer::read(array_blend_weight[index], instance.blend_weight[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const BlendStateWithClipData& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("clip_count", Serializer::write(instance.clip_count));
        Json::array blend_clip_json;
        for (auto& item : instance.blend_clip){
            blend_clip_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_clip",blend_clip_json);
        
        Json::array blend_anim_skel_map_json;
        for (auto& item : instance.blend_anim_skel_map){
            blend_anim_skel_map_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_anim_skel_map",blend_anim_skel_map_json);
        
        Json::array blend_weight_json;
        for (auto& item : instance.blend_weight){
            blend_weight_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_weight",blend_weight_json);
        
        Json::array blend_ratio_json;
        for (auto& item : instance.blend_ratio){
            blend_ratio_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_ratio",blend_ratio_json);
        
        return  Json(ret_context);
    }
    template<>
    BlendStateWithClipData& Serializer::read(const Json& json_context, BlendStateWithClipData& instance){
        assert(json_context.is_object());
        
        if(!json_context["clip_count"].is_null()){
            Serializer::read(json_context["clip_count"], instance.clip_count);
        }
        if(!json_context["blend_clip"].is_null()){
            assert(json_context["blend_clip"].is_array());
            Json::array array_blend_clip = json_context["blend_clip"].array_items();
            instance.blend_clip.resize(array_blend_clip.size());
            for (size_t index=0; index < array_blend_clip.size();++index){
                Serializer::read(array_blend_clip[index], instance.blend_clip[index]);
            }
        }
        if(!json_context["blend_anim_skel_map"].is_null()){
            assert(json_context["blend_anim_skel_map"].is_array());
            Json::array array_blend_anim_skel_map = json_context["blend_anim_skel_map"].array_items();
            instance.blend_anim_skel_map.resize(array_blend_anim_skel_map.size());
            for (size_t index=0; index < array_blend_anim_skel_map.size();++index){
                Serializer::read(array_blend_anim_skel_map[index], instance.blend_anim_skel_map[index]);
            }
        }
        if(!json_context["blend_weight"].is_null()){
            assert(json_context["blend_weight"].is_array());
            Json::array array_blend_weight = json_context["blend_weight"].array_items();
            instance.blend_weight.resize(array_blend_weight.size());
            for (size_t index=0; index < array_blend_weight.size();++index){
                Serializer::read(array_blend_weight[index], instance.blend_weight[index]);
            }
        }
        if(!json_context["blend_ratio"].is_null()){
            assert(json_context["blend_ratio"].is_array());
            Json::array array_blend_ratio = json_context["blend_ratio"].array_items();
            instance.blend_ratio.resize(array_blend_ratio.size());
            for (size_t index=0; index < array_blend_ratio.size();++index){
                Serializer::read(array_blend_ratio[index], instance.blend_ratio[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const BlendState& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("clip_count", Serializer::write(instance.clip_count));
        Json::array blend_clip_file_path_json;
        for (auto& item : instance.blend_clip_file_path){
            blend_clip_file_path_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_clip_file_path",blend_clip_file_path_json);
        
        Json::array blend_clip_file_length_json;
        for (auto& item : instance.blend_clip_file_length){
            blend_clip_file_length_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_clip_file_length",blend_clip_file_length_json);
        
        Json::array blend_anim_skel_map_path_json;
        for (auto& item : instance.blend_anim_skel_map_path){
            blend_anim_skel_map_path_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_anim_skel_map_path",blend_anim_skel_map_path_json);
        
        Json::array blend_weight_json;
        for (auto& item : instance.blend_weight){
            blend_weight_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_weight",blend_weight_json);
        
        Json::array blend_mask_file_path_json;
        for (auto& item : instance.blend_mask_file_path){
            blend_mask_file_path_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_mask_file_path",blend_mask_file_path_json);
        
        Json::array blend_ratio_json;
        for (auto& item : instance.blend_ratio){
            blend_ratio_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("blend_ratio",blend_ratio_json);
        
        return  Json(ret_context);
    }
    template<>
    BlendState& Serializer::read(const Json& json_context, BlendState& instance){
        assert(json_context.is_object());
        
        if(!json_context["clip_count"].is_null()){
            Serializer::read(json_context["clip_count"], instance.clip_count);
        }
        if(!json_context["blend_clip_file_path"].is_null()){
            assert(json_context["blend_clip_file_path"].is_array());
            Json::array array_blend_clip_file_path = json_context["blend_clip_file_path"].array_items();
            instance.blend_clip_file_path.resize(array_blend_clip_file_path.size());
            for (size_t index=0; index < array_blend_clip_file_path.size();++index){
                Serializer::read(array_blend_clip_file_path[index], instance.blend_clip_file_path[index]);
            }
        }
        if(!json_context["blend_clip_file_length"].is_null()){
            assert(json_context["blend_clip_file_length"].is_array());
            Json::array array_blend_clip_file_length = json_context["blend_clip_file_length"].array_items();
            instance.blend_clip_file_length.resize(array_blend_clip_file_length.size());
            for (size_t index=0; index < array_blend_clip_file_length.size();++index){
                Serializer::read(array_blend_clip_file_length[index], instance.blend_clip_file_length[index]);
            }
        }
        if(!json_context["blend_anim_skel_map_path"].is_null()){
            assert(json_context["blend_anim_skel_map_path"].is_array());
            Json::array array_blend_anim_skel_map_path = json_context["blend_anim_skel_map_path"].array_items();
            instance.blend_anim_skel_map_path.resize(array_blend_anim_skel_map_path.size());
            for (size_t index=0; index < array_blend_anim_skel_map_path.size();++index){
                Serializer::read(array_blend_anim_skel_map_path[index], instance.blend_anim_skel_map_path[index]);
            }
        }
        if(!json_context["blend_weight"].is_null()){
            assert(json_context["blend_weight"].is_array());
            Json::array array_blend_weight = json_context["blend_weight"].array_items();
            instance.blend_weight.resize(array_blend_weight.size());
            for (size_t index=0; index < array_blend_weight.size();++index){
                Serializer::read(array_blend_weight[index], instance.blend_weight[index]);
            }
        }
        if(!json_context["blend_mask_file_path"].is_null()){
            assert(json_context["blend_mask_file_path"].is_array());
            Json::array array_blend_mask_file_path = json_context["blend_mask_file_path"].array_items();
            instance.blend_mask_file_path.resize(array_blend_mask_file_path.size());
            for (size_t index=0; index < array_blend_mask_file_path.size();++index){
                Serializer::read(array_blend_mask_file_path[index], instance.blend_mask_file_path[index]);
            }
        }
        if(!json_context["blend_ratio"].is_null()){
            assert(json_context["blend_ratio"].is_array());
            Json::array array_blend_ratio = json_context["blend_ratio"].array_items();
            instance.blend_ratio.resize(array_blend_ratio.size());
            for (size_t index=0; index < array_blend_ratio.size();++index){
                Serializer::read(array_blend_ratio[index], instance.blend_ratio[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const RawBone& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("name", Serializer::write(instance.name));
        ret_context.insert_or_assign("index", Serializer::write(instance.index));
        ret_context.insert_or_assign("binding_pose", Serializer::write(instance.binding_pose));
        ret_context.insert_or_assign("tpose_matrix", Serializer::write(instance.tpose_matrix));
        ret_context.insert_or_assign("parent_index", Serializer::write(instance.parent_index));
        return  Json(ret_context);
    }
    template<>
    RawBone& Serializer::read(const Json& json_context, RawBone& instance){
        assert(json_context.is_object());
        
        if(!json_context["name"].is_null()){
            Serializer::read(json_context["name"], instance.name);
        }
        if(!json_context["index"].is_null()){
            Serializer::read(json_context["index"], instance.index);
        }
        if(!json_context["binding_pose"].is_null()){
            Serializer::read(json_context["binding_pose"], instance.binding_pose);
        }
        if(!json_context["tpose_matrix"].is_null()){
            Serializer::read(json_context["tpose_matrix"], instance.tpose_matrix);
        }
        if(!json_context["parent_index"].is_null()){
            Serializer::read(json_context["parent_index"], instance.parent_index);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const SkeletonData& instance){
        Json::object  ret_context;
        
        Json::array bones_map_json;
        for (auto& item : instance.bones_map){
            bones_map_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("bones_map",bones_map_json);
        
        ret_context.insert_or_assign("is_flat", Serializer::write(instance.is_flat));
        ret_context.insert_or_assign("root_index", Serializer::write(instance.root_index));
        ret_context.insert_or_assign("in_topological_order", Serializer::write(instance.in_topological_order));
        return  Json(ret_context);
    }
    template<>
    SkeletonData& Serializer::read(const Json& json_context, SkeletonData& instance){
        assert(json_context.is_object());
        
        if(!json_context["bones_map"].is_null()){
            assert(json_context["bones_map"].is_array());
            Json::array array_bones_map = json_context["bones_map"].array_items();
            instance.bones_map.resize(array_bones_map.size());
            for (size_t index=0; index < array_bones_map.size();++index){
                Serializer::read(array_bones_map[index], instance.bones_map[index]);
            }
        }
        if(!json_context["is_flat"].is_null()){
            Serializer::read(json_context["is_flat"], instance.is_flat);
        }
        if(!json_context["root_index"].is_null()){
            Serializer::read(json_context["root_index"], instance.root_index);
        }
        if(!json_context["in_topological_order"].is_null()){
            Serializer::read(json_context["in_topological_order"], instance.in_topological_order);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const BoneBlendMask& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("skeleton_file_path", Serializer::write(instance.skeleton_file_path));
        Json::array enabled_json;
        for (auto& item : instance.enabled){
            enabled_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("enabled",enabled_json);
        
        return  Json(ret_context);
    }
    template<>
    BoneBlendMask& Serializer::read(const Json& json_context, BoneBlendMask& instance){
        assert(json_context.is_object());
        
        if(!json_context["skeleton_file_path"].is_null()){
            Serializer::read(json_context["skeleton_file_path"], instance.skeleton_file_path);
        }
        if(!json_context["enabled"].is_null()){
            assert(json_context["enabled"].is_array());
            Json::array array_enabled = json_context["enabled"].array_items();
            instance.enabled.resize(array_enabled.size());
            for (size_t index=0; index < array_enabled.size();++index){
                Serializer::read(array_enabled[index], instance.enabled[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const LevelRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("gravity", Serializer::write(instance.m_gravity));
        ret_context.insert_or_assign("camera_name", Serializer::write(instance.m_camera_name));
        Json::array m_objects_json;
        for (auto& item : instance.m_objects){
            m_objects_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("objects",m_objects_json);
        
        return  Json(ret_context);
    }
    template<>
    LevelRes& Serializer::read(const Json& json_context, LevelRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["gravity"].is_null()){
            Serializer::read(json_context["gravity"], instance.m_gravity);
        }
        if(!json_context["camera_name"].is_null()){
            Serializer::read(json_context["camera_name"], instance.m_camera_name);
        }
        if(!json_context["objects"].is_null()){
            assert(json_context["objects"].is_array());
            Json::array array_m_objects = json_context["objects"].array_items();
            instance.m_objects.resize(array_m_objects.size());
            for (size_t index=0; index < array_m_objects.size();++index){
                Serializer::read(array_m_objects[index], instance.m_objects[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const RigidBodyShape& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("local_transform", Serializer::write(instance.m_local_transform));
        ret_context.insert_or_assign("geometry", Serializer::write(instance.m_geometry));
        return  Json(ret_context);
    }
    template<>
    RigidBodyShape& Serializer::read(const Json& json_context, RigidBodyShape& instance){
        assert(json_context.is_object());
        
        if(!json_context["local_transform"].is_null()){
            Serializer::read(json_context["local_transform"], instance.m_local_transform);
        }
        if(!json_context["geometry"].is_null()){
            Serializer::read(json_context["geometry"], instance.m_geometry);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const RigidBodyComponentRes& instance){
        Json::object  ret_context;
        
        Json::array m_shapes_json;
        for (auto& item : instance.m_shapes){
            m_shapes_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("shapes",m_shapes_json);
        
        ret_context.insert_or_assign("inverse_mass", Serializer::write(instance.m_inverse_mass));
        ret_context.insert_or_assign("actor_type", Serializer::write(instance.m_actor_type));
        return  Json(ret_context);
    }
    template<>
    RigidBodyComponentRes& Serializer::read(const Json& json_context, RigidBodyComponentRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["shapes"].is_null()){
            assert(json_context["shapes"].is_array());
            Json::array array_m_shapes = json_context["shapes"].array_items();
            instance.m_shapes.resize(array_m_shapes.size());
            for (size_t index=0; index < array_m_shapes.size();++index){
                Serializer::read(array_m_shapes[index], instance.m_shapes[index]);
            }
        }
        if(!json_context["inverse_mass"].is_null()){
            Serializer::read(json_context["inverse_mass"], instance.m_inverse_mass);
        }
        if(!json_context["actor_type"].is_null()){
            Serializer::read(json_context["actor_type"], instance.m_actor_type);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const Vertex& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("px", Serializer::write(instance.px));
        ret_context.insert_or_assign("py", Serializer::write(instance.py));
        ret_context.insert_or_assign("pz", Serializer::write(instance.pz));
        ret_context.insert_or_assign("nx", Serializer::write(instance.nx));
        ret_context.insert_or_assign("ny", Serializer::write(instance.ny));
        ret_context.insert_or_assign("nz", Serializer::write(instance.nz));
        ret_context.insert_or_assign("tx", Serializer::write(instance.tx));
        ret_context.insert_or_assign("ty", Serializer::write(instance.ty));
        ret_context.insert_or_assign("tz", Serializer::write(instance.tz));
        ret_context.insert_or_assign("u", Serializer::write(instance.u));
        ret_context.insert_or_assign("v", Serializer::write(instance.v));
        return  Json(ret_context);
    }
    template<>
    Vertex& Serializer::read(const Json& json_context, Vertex& instance){
        assert(json_context.is_object());
        
        if(!json_context["px"].is_null()){
            Serializer::read(json_context["px"], instance.px);
        }
        if(!json_context["py"].is_null()){
            Serializer::read(json_context["py"], instance.py);
        }
        if(!json_context["pz"].is_null()){
            Serializer::read(json_context["pz"], instance.pz);
        }
        if(!json_context["nx"].is_null()){
            Serializer::read(json_context["nx"], instance.nx);
        }
        if(!json_context["ny"].is_null()){
            Serializer::read(json_context["ny"], instance.ny);
        }
        if(!json_context["nz"].is_null()){
            Serializer::read(json_context["nz"], instance.nz);
        }
        if(!json_context["tx"].is_null()){
            Serializer::read(json_context["tx"], instance.tx);
        }
        if(!json_context["ty"].is_null()){
            Serializer::read(json_context["ty"], instance.ty);
        }
        if(!json_context["tz"].is_null()){
            Serializer::read(json_context["tz"], instance.tz);
        }
        if(!json_context["u"].is_null()){
            Serializer::read(json_context["u"], instance.u);
        }
        if(!json_context["v"].is_null()){
            Serializer::read(json_context["v"], instance.v);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const SkeletonBinding& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("index0", Serializer::write(instance.index0));
        ret_context.insert_or_assign("index1", Serializer::write(instance.index1));
        ret_context.insert_or_assign("index2", Serializer::write(instance.index2));
        ret_context.insert_or_assign("index3", Serializer::write(instance.index3));
        ret_context.insert_or_assign("weight0", Serializer::write(instance.weight0));
        ret_context.insert_or_assign("weight1", Serializer::write(instance.weight1));
        ret_context.insert_or_assign("weight2", Serializer::write(instance.weight2));
        ret_context.insert_or_assign("weight3", Serializer::write(instance.weight3));
        return  Json(ret_context);
    }
    template<>
    SkeletonBinding& Serializer::read(const Json& json_context, SkeletonBinding& instance){
        assert(json_context.is_object());
        
        if(!json_context["index0"].is_null()){
            Serializer::read(json_context["index0"], instance.index0);
        }
        if(!json_context["index1"].is_null()){
            Serializer::read(json_context["index1"], instance.index1);
        }
        if(!json_context["index2"].is_null()){
            Serializer::read(json_context["index2"], instance.index2);
        }
        if(!json_context["index3"].is_null()){
            Serializer::read(json_context["index3"], instance.index3);
        }
        if(!json_context["weight0"].is_null()){
            Serializer::read(json_context["weight0"], instance.weight0);
        }
        if(!json_context["weight1"].is_null()){
            Serializer::read(json_context["weight1"], instance.weight1);
        }
        if(!json_context["weight2"].is_null()){
            Serializer::read(json_context["weight2"], instance.weight2);
        }
        if(!json_context["weight3"].is_null()){
            Serializer::read(json_context["weight3"], instance.weight3);
        }
        return instance;
    }
    template<>
    Json Serializer::write(const MeshData& instance){
        Json::object  ret_context;
        
        Json::array vertex_buffer_json;
        for (auto& item : instance.vertex_buffer){
            vertex_buffer_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("vertex_buffer",vertex_buffer_json);
        
        Json::array index_buffer_json;
        for (auto& item : instance.index_buffer){
            index_buffer_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("index_buffer",index_buffer_json);
        
        Json::array bind_json;
        for (auto& item : instance.bind){
            bind_json.emplace_back(Serializer::write(item));
        }
        ret_context.insert_or_assign("bind",bind_json);
        
        return  Json(ret_context);
    }
    template<>
    MeshData& Serializer::read(const Json& json_context, MeshData& instance){
        assert(json_context.is_object());
        
        if(!json_context["vertex_buffer"].is_null()){
            assert(json_context["vertex_buffer"].is_array());
            Json::array array_vertex_buffer = json_context["vertex_buffer"].array_items();
            instance.vertex_buffer.resize(array_vertex_buffer.size());
            for (size_t index=0; index < array_vertex_buffer.size();++index){
                Serializer::read(array_vertex_buffer[index], instance.vertex_buffer[index]);
            }
        }
        if(!json_context["index_buffer"].is_null()){
            assert(json_context["index_buffer"].is_array());
            Json::array array_index_buffer = json_context["index_buffer"].array_items();
            instance.index_buffer.resize(array_index_buffer.size());
            for (size_t index=0; index < array_index_buffer.size();++index){
                Serializer::read(array_index_buffer[index], instance.index_buffer[index]);
            }
        }
        if(!json_context["bind"].is_null()){
            assert(json_context["bind"].is_array());
            Json::array array_bind = json_context["bind"].array_items();
            instance.bind.resize(array_bind.size());
            for (size_t index=0; index < array_bind.size();++index){
                Serializer::read(array_bind[index], instance.bind[index]);
            }
        }
        return instance;
    }
    template<>
    Json Serializer::write(const GlobalParticleRes& instance){
        Json::object  ret_context;
        
        ret_context.insert_or_assign("emit_gap", Serializer::write(instance.m_emit_gap));
        ret_context.insert_or_assign("emit_count", Serializer::write(instance.m_emit_count));
        ret_context.insert_or_assign("time_step", Serializer::write(instance.m_time_step));
        ret_context.insert_or_assign("max_life", Serializer::write(instance.m_max_life));
        ret_context.insert_or_assign("gravity", Serializer::write(instance.m_gravity));
        ret_context.insert_or_assign("particle_billboard_texture_path", Serializer::write(instance.m_particle_billboard_texture_path));
        ret_context.insert_or_assign("piccolo_logo_texture_path", Serializer::write(instance.m_piccolo_logo_texture_path));
        return  Json(ret_context);
    }
    template<>
    GlobalParticleRes& Serializer::read(const Json& json_context, GlobalParticleRes& instance){
        assert(json_context.is_object());
        
        if(!json_context["emit_gap"].is_null()){
            Serializer::read(json_context["emit_gap"], instance.m_emit_gap);
        }
        if(!json_context["emit_count"].is_null()){
            Serializer::read(json_context["emit_count"], instance.m_emit_count);
        }
        if(!json_context["time_step"].is_null()){
            Serializer::read(json_context["time_step"], instance.m_time_step);
        }
        if(!json_context["max_life"].is_null()){
            Serializer::read(json_context["max_life"], instance.m_max_life);
        }
        if(!json_context["gravity"].is_null()){
            Serializer::read(json_context["gravity"], instance.m_gravity);
        }
        if(!json_context["particle_billboard_texture_path"].is_null()){
            Serializer::read(json_context["particle_billboard_texture_path"], instance.m_particle_billboard_texture_path);
        }
        if(!json_context["piccolo_logo_texture_path"].is_null()){
            Serializer::read(json_context["piccolo_logo_texture_path"], instance.m_piccolo_logo_texture_path);
        }
        return instance;
    }

}

