#pragma once
#include "runtime\resource\res_type\components\mesh.h"

namespace SimpleEngine{
    class SubMeshRes;
    class MeshComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeSubMeshResOperator{
    public:
        static const char* getClassName(){ return "SubMeshRes";}
        static void* constructorWithJson(const Json& json_context){
            SubMeshRes* ret_instance= new SubMeshRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(SubMeshRes*)instance);
        }
        // base class
        static int getSubMeshResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_obj_file_ref(){ return "m_obj_file_ref";}
        static const char* getFieldTypeName_m_obj_file_ref(){ return "std::string";}
        static void set_m_obj_file_ref(void* instance, void* field_value){ static_cast<SubMeshRes*>(instance)->m_obj_file_ref = *static_cast<std::string*>(field_value);}
        static void* get_m_obj_file_ref(void* instance){ return static_cast<void*>(&(static_cast<SubMeshRes*>(instance)->m_obj_file_ref));}
        static bool isArray_m_obj_file_ref(){ return false; }
        static const char* getFieldName_m_transform(){ return "m_transform";}
        static const char* getFieldTypeName_m_transform(){ return "Transform";}
        static void set_m_transform(void* instance, void* field_value){ static_cast<SubMeshRes*>(instance)->m_transform = *static_cast<Transform*>(field_value);}
        static void* get_m_transform(void* instance){ return static_cast<void*>(&(static_cast<SubMeshRes*>(instance)->m_transform));}
        static bool isArray_m_transform(){ return false; }
        static const char* getFieldName_m_material(){ return "m_material";}
        static const char* getFieldTypeName_m_material(){ return "std::string";}
        static void set_m_material(void* instance, void* field_value){ static_cast<SubMeshRes*>(instance)->m_material = *static_cast<std::string*>(field_value);}
        static void* get_m_material(void* instance){ return static_cast<void*>(&(static_cast<SubMeshRes*>(instance)->m_material));}
        static bool isArray_m_material(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_SubMeshRes(){
    FieldFunctionTuple* field_function_tuple_m_obj_file_ref=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::set_m_obj_file_ref,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::get_m_obj_file_ref,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldName_m_obj_file_ref,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldTypeName_m_obj_file_ref,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::isArray_m_obj_file_ref);
    REGISTER_FIELD_TO_MAP("SubMeshRes", field_function_tuple_m_obj_file_ref);
    FieldFunctionTuple* field_function_tuple_m_transform=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::set_m_transform,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::get_m_transform,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldName_m_transform,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldTypeName_m_transform,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::isArray_m_transform);
    REGISTER_FIELD_TO_MAP("SubMeshRes", field_function_tuple_m_transform);
    FieldFunctionTuple* field_function_tuple_m_material=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::set_m_material,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::get_m_material,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldName_m_material,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getFieldTypeName_m_material,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::isArray_m_material);
    REGISTER_FIELD_TO_MAP("SubMeshRes", field_function_tuple_m_material);

    

    
    ClassFunctionTuple* class_function_tuple_SubMeshRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::getSubMeshResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSubMeshResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("SubMeshRes", class_function_tuple_SubMeshRes);
    }namespace TypeFieldReflectionOparator{
    class TypeMeshComponentResOperator{
    public:
        static const char* getClassName(){ return "MeshComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            MeshComponentRes* ret_instance= new MeshComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(MeshComponentRes*)instance);
        }
        // base class
        static int getMeshComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_sub_meshes(){ return "m_sub_meshes";}
        static const char* getFieldTypeName_m_sub_meshes(){ return "std::vector<SubMeshRes>";}
        static void set_m_sub_meshes(void* instance, void* field_value){ static_cast<MeshComponentRes*>(instance)->m_sub_meshes = *static_cast<std::vector<SubMeshRes>*>(field_value);}
        static void* get_m_sub_meshes(void* instance){ return static_cast<void*>(&(static_cast<MeshComponentRes*>(instance)->m_sub_meshes));}
        static bool isArray_m_sub_meshes(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLSubMeshResROperatorMACRO
#define ArraystdSSvectorLSubMeshResROperatorMACRO
    class ArraystdSSvectorLSubMeshResROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<SubMeshRes>";}
            static const char* getElementTypeName(){ return "SubMeshRes";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<SubMeshRes>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<SubMeshRes>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<SubMeshRes>*>(instance))[index] = *static_cast<SubMeshRes*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLSubMeshResROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_MeshComponentRes(){
    FieldFunctionTuple* field_function_tuple_m_sub_meshes=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::set_m_sub_meshes,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::get_m_sub_meshes,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::getFieldName_m_sub_meshes,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::getFieldTypeName_m_sub_meshes,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::isArray_m_sub_meshes);
    REGISTER_FIELD_TO_MAP("MeshComponentRes", field_function_tuple_m_sub_meshes);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLSubMeshResR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLSubMeshResROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLSubMeshResROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLSubMeshResROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLSubMeshResROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLSubMeshResROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<SubMeshRes>", array_tuple_stdSSvectorLSubMeshResR);
    ClassFunctionTuple* class_function_tuple_MeshComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::getMeshComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeMeshComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("MeshComponentRes", class_function_tuple_MeshComponentRes);
    }
    namespace TypeWrappersRegister{
    void Mesh()
    {
    TypeWrapperRegister_SubMeshRes();
    TypeWrapperRegister_MeshComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

