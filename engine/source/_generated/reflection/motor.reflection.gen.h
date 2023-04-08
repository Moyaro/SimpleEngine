#pragma once
#include "runtime\resource\res_type\components\motor.h"

namespace SimpleEngine{
    class ControllerConfig;
    class PhysicsControllerConfig;
    class MotorComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeControllerConfigOperator{
    public:
        static const char* getClassName(){ return "ControllerConfig";}
        static void* constructorWithJson(const Json& json_context){
            ControllerConfig* ret_instance= new ControllerConfig;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(ControllerConfig*)instance);
        }
        // base class
        static int getControllerConfigBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_ControllerConfig(){
    

    

    
    ClassFunctionTuple* class_function_tuple_ControllerConfig=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeControllerConfigOperator::getControllerConfigBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeControllerConfigOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeControllerConfigOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("ControllerConfig", class_function_tuple_ControllerConfig);
    }namespace TypeFieldReflectionOparator{
    class TypePhysicsControllerConfigOperator{
    public:
        static const char* getClassName(){ return "PhysicsControllerConfig";}
        static void* constructorWithJson(const Json& json_context){
            PhysicsControllerConfig* ret_instance= new PhysicsControllerConfig;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(PhysicsControllerConfig*)instance);
        }
        // base class
        static int getPhysicsControllerConfigBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::ControllerConfig,static_cast<PhysicsControllerConfig*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_capsule_shape(){ return "m_capsule_shape";}
        static const char* getFieldTypeName_m_capsule_shape(){ return "Capsule";}
        static void set_m_capsule_shape(void* instance, void* field_value){ static_cast<PhysicsControllerConfig*>(instance)->m_capsule_shape = *static_cast<Capsule*>(field_value);}
        static void* get_m_capsule_shape(void* instance){ return static_cast<void*>(&(static_cast<PhysicsControllerConfig*>(instance)->m_capsule_shape));}
        static bool isArray_m_capsule_shape(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_PhysicsControllerConfig(){
    FieldFunctionTuple* field_function_tuple_m_capsule_shape=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::set_m_capsule_shape,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::get_m_capsule_shape,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::getClassName,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::getFieldName_m_capsule_shape,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::getFieldTypeName_m_capsule_shape,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::isArray_m_capsule_shape);
    REGISTER_FIELD_TO_MAP("PhysicsControllerConfig", field_function_tuple_m_capsule_shape);

    

    
    ClassFunctionTuple* class_function_tuple_PhysicsControllerConfig=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::getPhysicsControllerConfigBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypePhysicsControllerConfigOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("PhysicsControllerConfig", class_function_tuple_PhysicsControllerConfig);
    }namespace TypeFieldReflectionOparator{
    class TypeMotorComponentResOperator{
    public:
        static const char* getClassName(){ return "MotorComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            MotorComponentRes* ret_instance= new MotorComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(MotorComponentRes*)instance);
        }
        // base class
        static int getMotorComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_move_speed(){ return "m_move_speed";}
        static const char* getFieldTypeName_m_move_speed(){ return "float";}
        static void set_m_move_speed(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_move_speed = *static_cast<float*>(field_value);}
        static void* get_m_move_speed(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_move_speed));}
        static bool isArray_m_move_speed(){ return false; }
        static const char* getFieldName_m_jump_height(){ return "m_jump_height";}
        static const char* getFieldTypeName_m_jump_height(){ return "float";}
        static void set_m_jump_height(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_jump_height = *static_cast<float*>(field_value);}
        static void* get_m_jump_height(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_jump_height));}
        static bool isArray_m_jump_height(){ return false; }
        static const char* getFieldName_m_max_move_speed_ratio(){ return "m_max_move_speed_ratio";}
        static const char* getFieldTypeName_m_max_move_speed_ratio(){ return "float";}
        static void set_m_max_move_speed_ratio(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_max_move_speed_ratio = *static_cast<float*>(field_value);}
        static void* get_m_max_move_speed_ratio(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_max_move_speed_ratio));}
        static bool isArray_m_max_move_speed_ratio(){ return false; }
        static const char* getFieldName_m_max_sprint_speed_ratio(){ return "m_max_sprint_speed_ratio";}
        static const char* getFieldTypeName_m_max_sprint_speed_ratio(){ return "float";}
        static void set_m_max_sprint_speed_ratio(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_max_sprint_speed_ratio = *static_cast<float*>(field_value);}
        static void* get_m_max_sprint_speed_ratio(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_max_sprint_speed_ratio));}
        static bool isArray_m_max_sprint_speed_ratio(){ return false; }
        static const char* getFieldName_m_move_acceleration(){ return "m_move_acceleration";}
        static const char* getFieldTypeName_m_move_acceleration(){ return "float";}
        static void set_m_move_acceleration(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_move_acceleration = *static_cast<float*>(field_value);}
        static void* get_m_move_acceleration(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_move_acceleration));}
        static bool isArray_m_move_acceleration(){ return false; }
        static const char* getFieldName_m_sprint_acceleration(){ return "m_sprint_acceleration";}
        static const char* getFieldTypeName_m_sprint_acceleration(){ return "float";}
        static void set_m_sprint_acceleration(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_sprint_acceleration = *static_cast<float*>(field_value);}
        static void* get_m_sprint_acceleration(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_sprint_acceleration));}
        static bool isArray_m_sprint_acceleration(){ return false; }
        static const char* getFieldName_m_controller_config(){ return "m_controller_config";}
        static const char* getFieldTypeName_m_controller_config(){ return "Reflection::ReflectionPtr<ControllerConfig>";}
        static void set_m_controller_config(void* instance, void* field_value){ static_cast<MotorComponentRes*>(instance)->m_controller_config = *static_cast<Reflection::ReflectionPtr<ControllerConfig>*>(field_value);}
        static void* get_m_controller_config(void* instance){ return static_cast<void*>(&(static_cast<MotorComponentRes*>(instance)->m_controller_config));}
        static bool isArray_m_controller_config(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_MotorComponentRes(){
    FieldFunctionTuple* field_function_tuple_m_move_speed=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_move_speed,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_move_speed,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_move_speed,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_move_speed,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_move_speed);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_move_speed);
    FieldFunctionTuple* field_function_tuple_m_jump_height=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_jump_height,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_jump_height,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_jump_height,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_jump_height,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_jump_height);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_jump_height);
    FieldFunctionTuple* field_function_tuple_m_max_move_speed_ratio=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_max_move_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_max_move_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_max_move_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_max_move_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_max_move_speed_ratio);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_max_move_speed_ratio);
    FieldFunctionTuple* field_function_tuple_m_max_sprint_speed_ratio=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_max_sprint_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_max_sprint_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_max_sprint_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_max_sprint_speed_ratio,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_max_sprint_speed_ratio);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_max_sprint_speed_ratio);
    FieldFunctionTuple* field_function_tuple_m_move_acceleration=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_move_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_move_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_move_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_move_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_move_acceleration);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_move_acceleration);
    FieldFunctionTuple* field_function_tuple_m_sprint_acceleration=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_sprint_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_sprint_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_sprint_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_sprint_acceleration,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_sprint_acceleration);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_sprint_acceleration);
    FieldFunctionTuple* field_function_tuple_m_controller_config=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::set_m_controller_config,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::get_m_controller_config,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldName_m_controller_config,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getFieldTypeName_m_controller_config,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::isArray_m_controller_config);
    REGISTER_FIELD_TO_MAP("MotorComponentRes", field_function_tuple_m_controller_config);

    

    
    ClassFunctionTuple* class_function_tuple_MotorComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::getMotorComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeMotorComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("MotorComponentRes", class_function_tuple_MotorComponentRes);
    }
    namespace TypeWrappersRegister{
    void Motor()
    {
    TypeWrapperRegister_ControllerConfig();
    TypeWrapperRegister_PhysicsControllerConfig();
    TypeWrapperRegister_MotorComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

