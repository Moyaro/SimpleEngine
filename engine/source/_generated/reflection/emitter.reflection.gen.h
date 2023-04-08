#pragma once
#include "runtime\resource\res_type\components\emitter.h"

namespace SimpleEngine{
    class ParticleComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeParticleComponentResOperator{
    public:
        static const char* getClassName(){ return "ParticleComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            ParticleComponentRes* ret_instance= new ParticleComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(ParticleComponentRes*)instance);
        }
        // base class
        static int getParticleComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_local_translation(){ return "m_local_translation";}
        static const char* getFieldTypeName_m_local_translation(){ return "Vector3";}
        static void set_m_local_translation(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_local_translation = *static_cast<Vector3*>(field_value);}
        static void* get_m_local_translation(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_local_translation));}
        static bool isArray_m_local_translation(){ return false; }
        static const char* getFieldName_m_local_rotation(){ return "m_local_rotation";}
        static const char* getFieldTypeName_m_local_rotation(){ return "Quaternion";}
        static void set_m_local_rotation(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_local_rotation = *static_cast<Quaternion*>(field_value);}
        static void* get_m_local_rotation(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_local_rotation));}
        static bool isArray_m_local_rotation(){ return false; }
        static const char* getFieldName_m_velocity(){ return "m_velocity";}
        static const char* getFieldTypeName_m_velocity(){ return "Vector4";}
        static void set_m_velocity(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_velocity = *static_cast<Vector4*>(field_value);}
        static void* get_m_velocity(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_velocity));}
        static bool isArray_m_velocity(){ return false; }
        static const char* getFieldName_m_acceleration(){ return "m_acceleration";}
        static const char* getFieldTypeName_m_acceleration(){ return "Vector4";}
        static void set_m_acceleration(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_acceleration = *static_cast<Vector4*>(field_value);}
        static void* get_m_acceleration(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_acceleration));}
        static bool isArray_m_acceleration(){ return false; }
        static const char* getFieldName_m_size(){ return "m_size";}
        static const char* getFieldTypeName_m_size(){ return "Vector3";}
        static void set_m_size(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_size = *static_cast<Vector3*>(field_value);}
        static void* get_m_size(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_size));}
        static bool isArray_m_size(){ return false; }
        static const char* getFieldName_m_emitter_type(){ return "m_emitter_type";}
        static const char* getFieldTypeName_m_emitter_type(){ return "int";}
        static void set_m_emitter_type(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_emitter_type = *static_cast<int*>(field_value);}
        static void* get_m_emitter_type(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_emitter_type));}
        static bool isArray_m_emitter_type(){ return false; }
        static const char* getFieldName_m_life(){ return "m_life";}
        static const char* getFieldTypeName_m_life(){ return "Vector2";}
        static void set_m_life(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_life = *static_cast<Vector2*>(field_value);}
        static void* get_m_life(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_life));}
        static bool isArray_m_life(){ return false; }
        static const char* getFieldName_m_color(){ return "m_color";}
        static const char* getFieldTypeName_m_color(){ return "Vector4";}
        static void set_m_color(void* instance, void* field_value){ static_cast<ParticleComponentRes*>(instance)->m_color = *static_cast<Vector4*>(field_value);}
        static void* get_m_color(void* instance){ return static_cast<void*>(&(static_cast<ParticleComponentRes*>(instance)->m_color));}
        static bool isArray_m_color(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_ParticleComponentRes(){
    FieldFunctionTuple* field_function_tuple_m_local_translation=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_local_translation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_local_translation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_local_translation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_local_translation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_local_translation);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_local_translation);
    FieldFunctionTuple* field_function_tuple_m_local_rotation=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_local_rotation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_local_rotation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_local_rotation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_local_rotation,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_local_rotation);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_local_rotation);
    FieldFunctionTuple* field_function_tuple_m_velocity=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_velocity,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_velocity,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_velocity,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_velocity,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_velocity);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_velocity);
    FieldFunctionTuple* field_function_tuple_m_acceleration=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_acceleration,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_acceleration,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_acceleration,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_acceleration,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_acceleration);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_acceleration);
    FieldFunctionTuple* field_function_tuple_m_size=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_size,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_size,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_size,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_size,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_size);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_size);
    FieldFunctionTuple* field_function_tuple_m_emitter_type=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_emitter_type,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_emitter_type,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_emitter_type,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_emitter_type,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_emitter_type);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_emitter_type);
    FieldFunctionTuple* field_function_tuple_m_life=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_life,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_life,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_life,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_life,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_life);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_life);
    FieldFunctionTuple* field_function_tuple_m_color=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::set_m_color,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::get_m_color,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldName_m_color,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getFieldTypeName_m_color,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::isArray_m_color);
    REGISTER_FIELD_TO_MAP("ParticleComponentRes", field_function_tuple_m_color);

    

    
    ClassFunctionTuple* class_function_tuple_ParticleComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::getParticleComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeParticleComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("ParticleComponentRes", class_function_tuple_ParticleComponentRes);
    }
    namespace TypeWrappersRegister{
    void Emitter()
    {
    TypeWrapperRegister_ParticleComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

