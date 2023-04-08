#pragma once
#include "runtime\resource\res_type\data\skeleton_data.h"

namespace SimpleEngine{
    class RawBone;
    class SkeletonData;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeRawBoneOperator{
    public:
        static const char* getClassName(){ return "RawBone";}
        static void* constructorWithJson(const Json& json_context){
            RawBone* ret_instance= new RawBone;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(RawBone*)instance);
        }
        // base class
        static int getRawBoneBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_name(){ return "name";}
        static const char* getFieldTypeName_name(){ return "std::string";}
        static void set_name(void* instance, void* field_value){ static_cast<RawBone*>(instance)->name = *static_cast<std::string*>(field_value);}
        static void* get_name(void* instance){ return static_cast<void*>(&(static_cast<RawBone*>(instance)->name));}
        static bool isArray_name(){ return false; }
        static const char* getFieldName_index(){ return "index";}
        static const char* getFieldTypeName_index(){ return "int";}
        static void set_index(void* instance, void* field_value){ static_cast<RawBone*>(instance)->index = *static_cast<int*>(field_value);}
        static void* get_index(void* instance){ return static_cast<void*>(&(static_cast<RawBone*>(instance)->index));}
        static bool isArray_index(){ return false; }
        static const char* getFieldName_binding_pose(){ return "binding_pose";}
        static const char* getFieldTypeName_binding_pose(){ return "Transform";}
        static void set_binding_pose(void* instance, void* field_value){ static_cast<RawBone*>(instance)->binding_pose = *static_cast<Transform*>(field_value);}
        static void* get_binding_pose(void* instance){ return static_cast<void*>(&(static_cast<RawBone*>(instance)->binding_pose));}
        static bool isArray_binding_pose(){ return false; }
        static const char* getFieldName_tpose_matrix(){ return "tpose_matrix";}
        static const char* getFieldTypeName_tpose_matrix(){ return "Matrix4x4_";}
        static void set_tpose_matrix(void* instance, void* field_value){ static_cast<RawBone*>(instance)->tpose_matrix = *static_cast<Matrix4x4_*>(field_value);}
        static void* get_tpose_matrix(void* instance){ return static_cast<void*>(&(static_cast<RawBone*>(instance)->tpose_matrix));}
        static bool isArray_tpose_matrix(){ return false; }
        static const char* getFieldName_parent_index(){ return "parent_index";}
        static const char* getFieldTypeName_parent_index(){ return "int";}
        static void set_parent_index(void* instance, void* field_value){ static_cast<RawBone*>(instance)->parent_index = *static_cast<int*>(field_value);}
        static void* get_parent_index(void* instance){ return static_cast<void*>(&(static_cast<RawBone*>(instance)->parent_index));}
        static bool isArray_parent_index(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_RawBone(){
    FieldFunctionTuple* field_function_tuple_name=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::set_name,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::get_name,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldName_name,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldTypeName_name,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::isArray_name);
    REGISTER_FIELD_TO_MAP("RawBone", field_function_tuple_name);
    FieldFunctionTuple* field_function_tuple_index=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::set_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::get_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldName_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldTypeName_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::isArray_index);
    REGISTER_FIELD_TO_MAP("RawBone", field_function_tuple_index);
    FieldFunctionTuple* field_function_tuple_binding_pose=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::set_binding_pose,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::get_binding_pose,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldName_binding_pose,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldTypeName_binding_pose,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::isArray_binding_pose);
    REGISTER_FIELD_TO_MAP("RawBone", field_function_tuple_binding_pose);
    FieldFunctionTuple* field_function_tuple_tpose_matrix=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::set_tpose_matrix,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::get_tpose_matrix,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldName_tpose_matrix,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldTypeName_tpose_matrix,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::isArray_tpose_matrix);
    REGISTER_FIELD_TO_MAP("RawBone", field_function_tuple_tpose_matrix);
    FieldFunctionTuple* field_function_tuple_parent_index=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::set_parent_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::get_parent_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldName_parent_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getFieldTypeName_parent_index,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::isArray_parent_index);
    REGISTER_FIELD_TO_MAP("RawBone", field_function_tuple_parent_index);

    

    
    ClassFunctionTuple* class_function_tuple_RawBone=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeRawBoneOperator::getRawBoneBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeRawBoneOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("RawBone", class_function_tuple_RawBone);
    }namespace TypeFieldReflectionOparator{
    class TypeSkeletonDataOperator{
    public:
        static const char* getClassName(){ return "SkeletonData";}
        static void* constructorWithJson(const Json& json_context){
            SkeletonData* ret_instance= new SkeletonData;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(SkeletonData*)instance);
        }
        // base class
        static int getSkeletonDataBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_bones_map(){ return "bones_map";}
        static const char* getFieldTypeName_bones_map(){ return "std::vector<RawBone>";}
        static void set_bones_map(void* instance, void* field_value){ static_cast<SkeletonData*>(instance)->bones_map = *static_cast<std::vector<RawBone>*>(field_value);}
        static void* get_bones_map(void* instance){ return static_cast<void*>(&(static_cast<SkeletonData*>(instance)->bones_map));}
        static bool isArray_bones_map(){ return true; }
        static const char* getFieldName_is_flat(){ return "is_flat";}
        static const char* getFieldTypeName_is_flat(){ return "bool";}
        static void set_is_flat(void* instance, void* field_value){ static_cast<SkeletonData*>(instance)->is_flat = *static_cast<bool*>(field_value);}
        static void* get_is_flat(void* instance){ return static_cast<void*>(&(static_cast<SkeletonData*>(instance)->is_flat));}
        static bool isArray_is_flat(){ return false; }
        static const char* getFieldName_root_index(){ return "root_index";}
        static const char* getFieldTypeName_root_index(){ return "int";}
        static void set_root_index(void* instance, void* field_value){ static_cast<SkeletonData*>(instance)->root_index = *static_cast<int*>(field_value);}
        static void* get_root_index(void* instance){ return static_cast<void*>(&(static_cast<SkeletonData*>(instance)->root_index));}
        static bool isArray_root_index(){ return false; }
        static const char* getFieldName_in_topological_order(){ return "in_topological_order";}
        static const char* getFieldTypeName_in_topological_order(){ return "bool";}
        static void set_in_topological_order(void* instance, void* field_value){ static_cast<SkeletonData*>(instance)->in_topological_order = *static_cast<bool*>(field_value);}
        static void* get_in_topological_order(void* instance){ return static_cast<void*>(&(static_cast<SkeletonData*>(instance)->in_topological_order));}
        static bool isArray_in_topological_order(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLRawBoneROperatorMACRO
#define ArraystdSSvectorLRawBoneROperatorMACRO
    class ArraystdSSvectorLRawBoneROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<RawBone>";}
            static const char* getElementTypeName(){ return "RawBone";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<RawBone>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<RawBone>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<RawBone>*>(instance))[index] = *static_cast<RawBone*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLRawBoneROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_SkeletonData(){
    FieldFunctionTuple* field_function_tuple_bones_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::set_bones_map,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::get_bones_map,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldName_bones_map,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldTypeName_bones_map,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::isArray_bones_map);
    REGISTER_FIELD_TO_MAP("SkeletonData", field_function_tuple_bones_map);
    FieldFunctionTuple* field_function_tuple_is_flat=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::set_is_flat,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::get_is_flat,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldName_is_flat,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldTypeName_is_flat,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::isArray_is_flat);
    REGISTER_FIELD_TO_MAP("SkeletonData", field_function_tuple_is_flat);
    FieldFunctionTuple* field_function_tuple_root_index=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::set_root_index,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::get_root_index,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldName_root_index,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldTypeName_root_index,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::isArray_root_index);
    REGISTER_FIELD_TO_MAP("SkeletonData", field_function_tuple_root_index);
    FieldFunctionTuple* field_function_tuple_in_topological_order=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::set_in_topological_order,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::get_in_topological_order,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldName_in_topological_order,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getFieldTypeName_in_topological_order,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::isArray_in_topological_order);
    REGISTER_FIELD_TO_MAP("SkeletonData", field_function_tuple_in_topological_order);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLRawBoneR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLRawBoneROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLRawBoneROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLRawBoneROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLRawBoneROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLRawBoneROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<RawBone>", array_tuple_stdSSvectorLRawBoneR);
    ClassFunctionTuple* class_function_tuple_SkeletonData=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::getSkeletonDataBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSkeletonDataOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("SkeletonData", class_function_tuple_SkeletonData);
    }
    namespace TypeWrappersRegister{
    void SkeletonData()
    {
    TypeWrapperRegister_RawBone();
    TypeWrapperRegister_SkeletonData();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

