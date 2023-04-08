#pragma once

#include "runtime/core/meta/json.h"
#include <string>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace SimpleEngine {

    //启动反射编译
#if defined(__REFLECTION_PARSER__)
#define META(...) __attribute__((annotate(#__VA_ARGS__)))
#define CLASS(class_name,...) class __attribute__((annotate(#__VA_ARGS__))) class_name
#define STRUCT(struct_name,...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name

#else
#define META(...)
#define CLASS(class_name,...) class class_name
#define STRUCT(struct_name,...) struct struct_name
#endif

	//设置为序列化和当前类操作器的友元类
#define REFLECTION_BODY(class_name) \
	friend class Reflection::TypeFieldReflectionOparator::Type##class_name##Operator;\
	friend class Serializer;
    //设置当前类操作器的声明
#define REFLECTION_TYPE(class_name) \
	namespace Reflection{ \
		namespace TypeFieldReflectionOparator{ \
			class Type##class_name##Operator; \
		}\
	};

    //创建反射指针：类名，实例指针
#define ENGINE_REFLECTION_NEW(name, ...) Reflection::ReflectionPtr(#name, new name(__VA_ARGS__));
    //删除反射指针
#define ENGINE_REFLECTION_DELETE(value) \
    if (value) \
    { \
        delete value.operator->(); \
        value.getPtrReference() = nullptr; \
    }
    //反射指针的深拷贝
#define ENGINE_REFLECTION_DEEP_COPY(type, dst_ptr, src_ptr) \
    *static_cast<type*>(dst_ptr) = *static_cast<type*>(src_ptr.getPtr());


    //创建反射实例：元类型，实例指针
#define TypeMetaDef(class_name, ptr) \
    SimpleEngine::Reflection::ReflectionInstance(SimpleEngine::Reflection::TypeMeta::newMetaFromName(#class_name),(class_name*)ptr)
#define TypeMetaDefPtr(class_name, ptr) \
    new SimpleEngine::Reflection::ReflectionInstance(SimpleEngine::Reflection::TypeMeta::newMetaFromName(#class_name),(class_name*)ptr)


//注册类、属性、数组
#define REGISTER_BASE_CLASS_TO_MAP(name,value) TypeMetaRegisterinterface::registerToClassMap(name,value);
#define REGISTER_FIELD_TO_MAP(name, value) TypeMetaRegisterinterface::registerToFieldMap(name, value);
#define REGISTER_ARRAY_TO_MAP(name, value) TypeMetaRegisterinterface::registerToArrayMap(name, value);
#define REGISTER_METHOD_TO_MAP(name, value) TypeMetaRegisterinterface::registerToMethodMap(name, value);
#define UNREGISTER_ALL TypeMetaRegisterinterface::unregisterAll();

	namespace Reflection {
		class TypeMeta;
		class FieldAccessor;
		class ArrayAccessor;
        class MethodAccessor;
		class ReflectionInstance;
	}

	//功能类型
	using SetFunction = std::function<void(void*, void*)>;
	using GetFunction = std::function<void* (void*)>;
	using GetNameFunction = std::function<const char*()>;
	using SetArrayFunc = std::function<void(int, void*, void*)>;
	using GetArrayFunc = std::function<void* (int, void*)>;
	using GetSizeFunc = std::function<int(void*)>;
	using GetBoolFunc = std::function<bool()>;
	using InvokeFunction = std::function<void(void*)>;

	using ConstructorWithJson = std::function<void* (const Json&)>;
	using WriteJsonByName = std::function<Json(void*)>;
	using GetBaseClassReflectionInstanceListFunc = std::function<int(Reflection::ReflectionInstance*&, void*)>;

	//功能元组
	using FieldFunctionTuple = std::tuple<SetFunction, GetFunction, GetNameFunction, GetNameFunction, GetNameFunction, GetBoolFunc>;
	using MethodFunctionTuple = std::tuple<GetNameFunction, InvokeFunction>;
	using ClassFunctionTuple = std::tuple<GetBaseClassReflectionInstanceListFunc, ConstructorWithJson, WriteJsonByName>;
	using ArrayFunctionTuple = std::tuple<SetArrayFunc, GetArrayFunc, GetSizeFunc, GetNameFunction, GetNameFunction>;

	namespace Reflection {
		class TypeMetaRegisterinterface
		{
		public:
			static void registerToClassMap(const char* name, ClassFunctionTuple* value);
			static void registerToFieldMap(const char* name, FieldFunctionTuple* value);
			static void registerToArrayMap(const char* name, ArrayFunctionTuple* value);
            static void registerToMethodMap(const char* name, MethodFunctionTuple* value);

			static void unregisterAll();
		};

		/// <summary>
		/// 元类型：方法、字段、类型名
		/// </summary>
		class TypeMeta {
			friend class FieldAccessor;
			friend class ArrayAccessor;
			friend class TypeMetaRegisterInterface;

		public:
			TypeMeta();

			static TypeMeta newMetaFromName(std::string type_name) { return TypeMeta(type_name); }//创建元类型
			static bool newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor);//创建数组访问器
			static ReflectionInstance newFromNameAndJson(std::string type_name, const Json& json_context);//返回创建的反射实例
			static Json writeByName(std::string type_name, void* instance);

			int getBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance);//获取反射实例列表

            //获取字段、方法列表，返回个数
			int getFieldsList(FieldAccessor*& out_list);
			int getMethodsList(MethodAccessor*& out_list);
            //根据名字获取方法/字段
			FieldAccessor getFieldByName(const char* name);
			MethodAccessor getMethodByName(const char* name);

			bool isValid() { return m_is_valid; }//类型是否有效
            std::string getTypeName() { return m_type_name; }//获取类型名

			TypeMeta& operator=(const TypeMeta& dest);

		private:
			TypeMeta(std::string type_name);

			std::string m_type_name;//类型名
			bool m_is_valid;//类型是否可用

			//字段、方法
			std::vector<FieldAccessor>   m_fields;
			std::vector<MethodAccessor> m_methods;
		};

		/// <summary>
		/// 字段访问器：访问类型的字段
		/// </summary>
		class FieldAccessor
		{
			friend class TypeMeta;
		public:
			FieldAccessor();

            //设置和获取字段
			void* get(void* instance) { return static_cast<void*>((std::get<1>(*m_function))(instance)); }
			void  set(void* instance, void* value) { (std::get<0>(*m_function))(instance,value); }

			TypeMeta getOwnerTypeMeta() { return TypeMeta((std::get<2>(*m_function))()); }//获取字段的源类型
			bool getTypeMeta(TypeMeta& field_type);//获取字段类型，返回类型是否有效，无效说明是C++内置类型

            //获取字段、字段类型名
			const char* getFieldName() const { return m_field_name; } 
			const char* getFieldTypeName() { return m_field_type_name; }

            //是否为数组类型
			bool isArrayType() { return (std::get<5>(*m_function))(); }

			FieldAccessor& operator=(const FieldAccessor& dest);

		private:
			FieldAccessor(FieldFunctionTuple* functions);

			FieldFunctionTuple* m_function;
			const char* m_field_name;
			const char* m_field_type_name;
		};

        /// <summary>
        /// 函数访问器
        /// </summary>
        class MethodAccessor
        {
            friend class TypeMeta;
        public:
            MethodAccessor();

            //获取函数名、调用函数
            void invoke(void* instance) { (std::get<1>(*m_functions))(instance); }
            const char* getMethodName() const { return m_method_name; }

            MethodAccessor& operator=(const MethodAccessor& dest);
        private:
            MethodAccessor(MethodFunctionTuple* functions);

        private:
            MethodFunctionTuple* m_functions;
            const char* m_method_name;
        };

		/// <summary>
		/// 数组访问器
		/// </summary>
		class ArrayAccessor {
			friend class TypeMeta;

		public:
			ArrayAccessor();
            
            //获取数组类型名、数组元素类型名
            const char* getArrayTypeName() { return m_array_type_name; }
            const char* getElementTypeName() { return m_element_type_name; }

            //获取数组大小，设置/获取数组
            int getSize(void* instance) { return std::get<2>(*m_functions)(instance); }
            void set(int index, void* instance, void* element_value);
            void* get(int index, void* instance);

            ArrayAccessor& operator=(ArrayAccessor& dest);
		private:
            ArrayAccessor(ArrayFunctionTuple* array_func);

			ArrayFunctionTuple* m_functions;
			const char* m_array_type_name;
			const char* m_element_type_name;
		};


        

        
        
        /// <summary>
        /// 反射实例：有元类型、实例指针
        /// </summary>
        class ReflectionInstance
        {
        public:
            ReflectionInstance(TypeMeta meta, void* instance) : m_meta(meta), m_instance(instance) {}
            ReflectionInstance() : m_meta(), m_instance(nullptr) {}

            ReflectionInstance& operator=(ReflectionInstance& dest);
            ReflectionInstance& operator=(ReflectionInstance&& dest);

        public:
            TypeMeta m_meta;//元类型
            void* m_instance;//实例指针
        };

        /// <summary>
        /// 反射指针：元类型的指针
        /// </summary>
        template<typename T>
        class ReflectionPtr
        {
            template<typename U>
            friend class ReflectionPtr;
        public:
            //初始化
            ReflectionPtr(std::string type_name, T* instance) : m_type_name(type_name), m_instance(instance) {}
            ReflectionPtr() : m_type_name(), m_instance(nullptr) {}

            ReflectionPtr(const ReflectionPtr& dest) : m_type_name(dest.m_type_name), m_instance(dest.m_instance) {}

            //相同/不同类型模板类之间通过=赋值，左值/右值都可以使用
            template<typename U>
            ReflectionPtr<T>& operator=(const ReflectionPtr<U>& dest)
            {
                if (this == static_cast<void*>(&dest))
                {
                    return *this;
                }
                m_type_name = dest.m_type_name;
                m_instance = static_cast<T*>(dest.m_instance);
                return *this;
            }

            template<typename U>
            ReflectionPtr<T>& operator=(ReflectionPtr<U>&& dest)
            {
                if (this == static_cast<void*>(&dest))
                {
                    return *this;
                }
                m_type_name = dest.m_type_name;
                m_instance = static_cast<T*>(dest.m_instance);
                return *this;
            }

            ReflectionPtr<T>& operator=(const ReflectionPtr<T>& dest)
            {
                if (this == &dest)
                {
                    return *this;
                }
                m_type_name = dest.m_type_name;
                m_instance = dest.m_instance;
                return *this;
            }

            ReflectionPtr<T>& operator=(ReflectionPtr<T>&& dest)
            {
                if (this == &dest)
                {
                    return *this;
                }
                m_type_name = dest.m_type_name;
                m_instance = dest.m_instance;
                return *this;
            }

            //获取/设置类型名
            std::string getTypeName() const { return m_type_name; }
            void setTypeName(std::string name) { m_type_name = name; }

            //相同类型之间的比较（比较m_instance）
            bool operator==(const T* ptr) const { return (m_instance == ptr); }
            bool operator!=(const T* ptr) const { return (m_instance != ptr); }
            bool operator==(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance == rhs_ptr.m_instance); }
            bool operator!=(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance != rhs_ptr.m_instance); }

            //隐式类型转换为T1/ReflectionPtr<T1>
            template<typename T1>
                explicit operator T1* ()
            {
                return static_cast<T1*>(m_instance);
            }

            template<typename T1>
                operator ReflectionPtr<T1>()
            {
                return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
            }

            template<typename T1>
                explicit operator const T1* () const
            {
                return static_cast<T1*>(m_instance);
            }

            template<typename T1>
                operator const ReflectionPtr<T1>() const
            {
                return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
            }

            //获取instance的指针
            T* operator->() { return m_instance; }
            T* operator->() const { return m_instance; }
            T* getPtr() { return m_instance; }
            T* getPtr() const { return m_instance; }
            T*& getPtrReference() { return m_instance; }

            //获取instance
            T& operator*() { return *(m_instance); }
            const T& operator*() const { return *(static_cast<const T*>(m_instance)); }

            //bool的隐式转换，不为空时为true
            operator bool() const { return (m_instance != nullptr); }

        private:
            std::string m_type_name{ "" };
            typedef T m_type;
            T* m_instance{ nullptr };
        };
	}
}