#pragma once
#include "runtime\resource\res_type\global\global_particle.h"

namespace SimpleEngine{
    class GlobalParticleRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeGlobalParticleResOperator{
    public:
        static const char* getClassName(){ return "GlobalParticleRes";}
        static void* constructorWithJson(const Json& json_context){
            GlobalParticleRes* ret_instance= new GlobalParticleRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(GlobalParticleRes*)instance);
        }
        // base class
        static int getGlobalParticleResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_emit_gap(){ return "m_emit_gap";}
        static const char* getFieldTypeName_m_emit_gap(){ return "int";}
        static void set_m_emit_gap(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_emit_gap = *static_cast<int*>(field_value);}
        static void* get_m_emit_gap(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_emit_gap));}
        static bool isArray_m_emit_gap(){ return false; }
        static const char* getFieldName_m_emit_count(){ return "m_emit_count";}
        static const char* getFieldTypeName_m_emit_count(){ return "int";}
        static void set_m_emit_count(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_emit_count = *static_cast<int*>(field_value);}
        static void* get_m_emit_count(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_emit_count));}
        static bool isArray_m_emit_count(){ return false; }
        static const char* getFieldName_m_time_step(){ return "m_time_step";}
        static const char* getFieldTypeName_m_time_step(){ return "float";}
        static void set_m_time_step(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_time_step = *static_cast<float*>(field_value);}
        static void* get_m_time_step(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_time_step));}
        static bool isArray_m_time_step(){ return false; }
        static const char* getFieldName_m_max_life(){ return "m_max_life";}
        static const char* getFieldTypeName_m_max_life(){ return "float";}
        static void set_m_max_life(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_max_life = *static_cast<float*>(field_value);}
        static void* get_m_max_life(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_max_life));}
        static bool isArray_m_max_life(){ return false; }
        static const char* getFieldName_m_gravity(){ return "m_gravity";}
        static const char* getFieldTypeName_m_gravity(){ return "Vector3";}
        static void set_m_gravity(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_gravity = *static_cast<Vector3*>(field_value);}
        static void* get_m_gravity(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_gravity));}
        static bool isArray_m_gravity(){ return false; }
        static const char* getFieldName_m_particle_billboard_texture_path(){ return "m_particle_billboard_texture_path";}
        static const char* getFieldTypeName_m_particle_billboard_texture_path(){ return "std::string";}
        static void set_m_particle_billboard_texture_path(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_particle_billboard_texture_path = *static_cast<std::string*>(field_value);}
        static void* get_m_particle_billboard_texture_path(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_particle_billboard_texture_path));}
        static bool isArray_m_particle_billboard_texture_path(){ return false; }
        static const char* getFieldName_m_piccolo_logo_texture_path(){ return "m_piccolo_logo_texture_path";}
        static const char* getFieldTypeName_m_piccolo_logo_texture_path(){ return "std::string";}
        static void set_m_piccolo_logo_texture_path(void* instance, void* field_value){ static_cast<GlobalParticleRes*>(instance)->m_piccolo_logo_texture_path = *static_cast<std::string*>(field_value);}
        static void* get_m_piccolo_logo_texture_path(void* instance){ return static_cast<void*>(&(static_cast<GlobalParticleRes*>(instance)->m_piccolo_logo_texture_path));}
        static bool isArray_m_piccolo_logo_texture_path(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GlobalParticleRes(){
    FieldFunctionTuple* field_function_tuple_m_emit_gap=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_emit_gap,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_emit_gap,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_emit_gap,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_emit_gap,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_emit_gap);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_emit_gap);
    FieldFunctionTuple* field_function_tuple_m_emit_count=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_emit_count,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_emit_count,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_emit_count,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_emit_count,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_emit_count);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_emit_count);
    FieldFunctionTuple* field_function_tuple_m_time_step=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_time_step,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_time_step,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_time_step,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_time_step,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_time_step);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_time_step);
    FieldFunctionTuple* field_function_tuple_m_max_life=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_max_life,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_max_life,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_max_life,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_max_life,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_max_life);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_max_life);
    FieldFunctionTuple* field_function_tuple_m_gravity=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_gravity,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_gravity,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_gravity,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_gravity,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_gravity);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_gravity);
    FieldFunctionTuple* field_function_tuple_m_particle_billboard_texture_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_particle_billboard_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_particle_billboard_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_particle_billboard_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_particle_billboard_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_particle_billboard_texture_path);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_particle_billboard_texture_path);
    FieldFunctionTuple* field_function_tuple_m_piccolo_logo_texture_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::set_m_piccolo_logo_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::get_m_piccolo_logo_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldName_m_piccolo_logo_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getFieldTypeName_m_piccolo_logo_texture_path,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::isArray_m_piccolo_logo_texture_path);
    REGISTER_FIELD_TO_MAP("GlobalParticleRes", field_function_tuple_m_piccolo_logo_texture_path);

    

    
    ClassFunctionTuple* class_function_tuple_GlobalParticleRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::getGlobalParticleResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGlobalParticleResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("GlobalParticleRes", class_function_tuple_GlobalParticleRes);
    }
    namespace TypeWrappersRegister{
    void GlobalParticle()
    {
    TypeWrapperRegister_GlobalParticleRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

