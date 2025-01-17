#pragma once
#include "core/meta/json.h"
#include "../reflection/reflection.h"
#include <cassert>

namespace SimpleEngine {
    //检错
    template<typename...>
    inline constexpr bool always_false = false;

    class Serializer
    {
    public:

        //参数为反射指针的读/写
        template<typename T>
        static Json write(const Reflection::ReflectionPtr<T>& instance)
        {
            T* instance_ptr = static_cast<T*>(instance.operator->());//获取实例指针
            std::string type_name = instance.getTypeName();//获取类型名
            return Json::object{ {"$typeName", Json(type_name)},{"$context", Reflection::TypeMeta::writeByName(type_name, instance_ptr)} };
        }

        template<typename T>
        static T*& read(const Json& json_context, Reflection::ReflectionPtr<T>& instance)
        {
            //设置类型名
            std::string type_name = json_context["$typeName"].string_value();
            instance.setTypeName(type_name);

            return readPointer(json_context, instance.getPtrReference());//把实例指针交给其他函数读取
        }

        template<typename T>
        static Json write(const T& instance){
            if constexpr (std::is_pointer<T>::value)//如果T是指针
                return writePointer((T)instance);
            else {
                static_assert(always_false<T>, "Serializer::read<T> has not been implemented yet!");
                return Json();
            }
        }

        template<typename T>
        static T& read(const Json& json_context, T& instance){
            if constexpr (std::is_pointer<T>::value)
                return readPointer(json_context, instance);
            else {
                static_assert(always_false<T>, "Serializer::read<T> has not been implemented yet!");
                return instance;
            }
                
        }

        //读/写指针
        template<typename T>
        static Json writePointer(T* instance)
        {
            return Json::object{ {"$typeName", Json {"*"}}, {"$context", Serializer::write(*instance)} };
        }

        template<typename T>
        static T*& readPointer(const Json& json_context, T*& instance)
        {
            assert(instance == nullptr);
            std::string type_name = json_context["$typeName"].string_value();//获取类型名
            assert(!type_name.empty());
            if ('*' == type_name[0])//类型为*直接读
            {
                instance = new T;
                read(json_context["$context"], *instance);
            }
            else//创建反射实例
            {
                instance = static_cast<T*>(Reflection::TypeMeta::newFromNameAndJson(type_name, json_context["$context"]).m_instance);
            }
            return instance;
        }
    };

    template<>
    Json Serializer::write(const char& instance);
    template<>
    char& Serializer::read(const Json& json_context, char& instance);

    template<>
    Json Serializer::write(const int& instance);
    template<>
    int& Serializer::read(const Json& json_context, int& instance);

    template<>
    Json Serializer::write(const unsigned int& instance);
    template<>
    unsigned int& Serializer::read(const Json& json_context, unsigned int& instance);

    template<>
    Json Serializer::write(const float& instance);
    template<>
    float& Serializer::read(const Json& json_context, float& instance);

    template<>
    Json Serializer::write(const double& instance);
    template<>
    double& Serializer::read(const Json& json_context, double& instance);

    template<>
    Json Serializer::write(const bool& instance);
    template<>
    bool& Serializer::read(const Json& json_context, bool& instance);

    template<>
    Json Serializer::write(const std::string& instance);
    template<>
    std::string& Serializer::read(const Json& json_context, std::string& instance);
}