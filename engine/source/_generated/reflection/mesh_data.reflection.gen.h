#pragma once
#include "runtime\resource\res_type\data\mesh_data.h"

namespace SimpleEngine{
    class Vertex;
    class SkeletonBinding;
    class MeshData;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVertexOperator{
    public:
        static const char* getClassName(){ return "Vertex";}
        static void* constructorWithJson(const Json& json_context){
            Vertex* ret_instance= new Vertex;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Vertex*)instance);
        }
        // base class
        static int getVertexBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_px(){ return "px";}
        static const char* getFieldTypeName_px(){ return "float";}
        static void set_px(void* instance, void* field_value){ static_cast<Vertex*>(instance)->px = *static_cast<float*>(field_value);}
        static void* get_px(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->px));}
        static bool isArray_px(){ return false; }
        static const char* getFieldName_py(){ return "py";}
        static const char* getFieldTypeName_py(){ return "float";}
        static void set_py(void* instance, void* field_value){ static_cast<Vertex*>(instance)->py = *static_cast<float*>(field_value);}
        static void* get_py(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->py));}
        static bool isArray_py(){ return false; }
        static const char* getFieldName_pz(){ return "pz";}
        static const char* getFieldTypeName_pz(){ return "float";}
        static void set_pz(void* instance, void* field_value){ static_cast<Vertex*>(instance)->pz = *static_cast<float*>(field_value);}
        static void* get_pz(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->pz));}
        static bool isArray_pz(){ return false; }
        static const char* getFieldName_nx(){ return "nx";}
        static const char* getFieldTypeName_nx(){ return "float";}
        static void set_nx(void* instance, void* field_value){ static_cast<Vertex*>(instance)->nx = *static_cast<float*>(field_value);}
        static void* get_nx(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->nx));}
        static bool isArray_nx(){ return false; }
        static const char* getFieldName_ny(){ return "ny";}
        static const char* getFieldTypeName_ny(){ return "float";}
        static void set_ny(void* instance, void* field_value){ static_cast<Vertex*>(instance)->ny = *static_cast<float*>(field_value);}
        static void* get_ny(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->ny));}
        static bool isArray_ny(){ return false; }
        static const char* getFieldName_nz(){ return "nz";}
        static const char* getFieldTypeName_nz(){ return "float";}
        static void set_nz(void* instance, void* field_value){ static_cast<Vertex*>(instance)->nz = *static_cast<float*>(field_value);}
        static void* get_nz(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->nz));}
        static bool isArray_nz(){ return false; }
        static const char* getFieldName_tx(){ return "tx";}
        static const char* getFieldTypeName_tx(){ return "float";}
        static void set_tx(void* instance, void* field_value){ static_cast<Vertex*>(instance)->tx = *static_cast<float*>(field_value);}
        static void* get_tx(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->tx));}
        static bool isArray_tx(){ return false; }
        static const char* getFieldName_ty(){ return "ty";}
        static const char* getFieldTypeName_ty(){ return "float";}
        static void set_ty(void* instance, void* field_value){ static_cast<Vertex*>(instance)->ty = *static_cast<float*>(field_value);}
        static void* get_ty(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->ty));}
        static bool isArray_ty(){ return false; }
        static const char* getFieldName_tz(){ return "tz";}
        static const char* getFieldTypeName_tz(){ return "float";}
        static void set_tz(void* instance, void* field_value){ static_cast<Vertex*>(instance)->tz = *static_cast<float*>(field_value);}
        static void* get_tz(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->tz));}
        static bool isArray_tz(){ return false; }
        static const char* getFieldName_u(){ return "u";}
        static const char* getFieldTypeName_u(){ return "float";}
        static void set_u(void* instance, void* field_value){ static_cast<Vertex*>(instance)->u = *static_cast<float*>(field_value);}
        static void* get_u(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->u));}
        static bool isArray_u(){ return false; }
        static const char* getFieldName_v(){ return "v";}
        static const char* getFieldTypeName_v(){ return "float";}
        static void set_v(void* instance, void* field_value){ static_cast<Vertex*>(instance)->v = *static_cast<float*>(field_value);}
        static void* get_v(void* instance){ return static_cast<void*>(&(static_cast<Vertex*>(instance)->v));}
        static bool isArray_v(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vertex(){
    FieldFunctionTuple* field_function_tuple_px=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_px,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_px,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_px,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_px,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_px);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_px);
    FieldFunctionTuple* field_function_tuple_py=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_py,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_py,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_py,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_py,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_py);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_py);
    FieldFunctionTuple* field_function_tuple_pz=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_pz,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_pz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_pz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_pz,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_pz);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_pz);
    FieldFunctionTuple* field_function_tuple_nx=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_nx,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_nx,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_nx,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_nx,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_nx);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_nx);
    FieldFunctionTuple* field_function_tuple_ny=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_ny,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_ny,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_ny,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_ny,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_ny);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_ny);
    FieldFunctionTuple* field_function_tuple_nz=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_nz,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_nz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_nz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_nz,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_nz);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_nz);
    FieldFunctionTuple* field_function_tuple_tx=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_tx,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_tx,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_tx,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_tx,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_tx);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_tx);
    FieldFunctionTuple* field_function_tuple_ty=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_ty,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_ty,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_ty,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_ty,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_ty);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_ty);
    FieldFunctionTuple* field_function_tuple_tz=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_tz,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_tz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_tz,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_tz,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_tz);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_tz);
    FieldFunctionTuple* field_function_tuple_u=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_u,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_u,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_u,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_u,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_u);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_u);
    FieldFunctionTuple* field_function_tuple_v=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::set_v,
    &TypeFieldReflectionOparator::TypeVertexOperator::get_v,
    &TypeFieldReflectionOparator::TypeVertexOperator::getClassName,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldName_v,
    &TypeFieldReflectionOparator::TypeVertexOperator::getFieldTypeName_v,
    &TypeFieldReflectionOparator::TypeVertexOperator::isArray_v);
    REGISTER_FIELD_TO_MAP("Vertex", field_function_tuple_v);

    

    
    ClassFunctionTuple* class_function_tuple_Vertex=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeVertexOperator::getVertexBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeVertexOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeVertexOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("Vertex", class_function_tuple_Vertex);
    }namespace TypeFieldReflectionOparator{
    class TypeSkeletonBindingOperator{
    public:
        static const char* getClassName(){ return "SkeletonBinding";}
        static void* constructorWithJson(const Json& json_context){
            SkeletonBinding* ret_instance= new SkeletonBinding;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(SkeletonBinding*)instance);
        }
        // base class
        static int getSkeletonBindingBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_index0(){ return "index0";}
        static const char* getFieldTypeName_index0(){ return "int";}
        static void set_index0(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->index0 = *static_cast<int*>(field_value);}
        static void* get_index0(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->index0));}
        static bool isArray_index0(){ return false; }
        static const char* getFieldName_index1(){ return "index1";}
        static const char* getFieldTypeName_index1(){ return "int";}
        static void set_index1(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->index1 = *static_cast<int*>(field_value);}
        static void* get_index1(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->index1));}
        static bool isArray_index1(){ return false; }
        static const char* getFieldName_index2(){ return "index2";}
        static const char* getFieldTypeName_index2(){ return "int";}
        static void set_index2(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->index2 = *static_cast<int*>(field_value);}
        static void* get_index2(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->index2));}
        static bool isArray_index2(){ return false; }
        static const char* getFieldName_index3(){ return "index3";}
        static const char* getFieldTypeName_index3(){ return "int";}
        static void set_index3(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->index3 = *static_cast<int*>(field_value);}
        static void* get_index3(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->index3));}
        static bool isArray_index3(){ return false; }
        static const char* getFieldName_weight0(){ return "weight0";}
        static const char* getFieldTypeName_weight0(){ return "float";}
        static void set_weight0(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->weight0 = *static_cast<float*>(field_value);}
        static void* get_weight0(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->weight0));}
        static bool isArray_weight0(){ return false; }
        static const char* getFieldName_weight1(){ return "weight1";}
        static const char* getFieldTypeName_weight1(){ return "float";}
        static void set_weight1(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->weight1 = *static_cast<float*>(field_value);}
        static void* get_weight1(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->weight1));}
        static bool isArray_weight1(){ return false; }
        static const char* getFieldName_weight2(){ return "weight2";}
        static const char* getFieldTypeName_weight2(){ return "float";}
        static void set_weight2(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->weight2 = *static_cast<float*>(field_value);}
        static void* get_weight2(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->weight2));}
        static bool isArray_weight2(){ return false; }
        static const char* getFieldName_weight3(){ return "weight3";}
        static const char* getFieldTypeName_weight3(){ return "float";}
        static void set_weight3(void* instance, void* field_value){ static_cast<SkeletonBinding*>(instance)->weight3 = *static_cast<float*>(field_value);}
        static void* get_weight3(void* instance){ return static_cast<void*>(&(static_cast<SkeletonBinding*>(instance)->weight3));}
        static bool isArray_weight3(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_SkeletonBinding(){
    FieldFunctionTuple* field_function_tuple_index0=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_index0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_index0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_index0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_index0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_index0);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_index0);
    FieldFunctionTuple* field_function_tuple_index1=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_index1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_index1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_index1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_index1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_index1);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_index1);
    FieldFunctionTuple* field_function_tuple_index2=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_index2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_index2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_index2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_index2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_index2);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_index2);
    FieldFunctionTuple* field_function_tuple_index3=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_index3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_index3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_index3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_index3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_index3);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_index3);
    FieldFunctionTuple* field_function_tuple_weight0=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_weight0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_weight0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_weight0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_weight0,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_weight0);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_weight0);
    FieldFunctionTuple* field_function_tuple_weight1=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_weight1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_weight1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_weight1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_weight1,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_weight1);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_weight1);
    FieldFunctionTuple* field_function_tuple_weight2=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_weight2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_weight2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_weight2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_weight2,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_weight2);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_weight2);
    FieldFunctionTuple* field_function_tuple_weight3=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::set_weight3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::get_weight3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldName_weight3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getFieldTypeName_weight3,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::isArray_weight3);
    REGISTER_FIELD_TO_MAP("SkeletonBinding", field_function_tuple_weight3);

    

    
    ClassFunctionTuple* class_function_tuple_SkeletonBinding=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::getSkeletonBindingBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSkeletonBindingOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("SkeletonBinding", class_function_tuple_SkeletonBinding);
    }namespace TypeFieldReflectionOparator{
    class TypeMeshDataOperator{
    public:
        static const char* getClassName(){ return "MeshData";}
        static void* constructorWithJson(const Json& json_context){
            MeshData* ret_instance= new MeshData;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(MeshData*)instance);
        }
        // base class
        static int getMeshDataBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_vertex_buffer(){ return "vertex_buffer";}
        static const char* getFieldTypeName_vertex_buffer(){ return "std::vector<Vertex>";}
        static void set_vertex_buffer(void* instance, void* field_value){ static_cast<MeshData*>(instance)->vertex_buffer = *static_cast<std::vector<Vertex>*>(field_value);}
        static void* get_vertex_buffer(void* instance){ return static_cast<void*>(&(static_cast<MeshData*>(instance)->vertex_buffer));}
        static bool isArray_vertex_buffer(){ return true; }
        static const char* getFieldName_index_buffer(){ return "index_buffer";}
        static const char* getFieldTypeName_index_buffer(){ return "std::vector<int>";}
        static void set_index_buffer(void* instance, void* field_value){ static_cast<MeshData*>(instance)->index_buffer = *static_cast<std::vector<int>*>(field_value);}
        static void* get_index_buffer(void* instance){ return static_cast<void*>(&(static_cast<MeshData*>(instance)->index_buffer));}
        static bool isArray_index_buffer(){ return true; }
        static const char* getFieldName_bind(){ return "bind";}
        static const char* getFieldTypeName_bind(){ return "std::vector<SkeletonBinding>";}
        static void set_bind(void* instance, void* field_value){ static_cast<MeshData*>(instance)->bind = *static_cast<std::vector<SkeletonBinding>*>(field_value);}
        static void* get_bind(void* instance){ return static_cast<void*>(&(static_cast<MeshData*>(instance)->bind));}
        static bool isArray_bind(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLSkeletonBindingROperatorMACRO
#define ArraystdSSvectorLSkeletonBindingROperatorMACRO
    class ArraystdSSvectorLSkeletonBindingROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<SkeletonBinding>";}
            static const char* getElementTypeName(){ return "SkeletonBinding";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<SkeletonBinding>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<SkeletonBinding>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<SkeletonBinding>*>(instance))[index] = *static_cast<SkeletonBinding*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLSkeletonBindingROperator
    #ifndef ArraystdSSvectorLVertexROperatorMACRO
#define ArraystdSSvectorLVertexROperatorMACRO
    class ArraystdSSvectorLVertexROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<Vertex>";}
            static const char* getElementTypeName(){ return "Vertex";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<Vertex>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<Vertex>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<Vertex>*>(instance))[index] = *static_cast<Vertex*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLVertexROperator
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

    void TypeWrapperRegister_MeshData(){
    FieldFunctionTuple* field_function_tuple_vertex_buffer=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshDataOperator::set_vertex_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::get_vertex_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldName_vertex_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldTypeName_vertex_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::isArray_vertex_buffer);
    REGISTER_FIELD_TO_MAP("MeshData", field_function_tuple_vertex_buffer);
    FieldFunctionTuple* field_function_tuple_index_buffer=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshDataOperator::set_index_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::get_index_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldName_index_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldTypeName_index_buffer,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::isArray_index_buffer);
    REGISTER_FIELD_TO_MAP("MeshData", field_function_tuple_index_buffer);
    FieldFunctionTuple* field_function_tuple_bind=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshDataOperator::set_bind,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::get_bind,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldName_bind,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getFieldTypeName_bind,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::isArray_bind);
    REGISTER_FIELD_TO_MAP("MeshData", field_function_tuple_bind);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLSkeletonBindingR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLSkeletonBindingROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLSkeletonBindingROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLSkeletonBindingROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLSkeletonBindingROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLSkeletonBindingROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<SkeletonBinding>", array_tuple_stdSSvectorLSkeletonBindingR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLVertexR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLVertexROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLVertexROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLVertexROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLVertexROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLVertexROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<Vertex>", array_tuple_stdSSvectorLVertexR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLintR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLintROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<int>", array_tuple_stdSSvectorLintR);
    ClassFunctionTuple* class_function_tuple_MeshData=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeMeshDataOperator::getMeshDataBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeMeshDataOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("MeshData", class_function_tuple_MeshData);
    }
    namespace TypeWrappersRegister{
    void MeshData()
    {
    TypeWrapperRegister_Vertex();
    TypeWrapperRegister_SkeletonBinding();
    TypeWrapperRegister_MeshData();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

