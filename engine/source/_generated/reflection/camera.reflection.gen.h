#pragma once
#include "runtime\resource\res_type\components\camera.h"

namespace SimpleEngine{
    class CameraParameter;
    class FirstPersonCameraParameter;
    class ThirdPersonCameraParameter;
    class FreeCameraParameter;
    class CameraComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeCameraParameterOperator{
    public:
        static const char* getClassName(){ return "CameraParameter";}
        static void* constructorWithJson(const Json& json_context){
            CameraParameter* ret_instance= new CameraParameter;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(CameraParameter*)instance);
        }
        // base class
        static int getCameraParameterBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_fov(){ return "m_fov";}
        static const char* getFieldTypeName_m_fov(){ return "float";}
        static void set_m_fov(void* instance, void* field_value){ static_cast<CameraParameter*>(instance)->m_fov = *static_cast<float*>(field_value);}
        static void* get_m_fov(void* instance){ return static_cast<void*>(&(static_cast<CameraParameter*>(instance)->m_fov));}
        static bool isArray_m_fov(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_CameraParameter(){
    FieldFunctionTuple* field_function_tuple_m_fov=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::set_m_fov,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::get_m_fov,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::getClassName,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::getFieldName_m_fov,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::getFieldTypeName_m_fov,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::isArray_m_fov);
    REGISTER_FIELD_TO_MAP("CameraParameter", field_function_tuple_m_fov);

    

    
    ClassFunctionTuple* class_function_tuple_CameraParameter=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::getCameraParameterBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeCameraParameterOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("CameraParameter", class_function_tuple_CameraParameter);
    }namespace TypeFieldReflectionOparator{
    class TypeFirstPersonCameraParameterOperator{
    public:
        static const char* getClassName(){ return "FirstPersonCameraParameter";}
        static void* constructorWithJson(const Json& json_context){
            FirstPersonCameraParameter* ret_instance= new FirstPersonCameraParameter;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(FirstPersonCameraParameter*)instance);
        }
        // base class
        static int getFirstPersonCameraParameterBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::CameraParameter,static_cast<FirstPersonCameraParameter*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_vertical_offset(){ return "m_vertical_offset";}
        static const char* getFieldTypeName_m_vertical_offset(){ return "float";}
        static void set_m_vertical_offset(void* instance, void* field_value){ static_cast<FirstPersonCameraParameter*>(instance)->m_vertical_offset = *static_cast<float*>(field_value);}
        static void* get_m_vertical_offset(void* instance){ return static_cast<void*>(&(static_cast<FirstPersonCameraParameter*>(instance)->m_vertical_offset));}
        static bool isArray_m_vertical_offset(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_FirstPersonCameraParameter(){
    FieldFunctionTuple* field_function_tuple_m_vertical_offset=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::set_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::get_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::getClassName,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::getFieldName_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::getFieldTypeName_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::isArray_m_vertical_offset);
    REGISTER_FIELD_TO_MAP("FirstPersonCameraParameter", field_function_tuple_m_vertical_offset);

    

    
    ClassFunctionTuple* class_function_tuple_FirstPersonCameraParameter=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::getFirstPersonCameraParameterBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeFirstPersonCameraParameterOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("FirstPersonCameraParameter", class_function_tuple_FirstPersonCameraParameter);
    }namespace TypeFieldReflectionOparator{
    class TypeThirdPersonCameraParameterOperator{
    public:
        static const char* getClassName(){ return "ThirdPersonCameraParameter";}
        static void* constructorWithJson(const Json& json_context){
            ThirdPersonCameraParameter* ret_instance= new ThirdPersonCameraParameter;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(ThirdPersonCameraParameter*)instance);
        }
        // base class
        static int getThirdPersonCameraParameterBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::CameraParameter,static_cast<ThirdPersonCameraParameter*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_horizontal_offset(){ return "m_horizontal_offset";}
        static const char* getFieldTypeName_m_horizontal_offset(){ return "float";}
        static void set_m_horizontal_offset(void* instance, void* field_value){ static_cast<ThirdPersonCameraParameter*>(instance)->m_horizontal_offset = *static_cast<float*>(field_value);}
        static void* get_m_horizontal_offset(void* instance){ return static_cast<void*>(&(static_cast<ThirdPersonCameraParameter*>(instance)->m_horizontal_offset));}
        static bool isArray_m_horizontal_offset(){ return false; }
        static const char* getFieldName_m_vertical_offset(){ return "m_vertical_offset";}
        static const char* getFieldTypeName_m_vertical_offset(){ return "float";}
        static void set_m_vertical_offset(void* instance, void* field_value){ static_cast<ThirdPersonCameraParameter*>(instance)->m_vertical_offset = *static_cast<float*>(field_value);}
        static void* get_m_vertical_offset(void* instance){ return static_cast<void*>(&(static_cast<ThirdPersonCameraParameter*>(instance)->m_vertical_offset));}
        static bool isArray_m_vertical_offset(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_ThirdPersonCameraParameter(){
    FieldFunctionTuple* field_function_tuple_m_horizontal_offset=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::set_m_horizontal_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::get_m_horizontal_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getClassName,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getFieldName_m_horizontal_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getFieldTypeName_m_horizontal_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::isArray_m_horizontal_offset);
    REGISTER_FIELD_TO_MAP("ThirdPersonCameraParameter", field_function_tuple_m_horizontal_offset);
    FieldFunctionTuple* field_function_tuple_m_vertical_offset=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::set_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::get_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getClassName,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getFieldName_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getFieldTypeName_m_vertical_offset,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::isArray_m_vertical_offset);
    REGISTER_FIELD_TO_MAP("ThirdPersonCameraParameter", field_function_tuple_m_vertical_offset);

    

    
    ClassFunctionTuple* class_function_tuple_ThirdPersonCameraParameter=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::getThirdPersonCameraParameterBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeThirdPersonCameraParameterOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("ThirdPersonCameraParameter", class_function_tuple_ThirdPersonCameraParameter);
    }namespace TypeFieldReflectionOparator{
    class TypeFreeCameraParameterOperator{
    public:
        static const char* getClassName(){ return "FreeCameraParameter";}
        static void* constructorWithJson(const Json& json_context){
            FreeCameraParameter* ret_instance= new FreeCameraParameter;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(FreeCameraParameter*)instance);
        }
        // base class
        static int getFreeCameraParameterBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::CameraParameter,static_cast<FreeCameraParameter*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_speed(){ return "m_speed";}
        static const char* getFieldTypeName_m_speed(){ return "float";}
        static void set_m_speed(void* instance, void* field_value){ static_cast<FreeCameraParameter*>(instance)->m_speed = *static_cast<float*>(field_value);}
        static void* get_m_speed(void* instance){ return static_cast<void*>(&(static_cast<FreeCameraParameter*>(instance)->m_speed));}
        static bool isArray_m_speed(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_FreeCameraParameter(){
    FieldFunctionTuple* field_function_tuple_m_speed=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::set_m_speed,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::get_m_speed,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::getClassName,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::getFieldName_m_speed,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::getFieldTypeName_m_speed,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::isArray_m_speed);
    REGISTER_FIELD_TO_MAP("FreeCameraParameter", field_function_tuple_m_speed);

    

    
    ClassFunctionTuple* class_function_tuple_FreeCameraParameter=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::getFreeCameraParameterBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeFreeCameraParameterOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("FreeCameraParameter", class_function_tuple_FreeCameraParameter);
    }namespace TypeFieldReflectionOparator{
    class TypeCameraComponentResOperator{
    public:
        static const char* getClassName(){ return "CameraComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            CameraComponentRes* ret_instance= new CameraComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(CameraComponentRes*)instance);
        }
        // base class
        static int getCameraComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_parameter(){ return "m_parameter";}
        static const char* getFieldTypeName_m_parameter(){ return "Reflection::ReflectionPtr<CameraParameter>";}
        static void set_m_parameter(void* instance, void* field_value){ static_cast<CameraComponentRes*>(instance)->m_parameter = *static_cast<Reflection::ReflectionPtr<CameraParameter>*>(field_value);}
        static void* get_m_parameter(void* instance){ return static_cast<void*>(&(static_cast<CameraComponentRes*>(instance)->m_parameter));}
        static bool isArray_m_parameter(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_CameraComponentRes(){
    FieldFunctionTuple* field_function_tuple_m_parameter=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::set_m_parameter,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::get_m_parameter,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::getFieldName_m_parameter,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::getFieldTypeName_m_parameter,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::isArray_m_parameter);
    REGISTER_FIELD_TO_MAP("CameraComponentRes", field_function_tuple_m_parameter);

    

    
    ClassFunctionTuple* class_function_tuple_CameraComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::getCameraComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeCameraComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("CameraComponentRes", class_function_tuple_CameraComponentRes);
    }
    namespace TypeWrappersRegister{
    void Camera()
    {
    TypeWrapperRegister_CameraParameter();
    TypeWrapperRegister_FirstPersonCameraParameter();
    TypeWrapperRegister_ThirdPersonCameraParameter();
    TypeWrapperRegister_FreeCameraParameter();
    TypeWrapperRegister_CameraComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

