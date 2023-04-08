#pragma once
#include "runtime\function\framework\component\rigidbody\rigidbody_component.h"

namespace SimpleEngine{
    class RigidBodyComponent;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeRigidBodyComponentOperator{
    public:
        static const char* getClassName(){ return "RigidBodyComponent";}
        static void* constructorWithJson(const Json& json_context){
            RigidBodyComponent* ret_instance= new RigidBodyComponent;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(RigidBodyComponent*)instance);
        }
        // base class
        static int getRigidBodyComponentBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::Component,static_cast<RigidBodyComponent*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_rigidbody_res(){ return "m_rigidbody_res";}
        static const char* getFieldTypeName_m_rigidbody_res(){ return "RigidBodyComponentRes";}
        static void set_m_rigidbody_res(void* instance, void* field_value){ static_cast<RigidBodyComponent*>(instance)->m_rigidbody_res = *static_cast<RigidBodyComponentRes*>(field_value);}
        static void* get_m_rigidbody_res(void* instance){ return static_cast<void*>(&(static_cast<RigidBodyComponent*>(instance)->m_rigidbody_res));}
        static bool isArray_m_rigidbody_res(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_RigidBodyComponent(){
    FieldFunctionTuple* field_function_tuple_m_rigidbody_res=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::set_m_rigidbody_res,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::get_m_rigidbody_res,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::getClassName,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::getFieldName_m_rigidbody_res,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::getFieldTypeName_m_rigidbody_res,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::isArray_m_rigidbody_res);
    REGISTER_FIELD_TO_MAP("RigidBodyComponent", field_function_tuple_m_rigidbody_res);

    

    
    ClassFunctionTuple* class_function_tuple_RigidBodyComponent=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::getRigidBodyComponentBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeRigidBodyComponentOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("RigidBodyComponent", class_function_tuple_RigidBodyComponent);
    }
    namespace TypeWrappersRegister{
    void RigidbodyComponent()
    {
    TypeWrapperRegister_RigidBodyComponent();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

