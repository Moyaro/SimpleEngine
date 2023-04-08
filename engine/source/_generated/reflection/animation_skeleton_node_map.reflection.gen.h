#pragma once
#include "runtime\resource\res_type\data\animation_skeleton_node_map.h"

namespace SimpleEngine{
    class AnimSkelMap;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAnimSkelMapOperator{
    public:
        static const char* getClassName(){ return "AnimSkelMap";}
        static void* constructorWithJson(const Json& json_context){
            AnimSkelMap* ret_instance= new AnimSkelMap;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimSkelMap*)instance);
        }
        // base class
        static int getAnimSkelMapBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_convert(){ return "convert";}
        static const char* getFieldTypeName_convert(){ return "std::vector<int>";}
        static void set_convert(void* instance, void* field_value){ static_cast<AnimSkelMap*>(instance)->convert = *static_cast<std::vector<int>*>(field_value);}
        static void* get_convert(void* instance){ return static_cast<void*>(&(static_cast<AnimSkelMap*>(instance)->convert));}
        static bool isArray_convert(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLintROperatorMACRO
#define ArraystdSSvectorLintROperatorMACRO
    class ArraystdSSvectorLintROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<int>";}
            static const char* getElementTypeName(){ return "int";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<int>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<int>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<int>*>(instance))[index] = *static_cast<int*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLintROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_AnimSkelMap(){
    FieldFunctionTuple* field_function_tuple_convert=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::set_convert,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::get_convert,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::getFieldName_convert,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::getFieldTypeName_convert,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::isArray_convert);
    REGISTER_FIELD_TO_MAP("AnimSkelMap", field_function_tuple_convert);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLintR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<int>", array_tuple_stdSSvectorLintR);
    ClassFunctionTuple* class_function_tuple_AnimSkelMap=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::getAnimSkelMapBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimSkelMapOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimSkelMap", class_function_tuple_AnimSkelMap);
    }
    namespace TypeWrappersRegister{
    void AnimationSkeletonNodeMap()
    {
    TypeWrapperRegister_AnimSkelMap();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

