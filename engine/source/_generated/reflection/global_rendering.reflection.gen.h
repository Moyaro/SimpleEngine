#pragma once
#include "runtime\resource\res_type\global\global_rendering.h"

namespace SimpleEngine{
    class SkyBoxIrradianceMap;
    class SkyBoxSpecularMap;
    class DirectionalLight;
    class GlobalRenderingRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeSkyBoxIrradianceMapOperator{
    public:
        static const char* getClassName(){ return "SkyBoxIrradianceMap";}
        static void* constructorWithJson(const Json& json_context){
            SkyBoxIrradianceMap* ret_instance= new SkyBoxIrradianceMap;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(SkyBoxIrradianceMap*)instance);
        }
        // base class
        static int getSkyBoxIrradianceMapBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_negative_x_map(){ return "m_negative_x_map";}
        static const char* getFieldTypeName_m_negative_x_map(){ return "std::string";}
        static void set_m_negative_x_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_x_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_x_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_x_map));}
        static bool isArray_m_negative_x_map(){ return false; }
        static const char* getFieldName_m_positive_x_map(){ return "m_positive_x_map";}
        static const char* getFieldTypeName_m_positive_x_map(){ return "std::string";}
        static void set_m_positive_x_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_x_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_x_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_x_map));}
        static bool isArray_m_positive_x_map(){ return false; }
        static const char* getFieldName_m_negative_y_map(){ return "m_negative_y_map";}
        static const char* getFieldTypeName_m_negative_y_map(){ return "std::string";}
        static void set_m_negative_y_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_y_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_y_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_y_map));}
        static bool isArray_m_negative_y_map(){ return false; }
        static const char* getFieldName_m_positive_y_map(){ return "m_positive_y_map";}
        static const char* getFieldTypeName_m_positive_y_map(){ return "std::string";}
        static void set_m_positive_y_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_y_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_y_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_y_map));}
        static bool isArray_m_positive_y_map(){ return false; }
        static const char* getFieldName_m_negative_z_map(){ return "m_negative_z_map";}
        static const char* getFieldTypeName_m_negative_z_map(){ return "std::string";}
        static void set_m_negative_z_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_z_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_z_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_negative_z_map));}
        static bool isArray_m_negative_z_map(){ return false; }
        static const char* getFieldName_m_positive_z_map(){ return "m_positive_z_map";}
        static const char* getFieldTypeName_m_positive_z_map(){ return "std::string";}
        static void set_m_positive_z_map(void* instance, void* field_value){ static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_z_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_z_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxIrradianceMap*>(instance)->m_positive_z_map));}
        static bool isArray_m_positive_z_map(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_SkyBoxIrradianceMap(){
    FieldFunctionTuple* field_function_tuple_m_negative_x_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_negative_x_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_negative_x_map);
    FieldFunctionTuple* field_function_tuple_m_positive_x_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_positive_x_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_positive_x_map);
    FieldFunctionTuple* field_function_tuple_m_negative_y_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_negative_y_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_negative_y_map);
    FieldFunctionTuple* field_function_tuple_m_positive_y_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_positive_y_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_positive_y_map);
    FieldFunctionTuple* field_function_tuple_m_negative_z_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_negative_z_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_negative_z_map);
    FieldFunctionTuple* field_function_tuple_m_positive_z_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::set_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::get_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldName_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getFieldTypeName_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::isArray_m_positive_z_map);
    REGISTER_FIELD_TO_MAP("SkyBoxIrradianceMap", field_function_tuple_m_positive_z_map);

    

    
    ClassFunctionTuple* class_function_tuple_SkyBoxIrradianceMap=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::getSkyBoxIrradianceMapBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSkyBoxIrradianceMapOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("SkyBoxIrradianceMap", class_function_tuple_SkyBoxIrradianceMap);
    }namespace TypeFieldReflectionOparator{
    class TypeSkyBoxSpecularMapOperator{
    public:
        static const char* getClassName(){ return "SkyBoxSpecularMap";}
        static void* constructorWithJson(const Json& json_context){
            SkyBoxSpecularMap* ret_instance= new SkyBoxSpecularMap;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(SkyBoxSpecularMap*)instance);
        }
        // base class
        static int getSkyBoxSpecularMapBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_negative_x_map(){ return "m_negative_x_map";}
        static const char* getFieldTypeName_m_negative_x_map(){ return "std::string";}
        static void set_m_negative_x_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_negative_x_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_x_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_negative_x_map));}
        static bool isArray_m_negative_x_map(){ return false; }
        static const char* getFieldName_m_positive_x_map(){ return "m_positive_x_map";}
        static const char* getFieldTypeName_m_positive_x_map(){ return "std::string";}
        static void set_m_positive_x_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_positive_x_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_x_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_positive_x_map));}
        static bool isArray_m_positive_x_map(){ return false; }
        static const char* getFieldName_m_negative_y_map(){ return "m_negative_y_map";}
        static const char* getFieldTypeName_m_negative_y_map(){ return "std::string";}
        static void set_m_negative_y_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_negative_y_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_y_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_negative_y_map));}
        static bool isArray_m_negative_y_map(){ return false; }
        static const char* getFieldName_m_positive_y_map(){ return "m_positive_y_map";}
        static const char* getFieldTypeName_m_positive_y_map(){ return "std::string";}
        static void set_m_positive_y_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_positive_y_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_y_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_positive_y_map));}
        static bool isArray_m_positive_y_map(){ return false; }
        static const char* getFieldName_m_negative_z_map(){ return "m_negative_z_map";}
        static const char* getFieldTypeName_m_negative_z_map(){ return "std::string";}
        static void set_m_negative_z_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_negative_z_map = *static_cast<std::string*>(field_value);}
        static void* get_m_negative_z_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_negative_z_map));}
        static bool isArray_m_negative_z_map(){ return false; }
        static const char* getFieldName_m_positive_z_map(){ return "m_positive_z_map";}
        static const char* getFieldTypeName_m_positive_z_map(){ return "std::string";}
        static void set_m_positive_z_map(void* instance, void* field_value){ static_cast<SkyBoxSpecularMap*>(instance)->m_positive_z_map = *static_cast<std::string*>(field_value);}
        static void* get_m_positive_z_map(void* instance){ return static_cast<void*>(&(static_cast<SkyBoxSpecularMap*>(instance)->m_positive_z_map));}
        static bool isArray_m_positive_z_map(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_SkyBoxSpecularMap(){
    FieldFunctionTuple* field_function_tuple_m_negative_x_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_negative_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_negative_x_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_negative_x_map);
    FieldFunctionTuple* field_function_tuple_m_positive_x_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_positive_x_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_positive_x_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_positive_x_map);
    FieldFunctionTuple* field_function_tuple_m_negative_y_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_negative_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_negative_y_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_negative_y_map);
    FieldFunctionTuple* field_function_tuple_m_positive_y_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_positive_y_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_positive_y_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_positive_y_map);
    FieldFunctionTuple* field_function_tuple_m_negative_z_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_negative_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_negative_z_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_negative_z_map);
    FieldFunctionTuple* field_function_tuple_m_positive_z_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::set_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::get_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldName_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getFieldTypeName_m_positive_z_map,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::isArray_m_positive_z_map);
    REGISTER_FIELD_TO_MAP("SkyBoxSpecularMap", field_function_tuple_m_positive_z_map);

    

    
    ClassFunctionTuple* class_function_tuple_SkyBoxSpecularMap=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::getSkyBoxSpecularMapBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSkyBoxSpecularMapOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("SkyBoxSpecularMap", class_function_tuple_SkyBoxSpecularMap);
    }namespace TypeFieldReflectionOparator{
    class TypeDirectionalLightOperator{
    public:
        static const char* getClassName(){ return "DirectionalLight";}
        static void* constructorWithJson(const Json& json_context){
            DirectionalLight* ret_instance= new DirectionalLight;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(DirectionalLight*)instance);
        }
        // base class
        static int getDirectionalLightBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_direction(){ return "m_direction";}
        static const char* getFieldTypeName_m_direction(){ return "Vector3";}
        static void set_m_direction(void* instance, void* field_value){ static_cast<DirectionalLight*>(instance)->m_direction = *static_cast<Vector3*>(field_value);}
        static void* get_m_direction(void* instance){ return static_cast<void*>(&(static_cast<DirectionalLight*>(instance)->m_direction));}
        static bool isArray_m_direction(){ return false; }
        static const char* getFieldName_m_color(){ return "m_color";}
        static const char* getFieldTypeName_m_color(){ return "Color";}
        static void set_m_color(void* instance, void* field_value){ static_cast<DirectionalLight*>(instance)->m_color = *static_cast<Color*>(field_value);}
        static void* get_m_color(void* instance){ return static_cast<void*>(&(static_cast<DirectionalLight*>(instance)->m_color));}
        static bool isArray_m_color(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_DirectionalLight(){
    FieldFunctionTuple* field_function_tuple_m_direction=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::set_m_direction,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::get_m_direction,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getClassName,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getFieldName_m_direction,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getFieldTypeName_m_direction,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::isArray_m_direction);
    REGISTER_FIELD_TO_MAP("DirectionalLight", field_function_tuple_m_direction);
    FieldFunctionTuple* field_function_tuple_m_color=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::set_m_color,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::get_m_color,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getClassName,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getFieldName_m_color,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getFieldTypeName_m_color,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::isArray_m_color);
    REGISTER_FIELD_TO_MAP("DirectionalLight", field_function_tuple_m_color);

    

    
    ClassFunctionTuple* class_function_tuple_DirectionalLight=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::getDirectionalLightBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeDirectionalLightOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("DirectionalLight", class_function_tuple_DirectionalLight);
    }namespace TypeFieldReflectionOparator{
    class TypeGlobalRenderingResOperator{
    public:
        static const char* getClassName(){ return "GlobalRenderingRes";}
        static void* constructorWithJson(const Json& json_context){
            GlobalRenderingRes* ret_instance= new GlobalRenderingRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GlobalRenderingRes*)instance);
        }
        // base class
        static int getGlobalRenderingResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_enable_fxaa(){ return "m_enable_fxaa";}
        static const char* getFieldTypeName_m_enable_fxaa(){ return "bool";}
        static void set_m_enable_fxaa(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_enable_fxaa = *static_cast<bool*>(field_value);}
        static void* get_m_enable_fxaa(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_enable_fxaa));}
        static bool isArray_m_enable_fxaa(){ return false; }
        static const char* getFieldName_m_skybox_irradiance_map(){ return "m_skybox_irradiance_map";}
        static const char* getFieldTypeName_m_skybox_irradiance_map(){ return "SkyBoxIrradianceMap";}
        static void set_m_skybox_irradiance_map(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_skybox_irradiance_map = *static_cast<SkyBoxIrradianceMap*>(field_value);}
        static void* get_m_skybox_irradiance_map(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_skybox_irradiance_map));}
        static bool isArray_m_skybox_irradiance_map(){ return false; }
        static const char* getFieldName_m_skybox_specular_map(){ return "m_skybox_specular_map";}
        static const char* getFieldTypeName_m_skybox_specular_map(){ return "SkyBoxSpecularMap";}
        static void set_m_skybox_specular_map(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_skybox_specular_map = *static_cast<SkyBoxSpecularMap*>(field_value);}
        static void* get_m_skybox_specular_map(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_skybox_specular_map));}
        static bool isArray_m_skybox_specular_map(){ return false; }
        static const char* getFieldName_m_brdf_map(){ return "m_brdf_map";}
        static const char* getFieldTypeName_m_brdf_map(){ return "std::string";}
        static void set_m_brdf_map(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_brdf_map = *static_cast<std::string*>(field_value);}
        static void* get_m_brdf_map(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_brdf_map));}
        static bool isArray_m_brdf_map(){ return false; }
        static const char* getFieldName_m_color_grading_map(){ return "m_color_grading_map";}
        static const char* getFieldTypeName_m_color_grading_map(){ return "std::string";}
        static void set_m_color_grading_map(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_color_grading_map = *static_cast<std::string*>(field_value);}
        static void* get_m_color_grading_map(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_color_grading_map));}
        static bool isArray_m_color_grading_map(){ return false; }
        static const char* getFieldName_m_sky_color(){ return "m_sky_color";}
        static const char* getFieldTypeName_m_sky_color(){ return "Color";}
        static void set_m_sky_color(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_sky_color = *static_cast<Color*>(field_value);}
        static void* get_m_sky_color(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_sky_color));}
        static bool isArray_m_sky_color(){ return false; }
        static const char* getFieldName_m_ambient_light(){ return "m_ambient_light";}
        static const char* getFieldTypeName_m_ambient_light(){ return "Color";}
        static void set_m_ambient_light(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_ambient_light = *static_cast<Color*>(field_value);}
        static void* get_m_ambient_light(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_ambient_light));}
        static bool isArray_m_ambient_light(){ return false; }
        static const char* getFieldName_m_camera_config(){ return "m_camera_config";}
        static const char* getFieldTypeName_m_camera_config(){ return "CameraConfig";}
        static void set_m_camera_config(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_camera_config = *static_cast<CameraConfig*>(field_value);}
        static void* get_m_camera_config(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_camera_config));}
        static bool isArray_m_camera_config(){ return false; }
        static const char* getFieldName_m_directional_light(){ return "m_directional_light";}
        static const char* getFieldTypeName_m_directional_light(){ return "DirectionalLight";}
        static void set_m_directional_light(void* instance, void* field_value){ static_cast<GlobalRenderingRes*>(instance)->m_directional_light = *static_cast<DirectionalLight*>(field_value);}
        static void* get_m_directional_light(void* instance){ return static_cast<void*>(&(static_cast<GlobalRenderingRes*>(instance)->m_directional_light));}
        static bool isArray_m_directional_light(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GlobalRenderingRes(){
    FieldFunctionTuple* field_function_tuple_m_enable_fxaa=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_enable_fxaa,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_enable_fxaa,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_enable_fxaa,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_enable_fxaa,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_enable_fxaa);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_enable_fxaa);
    FieldFunctionTuple* field_function_tuple_m_skybox_irradiance_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_skybox_irradiance_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_skybox_irradiance_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_skybox_irradiance_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_skybox_irradiance_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_skybox_irradiance_map);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_skybox_irradiance_map);
    FieldFunctionTuple* field_function_tuple_m_skybox_specular_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_skybox_specular_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_skybox_specular_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_skybox_specular_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_skybox_specular_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_skybox_specular_map);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_skybox_specular_map);
    FieldFunctionTuple* field_function_tuple_m_brdf_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_brdf_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_brdf_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_brdf_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_brdf_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_brdf_map);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_brdf_map);
    FieldFunctionTuple* field_function_tuple_m_color_grading_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_color_grading_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_color_grading_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_color_grading_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_color_grading_map,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_color_grading_map);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_color_grading_map);
    FieldFunctionTuple* field_function_tuple_m_sky_color=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_sky_color,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_sky_color,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_sky_color,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_sky_color,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_sky_color);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_sky_color);
    FieldFunctionTuple* field_function_tuple_m_ambient_light=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_ambient_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_ambient_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_ambient_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_ambient_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_ambient_light);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_ambient_light);
    FieldFunctionTuple* field_function_tuple_m_camera_config=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_camera_config,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_camera_config,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_camera_config,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_camera_config,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_camera_config);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_camera_config);
    FieldFunctionTuple* field_function_tuple_m_directional_light=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::set_m_directional_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::get_m_directional_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldName_m_directional_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getFieldTypeName_m_directional_light,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::isArray_m_directional_light);
    REGISTER_FIELD_TO_MAP("GlobalRenderingRes", field_function_tuple_m_directional_light);

    

    
    ClassFunctionTuple* class_function_tuple_GlobalRenderingRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::getGlobalRenderingResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGlobalRenderingResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GlobalRenderingRes", class_function_tuple_GlobalRenderingRes);
    }
    namespace TypeWrappersRegister{
    void GlobalRendering()
    {
    TypeWrapperRegister_SkyBoxIrradianceMap();
    TypeWrapperRegister_SkyBoxSpecularMap();
    TypeWrapperRegister_DirectionalLight();
    TypeWrapperRegister_GlobalRenderingRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

