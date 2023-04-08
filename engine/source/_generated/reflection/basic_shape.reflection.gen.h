#pragma once
#include "runtime\resource\res_type\data\basic_shape.h"

namespace SimpleEngine{
    class Geometry;
    class Box;
    class Sphere;
    class Capsule;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeGeometryOperator{
    public:
        static const char* getClassName(){ return "Geometry";}
        static void* constructorWithJson(const Json& json_context){
            Geometry* ret_instance= new Geometry;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Geometry*)instance);
        }
        // base class
        static int getGeometryBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Geometry(){
    

    

    
    ClassFunctionTuple* class_function_tuple_Geometry=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeGeometryOperator::getGeometryBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeGeometryOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeGeometryOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("Geometry", class_function_tuple_Geometry);
    }namespace TypeFieldReflectionOparator{
    class TypeBoxOperator{
    public:
        static const char* getClassName(){ return "Box";}
        static void* constructorWithJson(const Json& json_context){
            Box* ret_instance= new Box;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Box*)instance);
        }
        // base class
        static int getBoxBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::Geometry,static_cast<Box*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_half_extents(){ return "m_half_extents";}
        static const char* getFieldTypeName_m_half_extents(){ return "Vector3";}
        static void set_m_half_extents(void* instance, void* field_value){ static_cast<Box*>(instance)->m_half_extents = *static_cast<Vector3*>(field_value);}
        static void* get_m_half_extents(void* instance){ return static_cast<void*>(&(static_cast<Box*>(instance)->m_half_extents));}
        static bool isArray_m_half_extents(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Box(){
    FieldFunctionTuple* field_function_tuple_m_half_extents=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoxOperator::set_m_half_extents,
    &TypeFieldReflectionOparator::TypeBoxOperator::get_m_half_extents,
    &TypeFieldReflectionOparator::TypeBoxOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBoxOperator::getFieldName_m_half_extents,
    &TypeFieldReflectionOparator::TypeBoxOperator::getFieldTypeName_m_half_extents,
    &TypeFieldReflectionOparator::TypeBoxOperator::isArray_m_half_extents);
    REGISTER_FIELD_TO_MAP("Box", field_function_tuple_m_half_extents);

    

    
    ClassFunctionTuple* class_function_tuple_Box=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoxOperator::getBoxBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeBoxOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeBoxOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("Box", class_function_tuple_Box);
    }namespace TypeFieldReflectionOparator{
    class TypeSphereOperator{
    public:
        static const char* getClassName(){ return "Sphere";}
        static void* constructorWithJson(const Json& json_context){
            Sphere* ret_instance= new Sphere;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Sphere*)instance);
        }
        // base class
        static int getSphereBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::Geometry,static_cast<Sphere*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_radius(){ return "m_radius";}
        static const char* getFieldTypeName_m_radius(){ return "float";}
        static void set_m_radius(void* instance, void* field_value){ static_cast<Sphere*>(instance)->m_radius = *static_cast<float*>(field_value);}
        static void* get_m_radius(void* instance){ return static_cast<void*>(&(static_cast<Sphere*>(instance)->m_radius));}
        static bool isArray_m_radius(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Sphere(){
    FieldFunctionTuple* field_function_tuple_m_radius=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeSphereOperator::set_m_radius,
    &TypeFieldReflectionOparator::TypeSphereOperator::get_m_radius,
    &TypeFieldReflectionOparator::TypeSphereOperator::getClassName,
    &TypeFieldReflectionOparator::TypeSphereOperator::getFieldName_m_radius,
    &TypeFieldReflectionOparator::TypeSphereOperator::getFieldTypeName_m_radius,
    &TypeFieldReflectionOparator::TypeSphereOperator::isArray_m_radius);
    REGISTER_FIELD_TO_MAP("Sphere", field_function_tuple_m_radius);

    

    
    ClassFunctionTuple* class_function_tuple_Sphere=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeSphereOperator::getSphereBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeSphereOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeSphereOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("Sphere", class_function_tuple_Sphere);
    }namespace TypeFieldReflectionOparator{
    class TypeCapsuleOperator{
    public:
        static const char* getClassName(){ return "Capsule";}
        static void* constructorWithJson(const Json& json_context){
            Capsule* ret_instance= new Capsule;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Capsule*)instance);
        }
        // base class
        static int getCapsuleBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(SimpleEngine::Geometry,static_cast<Capsule*>(instance));
            }
            return count;
        }
        // fields
        static const char* getFieldName_m_radius(){ return "m_radius";}
        static const char* getFieldTypeName_m_radius(){ return "float";}
        static void set_m_radius(void* instance, void* field_value){ static_cast<Capsule*>(instance)->m_radius = *static_cast<float*>(field_value);}
        static void* get_m_radius(void* instance){ return static_cast<void*>(&(static_cast<Capsule*>(instance)->m_radius));}
        static bool isArray_m_radius(){ return false; }
        static const char* getFieldName_m_half_height(){ return "m_half_height";}
        static const char* getFieldTypeName_m_half_height(){ return "float";}
        static void set_m_half_height(void* instance, void* field_value){ static_cast<Capsule*>(instance)->m_half_height = *static_cast<float*>(field_value);}
        static void* get_m_half_height(void* instance){ return static_cast<void*>(&(static_cast<Capsule*>(instance)->m_half_height));}
        static bool isArray_m_half_height(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Capsule(){
    FieldFunctionTuple* field_function_tuple_m_radius=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeCapsuleOperator::set_m_radius,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::get_m_radius,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getClassName,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getFieldName_m_radius,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getFieldTypeName_m_radius,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::isArray_m_radius);
    REGISTER_FIELD_TO_MAP("Capsule", field_function_tuple_m_radius);
    FieldFunctionTuple* field_function_tuple_m_half_height=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeCapsuleOperator::set_m_half_height,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::get_m_half_height,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getClassName,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getFieldName_m_half_height,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getFieldTypeName_m_half_height,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::isArray_m_half_height);
    REGISTER_FIELD_TO_MAP("Capsule", field_function_tuple_m_half_height);

    

    
    ClassFunctionTuple* class_function_tuple_Capsule=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeCapsuleOperator::getCapsuleBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeCapsuleOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("Capsule", class_function_tuple_Capsule);
    }
    namespace TypeWrappersRegister{
    void BasicShape()
    {
    TypeWrapperRegister_Geometry();
    TypeWrapperRegister_Box();
    TypeWrapperRegister_Sphere();
    TypeWrapperRegister_Capsule();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

