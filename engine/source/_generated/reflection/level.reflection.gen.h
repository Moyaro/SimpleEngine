#pragma once
#include "runtime\resource\res_type\common\level.h"

namespace SimpleEngine{
    class LevelRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeLevelResOperator{
    public:
        static const char* getClassName(){ return "LevelRes";}
        static void* constructorWithJson(const Json& json_context){
            LevelRes* ret_instance= new LevelRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(LevelRes*)instance);
        }
        // base class
        static int getLevelResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_gravity(){ return "m_gravity";}
        static const char* getFieldTypeName_m_gravity(){ return "Vector3";}
        static void set_m_gravity(void* instance, void* field_value){ static_cast<LevelRes*>(instance)->m_gravity = *static_cast<Vector3*>(field_value);}
        static void* get_m_gravity(void* instance){ return static_cast<void*>(&(static_cast<LevelRes*>(instance)->m_gravity));}
        static bool isArray_m_gravity(){ return false; }
        static const char* getFieldName_m_camera_name(){ return "m_camera_name";}
        static const char* getFieldTypeName_m_camera_name(){ return "std::string";}
        static void set_m_camera_name(void* instance, void* field_value){ static_cast<LevelRes*>(instance)->m_camera_name = *static_cast<std::string*>(field_value);}
        static void* get_m_camera_name(void* instance){ return static_cast<void*>(&(static_cast<LevelRes*>(instance)->m_camera_name));}
        static bool isArray_m_camera_name(){ return false; }
        static const char* getFieldName_m_objects(){ return "m_objects";}
        static const char* getFieldTypeName_m_objects(){ return "std::vector<ObjectInstanceRes>";}
        static void set_m_objects(void* instance, void* field_value){ static_cast<LevelRes*>(instance)->m_objects = *static_cast<std::vector<ObjectInstanceRes>*>(field_value);}
        static void* get_m_objects(void* instance){ return static_cast<void*>(&(static_cast<LevelRes*>(instance)->m_objects));}
        static bool isArray_m_objects(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLObjectInstanceResROperatorMACRO
#define ArraystdSSvectorLObjectInstanceResROperatorMACRO
    class ArraystdSSvectorLObjectInstanceResROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<ObjectInstanceRes>";}
            static const char* getElementTypeName(){ return "ObjectInstanceRes";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<ObjectInstanceRes>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<ObjectInstanceRes>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<ObjectInstanceRes>*>(instance))[index] = *static_cast<ObjectInstanceRes*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLObjectInstanceResROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_LevelRes(){
    FieldFunctionTuple* field_function_tuple_m_gravity=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeLevelResOperator::set_m_gravity,
    &TypeFieldReflectionOparator::TypeLevelResOperator::get_m_gravity,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldName_m_gravity,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldTypeName_m_gravity,
    &TypeFieldReflectionOparator::TypeLevelResOperator::isArray_m_gravity);
    REGISTER_FIELD_TO_MAP("LevelRes", field_function_tuple_m_gravity);
    FieldFunctionTuple* field_function_tuple_m_camera_name=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeLevelResOperator::set_m_camera_name,
    &TypeFieldReflectionOparator::TypeLevelResOperator::get_m_camera_name,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldName_m_camera_name,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldTypeName_m_camera_name,
    &TypeFieldReflectionOparator::TypeLevelResOperator::isArray_m_camera_name);
    REGISTER_FIELD_TO_MAP("LevelRes", field_function_tuple_m_camera_name);
    FieldFunctionTuple* field_function_tuple_m_objects=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeLevelResOperator::set_m_objects,
    &TypeFieldReflectionOparator::TypeLevelResOperator::get_m_objects,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldName_m_objects,
    &TypeFieldReflectionOparator::TypeLevelResOperator::getFieldTypeName_m_objects,
    &TypeFieldReflectionOparator::TypeLevelResOperator::isArray_m_objects);
    REGISTER_FIELD_TO_MAP("LevelRes", field_function_tuple_m_objects);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLObjectInstanceResR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<ObjectInstanceRes>", array_tuple_stdSSvectorLObjectInstanceResR);
    ClassFunctionTuple* class_function_tuple_LevelRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeLevelResOperator::getLevelResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeLevelResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeLevelResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("LevelRes", class_function_tuple_LevelRes);
    }
    namespace TypeWrappersRegister{
    void Level()
    {
    TypeWrapperRegister_LevelRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

