#pragma once
#include "runtime\resource\res_type\components\animation.h"

namespace SimpleEngine{
    class AnimationResultElement;
    class AnimationResult;
    class AnimationComponentRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAnimationResultElementOperator{
    public:
        static const char* getClassName(){ return "AnimationResultElement";}
        static void* constructorWithJson(const Json& json_context){
            AnimationResultElement* ret_instance= new AnimationResultElement;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationResultElement*)instance);
        }
        // base class
        static int getAnimationResultElementBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_AnimationResultElement(){
    

    

    
    ClassFunctionTuple* class_function_tuple_AnimationResultElement=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationResultElementOperator::getAnimationResultElementBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationResultElementOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationResultElementOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationResultElement", class_function_tuple_AnimationResultElement);
    }namespace TypeFieldReflectionOparator{
    class TypeAnimationResultOperator{
    public:
        static const char* getClassName(){ return "AnimationResult";}
        static void* constructorWithJson(const Json& json_context){
            AnimationResult* ret_instance= new AnimationResult;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationResult*)instance);
        }
        // base class
        static int getAnimationResultBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_node(){ return "node";}
        static const char* getFieldTypeName_node(){ return "std::vector<AnimationResultElement>";}
        static void set_node(void* instance, void* field_value){ static_cast<AnimationResult*>(instance)->node = *static_cast<std::vector<AnimationResultElement>*>(field_value);}
        static void* get_node(void* instance){ return static_cast<void*>(&(static_cast<AnimationResult*>(instance)->node));}
        static bool isArray_node(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLAnimationResultElementROperatorMACRO
#define ArraystdSSvectorLAnimationResultElementROperatorMACRO
    class ArraystdSSvectorLAnimationResultElementROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<AnimationResultElement>";}
            static const char* getElementTypeName(){ return "AnimationResultElement";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<AnimationResultElement>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<AnimationResultElement>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<AnimationResultElement>*>(instance))[index] = *static_cast<AnimationResultElement*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLAnimationResultElementROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_AnimationResult(){
    FieldFunctionTuple* field_function_tuple_node=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::set_node,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::get_node,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::getFieldName_node,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::getFieldTypeName_node,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::isArray_node);
    REGISTER_FIELD_TO_MAP("AnimationResult", field_function_tuple_node);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLAnimationResultElementR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationResultElementROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationResultElementROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationResultElementROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationResultElementROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationResultElementROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<AnimationResultElement>", array_tuple_stdSSvectorLAnimationResultElementR);
    ClassFunctionTuple* class_function_tuple_AnimationResult=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::getAnimationResultBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationResultOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationResult", class_function_tuple_AnimationResult);
    }namespace TypeFieldReflectionOparator{
    class TypeAnimationComponentResOperator{
    public:
        static const char* getClassName(){ return "AnimationComponentRes";}
        static void* constructorWithJson(const Json& json_context){
            AnimationComponentRes* ret_instance= new AnimationComponentRes;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationComponentRes*)instance);
        }
        // base class
        static int getAnimationComponentResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_skeleton_file_path(){ return "skeleton_file_path";}
        static const char* getFieldTypeName_skeleton_file_path(){ return "std::string";}
        static void set_skeleton_file_path(void* instance, void* field_value){ static_cast<AnimationComponentRes*>(instance)->skeleton_file_path = *static_cast<std::string*>(field_value);}
        static void* get_skeleton_file_path(void* instance){ return static_cast<void*>(&(static_cast<AnimationComponentRes*>(instance)->skeleton_file_path));}
        static bool isArray_skeleton_file_path(){ return false; }
        static const char* getFieldName_blend_state(){ return "blend_state";}
        static const char* getFieldTypeName_blend_state(){ return "BlendState";}
        static void set_blend_state(void* instance, void* field_value){ static_cast<AnimationComponentRes*>(instance)->blend_state = *static_cast<BlendState*>(field_value);}
        static void* get_blend_state(void* instance){ return static_cast<void*>(&(static_cast<AnimationComponentRes*>(instance)->blend_state));}
        static bool isArray_blend_state(){ return false; }
        static const char* getFieldName_frame_position(){ return "frame_position";}
        static const char* getFieldTypeName_frame_position(){ return "float";}
        static void set_frame_position(void* instance, void* field_value){ static_cast<AnimationComponentRes*>(instance)->frame_position = *static_cast<float*>(field_value);}
        static void* get_frame_position(void* instance){ return static_cast<void*>(&(static_cast<AnimationComponentRes*>(instance)->frame_position));}
        static bool isArray_frame_position(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_AnimationComponentRes(){
    FieldFunctionTuple* field_function_tuple_skeleton_file_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::set_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::get_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldTypeName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::isArray_skeleton_file_path);
    REGISTER_FIELD_TO_MAP("AnimationComponentRes", field_function_tuple_skeleton_file_path);
    FieldFunctionTuple* field_function_tuple_blend_state=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::set_blend_state,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::get_blend_state,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldName_blend_state,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldTypeName_blend_state,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::isArray_blend_state);
    REGISTER_FIELD_TO_MAP("AnimationComponentRes", field_function_tuple_blend_state);
    FieldFunctionTuple* field_function_tuple_frame_position=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::set_frame_position,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::get_frame_position,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldName_frame_position,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getFieldTypeName_frame_position,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::isArray_frame_position);
    REGISTER_FIELD_TO_MAP("AnimationComponentRes", field_function_tuple_frame_position);

    

    
    ClassFunctionTuple* class_function_tuple_AnimationComponentRes=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::getAnimationComponentResBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationComponentResOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationComponentRes", class_function_tuple_AnimationComponentRes);
    }
    namespace TypeWrappersRegister{
    void Animation()
    {
    TypeWrapperRegister_AnimationResultElement();
    TypeWrapperRegister_AnimationResult();
    TypeWrapperRegister_AnimationComponentRes();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

