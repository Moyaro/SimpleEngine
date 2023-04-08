#pragma once

#include "runtime/core/meta/json.h"
#include <string>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace SimpleEngine {

    //�����������
#if defined(__REFLECTION_PARSER__)
#define META(...) __attribute__((annotate(#__VA_ARGS__)))
#define CLASS(class_name,...) class __attribute__((annotate(#__VA_ARGS__))) class_name
#define STRUCT(struct_name,...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name

#else
#define META(...)
#define CLASS(class_name,...) class class_name
#define STRUCT(struct_name,...) struct struct_name
#endif

	//����Ϊ���л��͵�ǰ�����������Ԫ��
#define REFLECTION_BODY(class_name) \
	friend class Reflection::TypeFieldReflectionOparator::Type##class_name##Operator;\
	friend class Serializer;
    //���õ�ǰ�������������
#define REFLECTION_TYPE(class_name) \
	namespace Reflection{ \
		namespace TypeFieldReflectionOparator{ \
			class Type##class_name##Operator; \
		}\
	};

    //��������ָ�룺������ʵ��ָ��
#define ENGINE_REFLECTION_NEW(name, ...) Reflection::ReflectionPtr(#name, new name(__VA_ARGS__));
    //ɾ������ָ��
#define ENGINE_REFLECTION_DELETE(value) \
    if (value) \
    { \
        delete value.operator->(); \
        value.getPtrReference() = nullptr; \
    }
    //����ָ������
#define ENGINE_REFLECTION_DEEP_COPY(type, dst_ptr, src_ptr) \
    *static_cast<type*>(dst_ptr) = *static_cast<type*>(src_ptr.getPtr());


    //��������ʵ����Ԫ���ͣ�ʵ��ָ��
#define TypeMetaDef(class_name, ptr) \
    SimpleEngine::Reflection::ReflectionInstance(SimpleEngine::Reflection::TypeMeta::newMetaFromName(#class_name),(class_name*)ptr)
#define TypeMetaDefPtr(class_name, ptr) \
    new SimpleEngine::Reflection::ReflectionInstance(SimpleEngine::Reflection::TypeMeta::newMetaFromName(#class_name),(class_name*)ptr)


//ע���ࡢ���ԡ�����
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

	//��������
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

	//����Ԫ��
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
		/// Ԫ���ͣ��������ֶΡ�������
		/// </summary>
		class TypeMeta {
			friend class FieldAccessor;
			friend class ArrayAccessor;
			friend class TypeMetaRegisterInterface;

		public:
			TypeMeta();

			static TypeMeta newMetaFromName(std::string type_name) { return TypeMeta(type_name); }//����Ԫ����
			static bool newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor);//�������������
			static ReflectionInstance newFromNameAndJson(std::string type_name, const Json& json_context);//���ش����ķ���ʵ��
			static Json writeByName(std::string type_name, void* instance);

			int getBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance);//��ȡ����ʵ���б�

            //��ȡ�ֶΡ������б����ظ���
			int getFieldsList(FieldAccessor*& out_list);
			int getMethodsList(MethodAccessor*& out_list);
            //�������ֻ�ȡ����/�ֶ�
			FieldAccessor getFieldByName(const char* name);
			MethodAccessor getMethodByName(const char* name);

			bool isValid() { return m_is_valid; }//�����Ƿ���Ч
            std::string getTypeName() { return m_type_name; }//��ȡ������

			TypeMeta& operator=(const TypeMeta& dest);

		private:
			TypeMeta(std::string type_name);

			std::string m_type_name;//������
			bool m_is_valid;//�����Ƿ����

			//�ֶΡ�����
			std::vector<FieldAccessor>   m_fields;
			std::vector<MethodAccessor> m_methods;
		};

		/// <summary>
		/// �ֶη��������������͵��ֶ�
		/// </summary>
		class FieldAccessor
		{
			friend class TypeMeta;
		public:
			FieldAccessor();

            //���úͻ�ȡ�ֶ�
			void* get(void* instance) { return static_cast<void*>((std::get<1>(*m_function))(instance)); }
			void  set(void* instance, void* value) { (std::get<0>(*m_function))(instance,value); }

			TypeMeta getOwnerTypeMeta() { return TypeMeta((std::get<2>(*m_function))()); }//��ȡ�ֶε�Դ����
			bool getTypeMeta(TypeMeta& field_type);//��ȡ�ֶ����ͣ����������Ƿ���Ч����Ч˵����C++��������

            //��ȡ�ֶΡ��ֶ�������
			const char* getFieldName() const { return m_field_name; } 
			const char* getFieldTypeName() { return m_field_type_name; }

            //�Ƿ�Ϊ��������
			bool isArrayType() { return (std::get<5>(*m_function))(); }

			FieldAccessor& operator=(const FieldAccessor& dest);

		private:
			FieldAccessor(FieldFunctionTuple* functions);

			FieldFunctionTuple* m_function;
			const char* m_field_name;
			const char* m_field_type_name;
		};

        /// <summary>
        /// ����������
        /// </summary>
        class MethodAccessor
        {
            friend class TypeMeta;
        public:
            MethodAccessor();

            //��ȡ�����������ú���
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
		/// ���������
		/// </summary>
		class ArrayAccessor {
			friend class TypeMeta;

		public:
			ArrayAccessor();
            
            //��ȡ����������������Ԫ��������
            const char* getArrayTypeName() { return m_array_type_name; }
            const char* getElementTypeName() { return m_element_type_name; }

            //��ȡ�����С������/��ȡ����
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
        /// ����ʵ������Ԫ���͡�ʵ��ָ��
        /// </summary>
        class ReflectionInstance
        {
        public:
            ReflectionInstance(TypeMeta meta, void* instance) : m_meta(meta), m_instance(instance) {}
            ReflectionInstance() : m_meta(), m_instance(nullptr) {}

            ReflectionInstance& operator=(ReflectionInstance& dest);
            ReflectionInstance& operator=(ReflectionInstance&& dest);

        public:
            TypeMeta m_meta;//Ԫ����
            void* m_instance;//ʵ��ָ��
        };

        /// <summary>
        /// ����ָ�룺Ԫ���͵�ָ��
        /// </summary>
        template<typename T>
        class ReflectionPtr
        {
            template<typename U>
            friend class ReflectionPtr;
        public:
            //��ʼ��
            ReflectionPtr(std::string type_name, T* instance) : m_type_name(type_name), m_instance(instance) {}
            ReflectionPtr() : m_type_name(), m_instance(nullptr) {}

            ReflectionPtr(const ReflectionPtr& dest) : m_type_name(dest.m_type_name), m_instance(dest.m_instance) {}

            //��ͬ/��ͬ����ģ����֮��ͨ��=��ֵ����ֵ/��ֵ������ʹ��
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

            //��ȡ/����������
            std::string getTypeName() const { return m_type_name; }
            void setTypeName(std::string name) { m_type_name = name; }

            //��ͬ����֮��ıȽϣ��Ƚ�m_instance��
            bool operator==(const T* ptr) const { return (m_instance == ptr); }
            bool operator!=(const T* ptr) const { return (m_instance != ptr); }
            bool operator==(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance == rhs_ptr.m_instance); }
            bool operator!=(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance != rhs_ptr.m_instance); }

            //��ʽ����ת��ΪT1/ReflectionPtr<T1>
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

            //��ȡinstance��ָ��
            T* operator->() { return m_instance; }
            T* operator->() const { return m_instance; }
            T* getPtr() { return m_instance; }
            T* getPtr() const { return m_instance; }
            T*& getPtrReference() { return m_instance; }

            //��ȡinstance
            T& operator*() { return *(m_instance); }
            const T& operator*() const { return *(static_cast<const T*>(m_instance)); }

            //bool����ʽת������Ϊ��ʱΪtrue
            operator bool() const { return (m_instance != nullptr); }

        private:
            std::string m_type_name{ "" };
            typedef T m_type;
            T* m_instance{ nullptr };
        };
	}
}