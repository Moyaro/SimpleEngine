#pragma once
#include "runtime\resource\res_type\data\skeleton_mask.h"

namespace SimpleEngine{
    class BoneBlendMask;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeBoneBlendMaskOperator{
    public:
        static const char* getClassName(){ return "BoneBlendMask";}
        static void* constructorWithJson(const Json& json_context){
            BoneBlendMask* ret_instance= new BoneBlendMask;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(BoneBlendMask*)instance);
        }
        // base class
        static int getBoneBlendMaskBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_skeleton_file_path(){ return "skeleton_file_path";}
        static const char* getFieldTypeName_skeleton_file_path(){ return "std::string";}
        static void set_skeleton_file_path(void* instance, void* field_value){ static_cast<BoneBlendMask*>(instance)->skeleton_file_path = *static_cast<std::string*>(field_value);}
        static void* get_skeleton_file_path(void* instance){ return static_cast<void*>(&(static_cast<BoneBlendMask*>(instance)->skeleton_file_path));}
        static bool isArray_skeleton_file_path(){ return false; }
        static const char* getFieldName_enabled(){ return "enabled";}
        static const char* getFieldTypeName_enabled(){ return "std::vector<int>";}
        static void set_enabled(void* instance, void* field_value){ static_cast<BoneBlendMask*>(instance)->enabled = *static_cast<std::vector<int>*>(field_value);}
        static void* get_enabled(void* instance){ return static_cast<void*>(&(static_cast<BoneBlendMask*>(instance)->enabled));}
        static bool isArray_enabled(){ return true; }

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

    void TypeWrapperRegister_BoneBlendMask(){
    FieldFunctionTuple* field_function_tuple_skeleton_file_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::set_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::get_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getFieldName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getFieldTypeName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::isArray_skeleton_file_path);
    REGISTER_FIELD_TO_MAP("BoneBlendMask", field_function_tuple_skeleton_file_path);
    FieldFunctionTuple* field_function_tuple_enabled=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::set_enabled,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::get_enabled,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getFieldName_enabled,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getFieldTypeName_enabled,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::isArray_enabled);
    REGISTER_FIELD_TO_MAP("BoneBlendMask", field_function_tuple_enabled);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLintR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<int>", array_tuple_stdSSvectorLintR);
    ClassFunctionTuple* class_function_tuple_BoneBlendMask=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::getBoneBlendMaskBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeBoneBlendMaskOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("BoneBlendMask", class_function_tuple_BoneBlendMask);
    }
    namespace TypeWrappersRegister{
    void SkeletonMask()
    {
    TypeWrapperRegister_BoneBlendMask();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

