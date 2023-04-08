#pragma once
#include "runtime\resource\res_type\data\animation_clip.h"

namespace SimpleEngine{
    class AnimNodeMap;
    class AnimationChannel;
    class AnimationClip;
    class AnimationAsset;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAnimNodeMapOperator{
    public:
        static const char* getClassName(){ return "AnimNodeMap";}
        static void* constructorWithJson(const Json& json_context){
            AnimNodeMap* ret_instance= new AnimNodeMap;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimNodeMap*)instance);
        }
        // base class
        static int getAnimNodeMapBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_convert(){ return "convert";}
        static const char* getFieldTypeName_convert(){ return "std::vector<std::string>";}
        static void set_convert(void* instance, void* field_value){ static_cast<AnimNodeMap*>(instance)->convert = *static_cast<std::vector<std::string>*>(field_value);}
        static void* get_convert(void* instance){ return static_cast<void*>(&(static_cast<AnimNodeMap*>(instance)->convert));}
        static bool isArray_convert(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLstdSSstringROperatorMACRO
#define ArraystdSSvectorLstdSSstringROperatorMACRO
    class ArraystdSSvectorLstdSSstringROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<std::string>";}
            static const char* getElementTypeName(){ return "std::string";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<std::string>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<std::string>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<std::string>*>(instance))[index] = *static_cast<std::string*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLstdSSstringROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_AnimNodeMap(){
    FieldFunctionTuple* field_function_tuple_convert=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::set_convert,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::get_convert,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::getFieldName_convert,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::getFieldTypeName_convert,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::isArray_convert);
    REGISTER_FIELD_TO_MAP("AnimNodeMap", field_function_tuple_convert);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLstdSSstringR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<std::string>", array_tuple_stdSSvectorLstdSSstringR);
    ClassFunctionTuple* class_function_tuple_AnimNodeMap=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::getAnimNodeMapBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimNodeMapOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimNodeMap", class_function_tuple_AnimNodeMap);
    }namespace TypeFieldReflectionOparator{
    class TypeAnimationChannelOperator{
    public:
        static const char* getClassName(){ return "AnimationChannel";}
        static void* constructorWithJson(const Json& json_context){
            AnimationChannel* ret_instance= new AnimationChannel;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationChannel*)instance);
        }
        // base class
        static int getAnimationChannelBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_name(){ return "name";}
        static const char* getFieldTypeName_name(){ return "std::string";}
        static void set_name(void* instance, void* field_value){ static_cast<AnimationChannel*>(instance)->name = *static_cast<std::string*>(field_value);}
        static void* get_name(void* instance){ return static_cast<void*>(&(static_cast<AnimationChannel*>(instance)->name));}
        static bool isArray_name(){ return false; }
        static const char* getFieldName_position_keys(){ return "position_keys";}
        static const char* getFieldTypeName_position_keys(){ return "std::vector<Vector3>";}
        static void set_position_keys(void* instance, void* field_value){ static_cast<AnimationChannel*>(instance)->position_keys = *static_cast<std::vector<Vector3>*>(field_value);}
        static void* get_position_keys(void* instance){ return static_cast<void*>(&(static_cast<AnimationChannel*>(instance)->position_keys));}
        static bool isArray_position_keys(){ return true; }
        static const char* getFieldName_rotation_keys(){ return "rotation_keys";}
        static const char* getFieldTypeName_rotation_keys(){ return "std::vector<Quaternion>";}
        static void set_rotation_keys(void* instance, void* field_value){ static_cast<AnimationChannel*>(instance)->rotation_keys = *static_cast<std::vector<Quaternion>*>(field_value);}
        static void* get_rotation_keys(void* instance){ return static_cast<void*>(&(static_cast<AnimationChannel*>(instance)->rotation_keys));}
        static bool isArray_rotation_keys(){ return true; }
        static const char* getFieldName_scaling_keys(){ return "scaling_keys";}
        static const char* getFieldTypeName_scaling_keys(){ return "std::vector<Vector3>";}
        static void set_scaling_keys(void* instance, void* field_value){ static_cast<AnimationChannel*>(instance)->scaling_keys = *static_cast<std::vector<Vector3>*>(field_value);}
        static void* get_scaling_keys(void* instance){ return static_cast<void*>(&(static_cast<AnimationChannel*>(instance)->scaling_keys));}
        static bool isArray_scaling_keys(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLQuaternionROperatorMACRO
#define ArraystdSSvectorLQuaternionROperatorMACRO
    class ArraystdSSvectorLQuaternionROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<Quaternion>";}
            static const char* getElementTypeName(){ return "Quaternion";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<Quaternion>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<Quaternion>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<Quaternion>*>(instance))[index] = *static_cast<Quaternion*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLQuaternionROperator
    #ifndef ArraystdSSvectorLVector3ROperatorMACRO
#define ArraystdSSvectorLVector3ROperatorMACRO
    class ArraystdSSvectorLVector3ROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<Vector3>";}
            static const char* getElementTypeName(){ return "Vector3";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<Vector3>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<Vector3>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<Vector3>*>(instance))[index] = *static_cast<Vector3*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLVector3ROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_AnimationChannel(){
    FieldFunctionTuple* field_function_tuple_name=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::set_name,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::get_name,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldName_name,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldTypeName_name,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::isArray_name);
    REGISTER_FIELD_TO_MAP("AnimationChannel", field_function_tuple_name);
    FieldFunctionTuple* field_function_tuple_position_keys=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::set_position_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::get_position_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldName_position_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldTypeName_position_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::isArray_position_keys);
    REGISTER_FIELD_TO_MAP("AnimationChannel", field_function_tuple_position_keys);
    FieldFunctionTuple* field_function_tuple_rotation_keys=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::set_rotation_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::get_rotation_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldName_rotation_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldTypeName_rotation_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::isArray_rotation_keys);
    REGISTER_FIELD_TO_MAP("AnimationChannel", field_function_tuple_rotation_keys);
    FieldFunctionTuple* field_function_tuple_scaling_keys=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::set_scaling_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::get_scaling_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldName_scaling_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getFieldTypeName_scaling_keys,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::isArray_scaling_keys);
    REGISTER_FIELD_TO_MAP("AnimationChannel", field_function_tuple_scaling_keys);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLQuaternionR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLQuaternionROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLQuaternionROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLQuaternionROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLQuaternionROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLQuaternionROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<Quaternion>", array_tuple_stdSSvectorLQuaternionR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLVector3R = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLVector3ROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLVector3ROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLVector3ROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLVector3ROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLVector3ROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<Vector3>", array_tuple_stdSSvectorLVector3R);
    ClassFunctionTuple* class_function_tuple_AnimationChannel=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::getAnimationChannelBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationChannelOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationChannel", class_function_tuple_AnimationChannel);
    }namespace TypeFieldReflectionOparator{
    class TypeAnimationClipOperator{
    public:
        static const char* getClassName(){ return "AnimationClip";}
        static void* constructorWithJson(const Json& json_context){
            AnimationClip* ret_instance= new AnimationClip;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationClip*)instance);
        }
        // base class
        static int getAnimationClipBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_total_frame(){ return "total_frame";}
        static const char* getFieldTypeName_total_frame(){ return "int";}
        static void set_total_frame(void* instance, void* field_value){ static_cast<AnimationClip*>(instance)->total_frame = *static_cast<int*>(field_value);}
        static void* get_total_frame(void* instance){ return static_cast<void*>(&(static_cast<AnimationClip*>(instance)->total_frame));}
        static bool isArray_total_frame(){ return false; }
        static const char* getFieldName_node_count(){ return "node_count";}
        static const char* getFieldTypeName_node_count(){ return "int";}
        static void set_node_count(void* instance, void* field_value){ static_cast<AnimationClip*>(instance)->node_count = *static_cast<int*>(field_value);}
        static void* get_node_count(void* instance){ return static_cast<void*>(&(static_cast<AnimationClip*>(instance)->node_count));}
        static bool isArray_node_count(){ return false; }
        static const char* getFieldName_node_channels(){ return "node_channels";}
        static const char* getFieldTypeName_node_channels(){ return "std::vector<AnimationChannel>";}
        static void set_node_channels(void* instance, void* field_value){ static_cast<AnimationClip*>(instance)->node_channels = *static_cast<std::vector<AnimationChannel>*>(field_value);}
        static void* get_node_channels(void* instance){ return static_cast<void*>(&(static_cast<AnimationClip*>(instance)->node_channels));}
        static bool isArray_node_channels(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLAnimationChannelROperatorMACRO
#define ArraystdSSvectorLAnimationChannelROperatorMACRO
    class ArraystdSSvectorLAnimationChannelROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<AnimationChannel>";}
            static const char* getElementTypeName(){ return "AnimationChannel";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<AnimationChannel>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<AnimationChannel>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<AnimationChannel>*>(instance))[index] = *static_cast<AnimationChannel*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLAnimationChannelROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_AnimationClip(){
    FieldFunctionTuple* field_function_tuple_total_frame=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::set_total_frame,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::get_total_frame,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldName_total_frame,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldTypeName_total_frame,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::isArray_total_frame);
    REGISTER_FIELD_TO_MAP("AnimationClip", field_function_tuple_total_frame);
    FieldFunctionTuple* field_function_tuple_node_count=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::set_node_count,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::get_node_count,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldName_node_count,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldTypeName_node_count,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::isArray_node_count);
    REGISTER_FIELD_TO_MAP("AnimationClip", field_function_tuple_node_count);
    FieldFunctionTuple* field_function_tuple_node_channels=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::set_node_channels,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::get_node_channels,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldName_node_channels,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getFieldTypeName_node_channels,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::isArray_node_channels);
    REGISTER_FIELD_TO_MAP("AnimationClip", field_function_tuple_node_channels);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLAnimationChannelR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationChannelROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationChannelROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationChannelROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationChannelROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationChannelROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<AnimationChannel>", array_tuple_stdSSvectorLAnimationChannelR);
    ClassFunctionTuple* class_function_tuple_AnimationClip=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::getAnimationClipBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationClipOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationClip", class_function_tuple_AnimationClip);
    }namespace TypeFieldReflectionOparator{
    class TypeAnimationAssetOperator{
    public:
        static const char* getClassName(){ return "AnimationAsset";}
        static void* constructorWithJson(const Json& json_context){
            AnimationAsset* ret_instance= new AnimationAsset;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(AnimationAsset*)instance);
        }
        // base class
        static int getAnimationAssetBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_node_map(){ return "node_map";}
        static const char* getFieldTypeName_node_map(){ return "AnimNodeMap";}
        static void set_node_map(void* instance, void* field_value){ static_cast<AnimationAsset*>(instance)->node_map = *static_cast<AnimNodeMap*>(field_value);}
        static void* get_node_map(void* instance){ return static_cast<void*>(&(static_cast<AnimationAsset*>(instance)->node_map));}
        static bool isArray_node_map(){ return false; }
        static const char* getFieldName_clip_data(){ return "clip_data";}
        static const char* getFieldTypeName_clip_data(){ return "AnimationClip";}
        static void set_clip_data(void* instance, void* field_value){ static_cast<AnimationAsset*>(instance)->clip_data = *static_cast<AnimationClip*>(field_value);}
        static void* get_clip_data(void* instance){ return static_cast<void*>(&(static_cast<AnimationAsset*>(instance)->clip_data));}
        static bool isArray_clip_data(){ return false; }
        static const char* getFieldName_skeleton_file_path(){ return "skeleton_file_path";}
        static const char* getFieldTypeName_skeleton_file_path(){ return "std::string";}
        static void set_skeleton_file_path(void* instance, void* field_value){ static_cast<AnimationAsset*>(instance)->skeleton_file_path = *static_cast<std::string*>(field_value);}
        static void* get_skeleton_file_path(void* instance){ return static_cast<void*>(&(static_cast<AnimationAsset*>(instance)->skeleton_file_path));}
        static bool isArray_skeleton_file_path(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_AnimationAsset(){
    FieldFunctionTuple* field_function_tuple_node_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::set_node_map,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::get_node_map,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldName_node_map,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldTypeName_node_map,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::isArray_node_map);
    REGISTER_FIELD_TO_MAP("AnimationAsset", field_function_tuple_node_map);
    FieldFunctionTuple* field_function_tuple_clip_data=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::set_clip_data,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::get_clip_data,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldName_clip_data,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldTypeName_clip_data,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::isArray_clip_data);
    REGISTER_FIELD_TO_MAP("AnimationAsset", field_function_tuple_clip_data);
    FieldFunctionTuple* field_function_tuple_skeleton_file_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::set_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::get_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getClassName,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getFieldTypeName_skeleton_file_path,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::isArray_skeleton_file_path);
    REGISTER_FIELD_TO_MAP("AnimationAsset", field_function_tuple_skeleton_file_path);

    

    
    ClassFunctionTuple* class_function_tuple_AnimationAsset=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::getAnimationAssetBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeAnimationAssetOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("AnimationAsset", class_function_tuple_AnimationAsset);
    }
    namespace TypeWrappersRegister{
    void AnimationClip()
    {
    TypeWrapperRegister_AnimNodeMap();
    TypeWrapperRegister_AnimationChannel();
    TypeWrapperRegister_AnimationClip();
    TypeWrapperRegister_AnimationAsset();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

