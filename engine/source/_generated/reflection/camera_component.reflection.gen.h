#pragma once
#include "runtime\function\framework\component\camera\camera_component.h"

namespace SimpleEngine{
    class CameraComponent;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeCameraComponentOperator{
    public:
        static const char* getClassName(){ return "CameraComponent";}
        static void* constructorWithJson(const Json& json_context){
            CameraComponent* ret_instance= new CameraComponent;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(CameraComponent*)instance);
        }
        // base class
        static int getCameraComponentBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::Component,static_cast<CameraComponent*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_camera_res(){ return "m_camera_res";}
        static const char* getFieldTypeName_m_camera_res(){ return "CameraComponentRes";}
        static void set_m_camera_res(void* instance, void* field_value){ static_cast<CameraComponent*>(instance)->m_camera_res = *static_cast<CameraComponentRes*>(field_value);}
        static void* get_m_camera_res(void* instance){ return static_cast<void*>(&(static_cast<CameraComponent*>(instance)->m_camera_res));}
        static bool isArray_m_camera_res(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_CameraComponent(){
    FieldFunctionTuple* field_function_tuple_m_camera_res=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::set_m_camera_res,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::get_m_camera_res,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::getClassName,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::getFieldName_m_camera_res,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::getFieldTypeName_m_camera_res,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::isArray_m_camera_res);
    REGISTER_FIELD_TO_MAP("CameraComponent", field_function_tuple_m_camera_res);

    

    
    ClassFunctionTuple* class_function_tuple_CameraComponent=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::getCameraComponentBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeCameraComponentOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("CameraComponent", class_function_tuple_CameraComponent);
    }
    namespace TypeWrappersRegister{
    void CameraComponent()
    {
    TypeWrapperRegister_CameraComponent();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

