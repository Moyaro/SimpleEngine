#pragma once
#include "runtime\resource\res_type\data\blend_state.h"

namespace SimpleEngine{
    class BoneBlendWeight;
    class BlendStateWithClipData;
    class BlendState;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeBoneBlendWeightOperator{
    public:
        static const char* getClassName(){ return "BoneBlendWeight";}
        static void* constructorWithJson(const Json& json_context){
            BoneBlendWeight* ret_instance= new BoneBlendWeight;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(BoneBlendWeight*)instance);
        }
        // base class
        static int getBoneBlendWeightBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_blend_weight(){ return "blend_weight";}
        static const char* getFieldTypeName_blend_weight(){ return "std::vector<float>";}
        static void set_blend_weight(void* instance, void* field_value){ static_cast<BoneBlendWeight*>(instance)->blend_weight = *static_cast<std::vector<float>*>(field_value);}
        static void* get_blend_weight(void* instance){ return static_cast<void*>(&(static_cast<BoneBlendWeight*>(instance)->blend_weight));}
        static bool isArray_blend_weight(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLfloatROperatorMACRO
#define ArraystdSSvectorLfloatROperatorMACRO
    class ArraystdSSvectorLfloatROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<float>";}
            static const char* getElementTypeName(){ return "float";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<float>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<float>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<float>*>(instance))[index] = *static_cast<float*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLfloatROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_BoneBlendWeight(){
    FieldFunctionTuple* field_function_tuple_blend_weight=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::set_blend_weight,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::get_blend_weight,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::getFieldName_blend_weight,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::getFieldTypeName_blend_weight,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::isArray_blend_weight);
    REGISTER_FIELD_TO_MAP("BoneBlendWeight", field_function_tuple_blend_weight);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLfloatR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<float>", array_tuple_stdSSvectorLfloatR);
    ClassFunctionTuple* class_function_tuple_BoneBlendWeight=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::getBoneBlendWeightBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeBoneBlendWeightOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("BoneBlendWeight", class_function_tuple_BoneBlendWeight);
    }namespace TypeFieldReflectionOparator{
    class TypeBlendStateWithClipDataOperator{
    public:
        static const char* getClassName(){ return "BlendStateWithClipData";}
        static void* constructorWithJson(const Json& json_context){
            BlendStateWithClipData* ret_instance= new BlendStateWithClipData;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(BlendStateWithClipData*)instance);
        }
        // base class
        static int getBlendStateWithClipDataBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_clip_count(){ return "clip_count";}
        static const char* getFieldTypeName_clip_count(){ return "int";}
        static void set_clip_count(void* instance, void* field_value){ static_cast<BlendStateWithClipData*>(instance)->clip_count = *static_cast<int*>(field_value);}
        static void* get_clip_count(void* instance){ return static_cast<void*>(&(static_cast<BlendStateWithClipData*>(instance)->clip_count));}
        static bool isArray_clip_count(){ return false; }
        static const char* getFieldName_blend_clip(){ return "blend_clip";}
        static const char* getFieldTypeName_blend_clip(){ return "std::vector<AnimationClip>";}
        static void set_blend_clip(void* instance, void* field_value){ static_cast<BlendStateWithClipData*>(instance)->blend_clip = *static_cast<std::vector<AnimationClip>*>(field_value);}
        static void* get_blend_clip(void* instance){ return static_cast<void*>(&(static_cast<BlendStateWithClipData*>(instance)->blend_clip));}
        static bool isArray_blend_clip(){ return true; }
        static const char* getFieldName_blend_anim_skel_map(){ return "blend_anim_skel_map";}
        static const char* getFieldTypeName_blend_anim_skel_map(){ return "std::vector<AnimSkelMap>";}
        static void set_blend_anim_skel_map(void* instance, void* field_value){ static_cast<BlendStateWithClipData*>(instance)->blend_anim_skel_map = *static_cast<std::vector<AnimSkelMap>*>(field_value);}
        static void* get_blend_anim_skel_map(void* instance){ return static_cast<void*>(&(static_cast<BlendStateWithClipData*>(instance)->blend_anim_skel_map));}
        static bool isArray_blend_anim_skel_map(){ return true; }
        static const char* getFieldName_blend_weight(){ return "blend_weight";}
        static const char* getFieldTypeName_blend_weight(){ return "std::vector<BoneBlendWeight>";}
        static void set_blend_weight(void* instance, void* field_value){ static_cast<BlendStateWithClipData*>(instance)->blend_weight = *static_cast<std::vector<BoneBlendWeight>*>(field_value);}
        static void* get_blend_weight(void* instance){ return static_cast<void*>(&(static_cast<BlendStateWithClipData*>(instance)->blend_weight));}
        static bool isArray_blend_weight(){ return true; }
        static const char* getFieldName_blend_ratio(){ return "blend_ratio";}
        static const char* getFieldTypeName_blend_ratio(){ return "std::vector<float>";}
        static void set_blend_ratio(void* instance, void* field_value){ static_cast<BlendStateWithClipData*>(instance)->blend_ratio = *static_cast<std::vector<float>*>(field_value);}
        static void* get_blend_ratio(void* instance){ return static_cast<void*>(&(static_cast<BlendStateWithClipData*>(instance)->blend_ratio));}
        static bool isArray_blend_ratio(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLAnimSkelMapROperatorMACRO
#define ArraystdSSvectorLAnimSkelMapROperatorMACRO
    class ArraystdSSvectorLAnimSkelMapROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<AnimSkelMap>";}
            static const char* getElementTypeName(){ return "AnimSkelMap";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<AnimSkelMap>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<AnimSkelMap>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<AnimSkelMap>*>(instance))[index] = *static_cast<AnimSkelMap*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLAnimSkelMapROperator
    #ifndef ArraystdSSvectorLAnimationClipROperatorMACRO
#define ArraystdSSvectorLAnimationClipROperatorMACRO
    class ArraystdSSvectorLAnimationClipROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<AnimationClip>";}
            static const char* getElementTypeName(){ return "AnimationClip";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<AnimationClip>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<AnimationClip>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<AnimationClip>*>(instance))[index] = *static_cast<AnimationClip*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLAnimationClipROperator
    #ifndef ArraystdSSvectorLBoneBlendWeightROperatorMACRO
#define ArraystdSSvectorLBoneBlendWeightROperatorMACRO
    class ArraystdSSvectorLBoneBlendWeightROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<BoneBlendWeight>";}
            static const char* getElementTypeName(){ return "BoneBlendWeight";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<BoneBlendWeight>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<BoneBlendWeight>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<BoneBlendWeight>*>(instance))[index] = *static_cast<BoneBlendWeight*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLBoneBlendWeightROperator
    #ifndef ArraystdSSvectorLfloatROperatorMACRO
#define ArraystdSSvectorLfloatROperatorMACRO
    class ArraystdSSvectorLfloatROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<float>";}
            static const char* getElementTypeName(){ return "float";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<float>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<float>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<float>*>(instance))[index] = *static_cast<float*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLfloatROperator
    }//namespace ArrayReflectionOperator

    void TypeWrapperRegister_BlendStateWithClipData(){
    FieldFunctionTuple* field_function_tuple_clip_count=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::set_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::get_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldName_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldTypeName_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::isArray_clip_count);
    REGISTER_FIELD_TO_MAP("BlendStateWithClipData", field_function_tuple_clip_count);
    FieldFunctionTuple* field_function_tuple_blend_clip=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::set_blend_clip,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::get_blend_clip,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldName_blend_clip,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldTypeName_blend_clip,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::isArray_blend_clip);
    REGISTER_FIELD_TO_MAP("BlendStateWithClipData", field_function_tuple_blend_clip);
    FieldFunctionTuple* field_function_tuple_blend_anim_skel_map=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::set_blend_anim_skel_map,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::get_blend_anim_skel_map,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldName_blend_anim_skel_map,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldTypeName_blend_anim_skel_map,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::isArray_blend_anim_skel_map);
    REGISTER_FIELD_TO_MAP("BlendStateWithClipData", field_function_tuple_blend_anim_skel_map);
    FieldFunctionTuple* field_function_tuple_blend_weight=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::set_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::get_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldName_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldTypeName_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::isArray_blend_weight);
    REGISTER_FIELD_TO_MAP("BlendStateWithClipData", field_function_tuple_blend_weight);
    FieldFunctionTuple* field_function_tuple_blend_ratio=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::set_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::get_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldName_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getFieldTypeName_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::isArray_blend_ratio);
    REGISTER_FIELD_TO_MAP("BlendStateWithClipData", field_function_tuple_blend_ratio);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLAnimSkelMapR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLAnimSkelMapROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimSkelMapROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimSkelMapROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimSkelMapROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimSkelMapROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<AnimSkelMap>", array_tuple_stdSSvectorLAnimSkelMapR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLAnimationClipR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationClipROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationClipROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationClipROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationClipROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLAnimationClipROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<AnimationClip>", array_tuple_stdSSvectorLAnimationClipR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLBoneBlendWeightR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLBoneBlendWeightROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLBoneBlendWeightROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLBoneBlendWeightROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLBoneBlendWeightROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLBoneBlendWeightROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<BoneBlendWeight>", array_tuple_stdSSvectorLBoneBlendWeightR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLfloatR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<float>", array_tuple_stdSSvectorLfloatR);
    ClassFunctionTuple* class_function_tuple_BlendStateWithClipData=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::getBlendStateWithClipDataBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeBlendStateWithClipDataOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("BlendStateWithClipData", class_function_tuple_BlendStateWithClipData);
    }namespace TypeFieldReflectionOparator{
    class TypeBlendStateOperator{
    public:
        static const char* getClassName(){ return "BlendState";}
        static void* constructorWithJson(const Json& json_context){
            BlendState* ret_instance= new BlendState;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(BlendState*)instance);
        }
        // base class
        static int getBlendStateBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_clip_count(){ return "clip_count";}
        static const char* getFieldTypeName_clip_count(){ return "int";}
        static void set_clip_count(void* instance, void* field_value){ static_cast<BlendState*>(instance)->clip_count = *static_cast<int*>(field_value);}
        static void* get_clip_count(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->clip_count));}
        static bool isArray_clip_count(){ return false; }
        static const char* getFieldName_blend_clip_file_path(){ return "blend_clip_file_path";}
        static const char* getFieldTypeName_blend_clip_file_path(){ return "std::vector<std::string>";}
        static void set_blend_clip_file_path(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_clip_file_path = *static_cast<std::vector<std::string>*>(field_value);}
        static void* get_blend_clip_file_path(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_clip_file_path));}
        static bool isArray_blend_clip_file_path(){ return true; }
        static const char* getFieldName_blend_clip_file_length(){ return "blend_clip_file_length";}
        static const char* getFieldTypeName_blend_clip_file_length(){ return "std::vector<float>";}
        static void set_blend_clip_file_length(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_clip_file_length = *static_cast<std::vector<float>*>(field_value);}
        static void* get_blend_clip_file_length(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_clip_file_length));}
        static bool isArray_blend_clip_file_length(){ return true; }
        static const char* getFieldName_blend_anim_skel_map_path(){ return "blend_anim_skel_map_path";}
        static const char* getFieldTypeName_blend_anim_skel_map_path(){ return "std::vector<std::string>";}
        static void set_blend_anim_skel_map_path(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_anim_skel_map_path = *static_cast<std::vector<std::string>*>(field_value);}
        static void* get_blend_anim_skel_map_path(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_anim_skel_map_path));}
        static bool isArray_blend_anim_skel_map_path(){ return true; }
        static const char* getFieldName_blend_weight(){ return "blend_weight";}
        static const char* getFieldTypeName_blend_weight(){ return "std::vector<float>";}
        static void set_blend_weight(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_weight = *static_cast<std::vector<float>*>(field_value);}
        static void* get_blend_weight(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_weight));}
        static bool isArray_blend_weight(){ return true; }
        static const char* getFieldName_blend_mask_file_path(){ return "blend_mask_file_path";}
        static const char* getFieldTypeName_blend_mask_file_path(){ return "std::vector<std::string>";}
        static void set_blend_mask_file_path(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_mask_file_path = *static_cast<std::vector<std::string>*>(field_value);}
        static void* get_blend_mask_file_path(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_mask_file_path));}
        static bool isArray_blend_mask_file_path(){ return true; }
        static const char* getFieldName_blend_ratio(){ return "blend_ratio";}
        static const char* getFieldTypeName_blend_ratio(){ return "std::vector<float>";}
        static void set_blend_ratio(void* instance, void* field_value){ static_cast<BlendState*>(instance)->blend_ratio = *static_cast<std::vector<float>*>(field_value);}
        static void* get_blend_ratio(void* instance){ return static_cast<void*>(&(static_cast<BlendState*>(instance)->blend_ratio));}
        static bool isArray_blend_ratio(){ return true; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLfloatROperatorMACRO
#define ArraystdSSvectorLfloatROperatorMACRO
    class ArraystdSSvectorLfloatROperator{
        public:
            static const char* getArrayTypeName(){ return "std::vector<float>";}
            static const char* getElementTypeName(){ return "float";}
            static int getSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<float>*>(instance)->size());
            }
            static void* get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<float>*>(instance))[index]));
            }
            static void set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<float>*>(instance))[index] = *static_cast<float*>
    (element_value);
    }
    };
    #endif //ArraystdSSvectorLfloatROperator
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

    void TypeWrapperRegister_BlendState(){
    FieldFunctionTuple* field_function_tuple_clip_count=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_clip_count,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_clip_count);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_clip_count);
    FieldFunctionTuple* field_function_tuple_blend_clip_file_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_clip_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_clip_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_clip_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_clip_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_clip_file_path);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_clip_file_path);
    FieldFunctionTuple* field_function_tuple_blend_clip_file_length=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_clip_file_length,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_clip_file_length,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_clip_file_length,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_clip_file_length,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_clip_file_length);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_clip_file_length);
    FieldFunctionTuple* field_function_tuple_blend_anim_skel_map_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_anim_skel_map_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_anim_skel_map_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_anim_skel_map_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_anim_skel_map_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_anim_skel_map_path);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_anim_skel_map_path);
    FieldFunctionTuple* field_function_tuple_blend_weight=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_weight,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_weight);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_weight);
    FieldFunctionTuple* field_function_tuple_blend_mask_file_path=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_mask_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_mask_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_mask_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_mask_file_path,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_mask_file_path);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_mask_file_path);
    FieldFunctionTuple* field_function_tuple_blend_ratio=new FieldFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::set_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::get_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getClassName,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldName_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getFieldTypeName_blend_ratio,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::isArray_blend_ratio);
    REGISTER_FIELD_TO_MAP("BlendState", field_function_tuple_blend_ratio);

    

    ArrayFunctionTuple* array_tuple_stdSSvectorLfloatR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLfloatROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<float>", array_tuple_stdSSvectorLfloatR);
    ArrayFunctionTuple* array_tuple_stdSSvectorLstdSSstringR = new  ArrayFunctionTuple(
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::set,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::get,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getSize,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getArrayTypeName,
    &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getElementTypeName);
    REGISTER_ARRAY_TO_MAP("std::vector<std::string>", array_tuple_stdSSvectorLstdSSstringR);
    ClassFunctionTuple* class_function_tuple_BlendState=new ClassFunctionTuple(
    &TypeFieldReflectionOparator::TypeBlendStateOperator::getBlendStateBaseClassReflectionInstanceList,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::constructorWithJson,
    &TypeFieldReflectionOparator::TypeBlendStateOperator::writeByName);
    REGISTER_BASE_CLASS_TO_MAP("BlendState", class_function_tuple_BlendState);
    }
    namespace TypeWrappersRegister{
    void BlendState()
    {
    TypeWrapperRegister_BoneBlendWeight();
    TypeWrapperRegister_BlendStateWithClipData();
    TypeWrapperRegister_BlendState();
    }
    }//namespace TypeWrappersRegister

    }//namespace Reflection
    }//namespace SimpleEngine

