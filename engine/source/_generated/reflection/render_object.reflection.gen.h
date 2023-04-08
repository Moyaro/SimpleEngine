#pragma once
#include "runtime\function\render\render_object.h"

namespace SimpleEngine{
    class GameObjectMeshDesc;
    class GameObjectMaterialDesc;
    class GameObjectTransformDesc;
    class GameObjectPartDesc;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeGameObjectMeshDescOperator{
    public:
        static const char* getClassName(){ return "GameObjectMeshDesc";}
        static void* constructorWithJson(const Json& json_context){
            GameObjectMeshDesc* ret_instance= new GameObjectMeshDesc;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GameObjectMeshDesc*)instance);
        }
        // base class
        static int getGameObjectMeshDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_mesh_file(){ return "m_mesh_file";}
        static const char* getFieldTypeName_m_mesh_file(){ return "std::string";}
        static void set_m_mesh_file(void* instance, void* field_value){ static_cast<GameObjectMeshDesc*>(instance)->m_mesh_file = *static_cast<std::string*>(field_value);}
        static void* get_m_mesh_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMeshDesc*>(instance)->m_mesh_file));}
        static bool isArray_m_mesh_file(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectMeshDesc(){
    FieldFunctionTuple* field_function_tuple_m_mesh_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::set_m_mesh_file,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::get_m_mesh_file,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::getFieldName_m_mesh_file,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::getFieldTypeName_m_mesh_file,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::isArray_m_mesh_file);
    REGISTER_FIELD_TO_MAP("GameObjectMeshDesc", field_function_tuple_m_mesh_file);

    

    
    ClassFunctionTuple* class_function_tuple_GameObjectMeshDesc=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::getGameObjectMeshDescBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GameObjectMeshDesc", class_function_tuple_GameObjectMeshDesc);
    }namespace TypeFieldReflectionOparator{
    class TypeGameObjectMaterialDescOperator{
    public:
        static const char* getClassName(){ return "GameObjectMaterialDesc";}
        static void* constructorWithJson(const Json& json_context){
            GameObjectMaterialDesc* ret_instance= new GameObjectMaterialDesc;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GameObjectMaterialDesc*)instance);
        }
        // base class
        static int getGameObjectMaterialDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_base_color_texture_file(){ return "m_base_color_texture_file";}
        static const char* getFieldTypeName_m_base_color_texture_file(){ return "std::string";}
        static void set_m_base_color_texture_file(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_base_color_texture_file = *static_cast<std::string*>(field_value);}
        static void* get_m_base_color_texture_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_base_color_texture_file));}
        static bool isArray_m_base_color_texture_file(){ return false; }
        static const char* getFieldName_m_metallic_roughness_texture_file(){ return "m_metallic_roughness_texture_file";}
        static const char* getFieldTypeName_m_metallic_roughness_texture_file(){ return "std::string";}
        static void set_m_metallic_roughness_texture_file(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_metallic_roughness_texture_file = *static_cast<std::string*>(field_value);}
        static void* get_m_metallic_roughness_texture_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_metallic_roughness_texture_file));}
        static bool isArray_m_metallic_roughness_texture_file(){ return false; }
        static const char* getFieldName_m_normal_texture_file(){ return "m_normal_texture_file";}
        static const char* getFieldTypeName_m_normal_texture_file(){ return "std::string";}
        static void set_m_normal_texture_file(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_normal_texture_file = *static_cast<std::string*>(field_value);}
        static void* get_m_normal_texture_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_normal_texture_file));}
        static bool isArray_m_normal_texture_file(){ return false; }
        static const char* getFieldName_m_occlusion_texture_file(){ return "m_occlusion_texture_file";}
        static const char* getFieldTypeName_m_occlusion_texture_file(){ return "std::string";}
        static void set_m_occlusion_texture_file(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_occlusion_texture_file = *static_cast<std::string*>(field_value);}
        static void* get_m_occlusion_texture_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_occlusion_texture_file));}
        static bool isArray_m_occlusion_texture_file(){ return false; }
        static const char* getFieldName_m_emissive_texture_file(){ return "m_emissive_texture_file";}
        static const char* getFieldTypeName_m_emissive_texture_file(){ return "std::string";}
        static void set_m_emissive_texture_file(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_emissive_texture_file = *static_cast<std::string*>(field_value);}
        static void* get_m_emissive_texture_file(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_emissive_texture_file));}
        static bool isArray_m_emissive_texture_file(){ return false; }
        static const char* getFieldName_m_with_texture(){ return "m_with_texture";}
        static const char* getFieldTypeName_m_with_texture(){ return "bool";}
        static void set_m_with_texture(void* instance, void* field_value){ static_cast<GameObjectMaterialDesc*>(instance)->m_with_texture = *static_cast<bool*>(field_value);}
        static void* get_m_with_texture(void* instance){ return static_cast<void*>(&(static_cast<GameObjectMaterialDesc*>(instance)->m_with_texture));}
        static bool isArray_m_with_texture(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectMaterialDesc(){
    FieldFunctionTuple* field_function_tuple_m_base_color_texture_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_base_color_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_base_color_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_base_color_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_base_color_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_base_color_texture_file);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_base_color_texture_file);
    FieldFunctionTuple* field_function_tuple_m_metallic_roughness_texture_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_metallic_roughness_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_metallic_roughness_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_metallic_roughness_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_metallic_roughness_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_metallic_roughness_texture_file);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_metallic_roughness_texture_file);
    FieldFunctionTuple* field_function_tuple_m_normal_texture_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_normal_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_normal_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_normal_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_normal_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_normal_texture_file);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_normal_texture_file);
    FieldFunctionTuple* field_function_tuple_m_occlusion_texture_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_occlusion_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_occlusion_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_occlusion_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_occlusion_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_occlusion_texture_file);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_occlusion_texture_file);
    FieldFunctionTuple* field_function_tuple_m_emissive_texture_file=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_emissive_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_emissive_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_emissive_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_emissive_texture_file,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_emissive_texture_file);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_emissive_texture_file);
    FieldFunctionTuple* field_function_tuple_m_with_texture=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::set_m_with_texture,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::get_m_with_texture,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldName_m_with_texture,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getFieldTypeName_m_with_texture,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::isArray_m_with_texture);
    REGISTER_FIELD_TO_MAP("GameObjectMaterialDesc", field_function_tuple_m_with_texture);

    

    
    ClassFunctionTuple* class_function_tuple_GameObjectMaterialDesc=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::getGameObjectMaterialDescBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGameObjectMaterialDescOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GameObjectMaterialDesc", class_function_tuple_GameObjectMaterialDesc);
    }namespace TypeFieldReflectionOparator{
    class TypeGameObjectTransformDescOperator{
    public:
        static const char* getClassName(){ return "GameObjectTransformDesc";}
        static void* constructorWithJson(const Json& json_context){
            GameObjectTransformDesc* ret_instance= new GameObjectTransformDesc;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GameObjectTransformDesc*)instance);
        }
        // base class
        static int getGameObjectTransformDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectTransformDesc(){
    

    

    
    ClassFunctionTuple* class_function_tuple_GameObjectTransformDesc=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectTransformDescOperator::getGameObjectTransformDescBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGameObjectTransformDescOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGameObjectTransformDescOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GameObjectTransformDesc", class_function_tuple_GameObjectTransformDesc);
    }namespace TypeFieldReflectionOparator{
    class TypeGameObjectPartDescOperator{
    public:
        static const char* getClassName(){ return "GameObjectPartDesc";}
        static void* constructorWithJson(const Json& json_context){
            GameObjectPartDesc* ret_instance= new GameObjectPartDesc;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GameObjectPartDesc*)instance);
        }
        // base class
        static int getGameObjectPartDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_mesh_desc(){ return "m_mesh_desc";}
        static const char* getFieldTypeName_m_mesh_desc(){ return "GameObjectMeshDesc";}
        static void set_m_mesh_desc(void* instance, void* field_value){ static_cast<GameObjectPartDesc*>(instance)->m_mesh_desc = *static_cast<GameObjectMeshDesc*>(field_value);}
        static void* get_m_mesh_desc(void* instance){ return static_cast<void*>(&(static_cast<GameObjectPartDesc*>(instance)->m_mesh_desc));}
        static bool isArray_m_mesh_desc(){ return false; }
        static const char* getFieldName_m_material_desc(){ return "m_material_desc";}
        static const char* getFieldTypeName_m_material_desc(){ return "GameObjectMaterialDesc";}
        static void set_m_material_desc(void* instance, void* field_value){ static_cast<GameObjectPartDesc*>(instance)->m_material_desc = *static_cast<GameObjectMaterialDesc*>(field_value);}
        static void* get_m_material_desc(void* instance){ return static_cast<void*>(&(static_cast<GameObjectPartDesc*>(instance)->m_material_desc));}
        static bool isArray_m_material_desc(){ return false; }
        static const char* getFieldName_m_transform_desc(){ return "m_transform_desc";}
        static const char* getFieldTypeName_m_transform_desc(){ return "GameObjectTransformDesc";}
        static void set_m_transform_desc(void* instance, void* field_value){ static_cast<GameObjectPartDesc*>(instance)->m_transform_desc = *static_cast<GameObjectTransformDesc*>(field_value);}
        static void* get_m_transform_desc(void* instance){ return static_cast<void*>(&(static_cast<GameObjectPartDesc*>(instance)->m_transform_desc));}
        static bool isArray_m_transform_desc(){ return false; }
        static const char* getFieldName_m_with_animation(){ return "m_with_animation";}
        static const char* getFieldTypeName_m_with_animation(){ return "bool";}
        static void set_m_with_animation(void* instance, void* field_value){ static_cast<GameObjectPartDesc*>(instance)->m_with_animation = *static_cast<bool*>(field_value);}
        static void* get_m_with_animation(void* instance){ return static_cast<void*>(&(static_cast<GameObjectPartDesc*>(instance)->m_with_animation));}
        static bool isArray_m_with_animation(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectPartDesc(){
    FieldFunctionTuple* field_function_tuple_m_mesh_desc=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::set_m_mesh_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::get_m_mesh_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldName_m_mesh_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldTypeName_m_mesh_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::isArray_m_mesh_desc);
    REGISTER_FIELD_TO_MAP("GameObjectPartDesc", field_function_tuple_m_mesh_desc);
    FieldFunctionTuple* field_function_tuple_m_material_desc=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::set_m_material_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::get_m_material_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldName_m_material_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldTypeName_m_material_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::isArray_m_material_desc);
    REGISTER_FIELD_TO_MAP("GameObjectPartDesc", field_function_tuple_m_material_desc);
    FieldFunctionTuple* field_function_tuple_m_transform_desc=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::set_m_transform_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::get_m_transform_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldName_m_transform_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldTypeName_m_transform_desc,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::isArray_m_transform_desc);
    REGISTER_FIELD_TO_MAP("GameObjectPartDesc", field_function_tuple_m_transform_desc);
    FieldFunctionTuple* field_function_tuple_m_with_animation=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::set_m_with_animation,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::get_m_with_animation,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldName_m_with_animation,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getFieldTypeName_m_with_animation,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::isArray_m_with_animation);
    REGISTER_FIELD_TO_MAP("GameObjectPartDesc", field_function_tuple_m_with_animation);

    

    
    ClassFunctionTuple* class_function_tuple_GameObjectPartDesc=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getGameObjectPartDescBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GameObjectPartDesc", class_function_tuple_GameObjectPartDesc);
    }
    namespace TypeWrappersRegister{
    void RenderObject()
    {
    TypeWrapperRegister_GameObjectMeshDesc();
    TypeWrapperRegister_GameObjectMaterialDesc();
    TypeWrapperRegister_GameObjectTransformDesc();
    TypeWrapperRegister_GameObjectPartDesc();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

