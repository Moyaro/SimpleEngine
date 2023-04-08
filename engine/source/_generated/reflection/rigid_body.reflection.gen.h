#pragma once
#include "runtime\resource\res_type\components\rigid_body.h"

namespace SimpleEngine{
    class RigidBodyShape;
    class RigidBodyComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeRigidBodyShapeOperator{
    public:
        static const char* getClassName(){ return "RigidBodyShape";}
        static void* constructorWithJson(const Json& json_context){
            RigidBodyShape* ret_instance= new RigidBodyShape;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(RigidBodyShape*)instance);
        }
        // base class
        static int getRigidBodyShapeBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_local_transform(){ return "m_local_transform";}
        static const char* getFieldTypeName_m_local_transform(){ return "Transform";}
        static void set_m_local_transform(void* instance, void* field_value){ static_cast<RigidBodyShape*>(instance)->m_local_transform = *static_cast<Transform*>(field_value);}
        static void* get_m_local_transform(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyShape*>(instance)->m_local_transform));}
        static bool isArray_m_local_transform(){ return false; }
        static const char* getFieldName_m_geometry(){ return "m_geometry";}
        static const char* getFieldTypeName_m_geometry(){ return "Reflection::ReflectionPtr<Geometry>";}
        static void set_m_geometry(void* instance, void* field_value){ static_cast<RigidBodyShape*>(instance)->m_geometry = *static_cast<Reflection::ReflectionPtr<Geometry>*>(field_value);}
        static void* get_m_geometry(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyShape*>(instance)->m_geometry));}
        static bool isArray_m_geometry(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_RigidBodyShape(){
    FieldFunctionTuple* field_function_tuple_m_local_transform=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::set_m_local_transform,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::get_m_local_transform,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getFieldName_m_local_transform,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getFieldTypeName_m_local_transform,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::isArray_m_local_transform);
    REGISTER_FIELD_TO_MAP("RigidBodyShape", field_function_tuple_m_local_transform);
    FieldFunctionTuple* field_function_tuple_m_geometry=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::set_m_geometry,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::get_m_geometry,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getFieldName_m_geometry,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getFieldTypeName_m_geometry,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::isArray_m_geometry);
    REGISTER_FIELD_TO_MAP("RigidBodyShape", field_function_tuple_m_geometry);

    

    
    ClassFunctionTuple* class_function_tuple_RigidBodyShape=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::getRigidBodyShapeBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeRigidBodyShapeOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("RigidBodyShape", class_function_tuple_RigidBodyShape);
    }namespace TypeFieldReflectionOparator{
    class TypeRigidBodyComponentResOperator{
    public:
        static const char* getClassName(){ return "RigidBodyComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            RigidBodyComponentRes* ret_instance= new RigidBodyComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(RigidBodyComponentRes*)instance);
        }
        // base class
        static int getRigidBodyComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_m_shapes(){ return "m_shapes";}
        static const char* getFieldTypeName_m_shapes(){ return "std::vector<RigidBodyShape>";}
        static void set_m_shapes(void* instance, void* field_value){ static_cast<RigidBodyComponentRes*>(instance)->m_shapes = *static_cast<std::vector<RigidBodyShape>*>(field_value);}
        static void* get_m_shapes(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyComponentRes*>(instance)->m_shapes));}
        static bool isArray_m_shapes(){ return true; }
        static const char* getFieldName_m_inverse_mass(){ return "m_inverse_mass";}
        static const char* getFieldTypeName_m_inverse_mass(){ return "float";}
        static void set_m_inverse_mass(void* instance, void* field_value){ static_cast<RigidBodyComponentRes*>(instance)->m_inverse_mass = *static_cast<float*>(field_value);}
        static void* get_m_inverse_mass(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyComponentRes*>(instance)->m_inverse_mass));}
        static bool isArray_m_inverse_mass(){ return false; }
        static const char* getFieldName_m_actor_type(){ return "m_actor_type";}
        static const char* getFieldTypeName_m_actor_type(){ return "int";}
        static void set_m_actor_type(void* instance, void* field_value){ static_cast<RigidBodyComponentRes*>(instance)->m_actor_type = *static_cast<int*>(field_value);}
        static void* get_m_actor_type(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyComponentRes*>(instance)->m_actor_type));}
        static bool isArray_m_actor_type(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLRigidBodyShapeROperatorMACRO
#define ArraystdSSvectorLRigidBodyShapeROperatorMACRO
    class ArraystdSSvectorLRigidBodyShapeROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<RigidBodyShape>";}
            static const char* getElementTypeName(){ return "RigidBodyShape";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<RigidBodyShape>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<RigidBodyShape>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<RigidBodyShape>*>(instance))[index] = *static_cast<RigidBodyShape*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLRigidBodyShapeROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_RigidBodyComponentRes(){
    FieldFunctionTuple* field_function_tuple_m_shapes=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::set_m_shapes,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::get_m_shapes,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldName_m_shapes,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldTypeName_m_shapes,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::isArray_m_shapes);
    REGISTER_FIELD_TO_MAP("RigidBodyComponentRes", field_function_tuple_m_shapes);
    FieldFunctionTuple* field_function_tuple_m_inverse_mass=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::set_m_inverse_mass,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::get_m_inverse_mass,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldName_m_inverse_mass,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldTypeName_m_inverse_mass,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::isArray_m_inverse_mass);
    REGISTER_FIELD_TO_MAP("RigidBodyComponentRes", field_function_tuple_m_inverse_mass);
    FieldFunctionTuple* field_function_tuple_m_actor_type=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::set_m_actor_type,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::get_m_actor_type,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldName_m_actor_type,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getFieldTypeName_m_actor_type,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::isArray_m_actor_type);
    REGISTER_FIELD_TO_MAP("RigidBodyComponentRes", field_function_tuple_m_actor_type);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLRigidBodyShapeR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLRigidBodyShapeROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLRigidBodyShapeROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLRigidBodyShapeROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLRigidBodyShapeROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLRigidBodyShapeROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<RigidBodyShape>", array_tuple_stdSSvectorLRigidBodyShapeR);
    ClassFunctionTuple* class_function_tuple_RigidBodyComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::getRigidBodyComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("RigidBodyComponentRes", class_function_tuple_RigidBodyComponentRes);
    }
    namespace TypeWrappersRegister{
    void RigidBody()
    {
    TypeWrapperRegister_RigidBodyShape();
    TypeWrapperRegister_RigidBodyComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

