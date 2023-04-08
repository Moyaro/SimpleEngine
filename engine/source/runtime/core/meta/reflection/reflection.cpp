#include "reflection.h"
#include <cstring>
#include <map>
#include <iostream>

namespace SimpleEngine {
	namespace Reflection {
		const char* k_unknown_type = "UnknownType";
		const char* k_unknown = "Unknown";

		//����ע������ࡢ�������ֶΡ�����
		static std::map<std::string, ClassFunctionTuple*> m_class_map;
		static std::multimap<std::string, FieldFunctionTuple*>  m_field_map;
		static std::multimap<std::string, MethodFunctionTuple*> m_method_map;
		static std::map<std::string, ArrayFunctionTuple*> m_array_map;

		//**********************************ע����********************************************//
		//���map��û����ͬ���ƾ�ע��ɹ�
		void TypeMetaRegisterinterface::registerToClassMap(const char* name, ClassFunctionTuple* value) {
			if (m_class_map.find(name) == m_class_map.end())
				m_class_map.insert(std::make_pair(name, value));
			else
				delete value;
		}
		void TypeMetaRegisterinterface::registerToArrayMap(const char* name, ArrayFunctionTuple* value)
		{
			if (m_array_map.find(name) == m_array_map.end())
				m_array_map.insert(std::make_pair(name, value));
			else
				delete value;
		}

		//����������ֱ��ע���map
		void TypeMetaRegisterinterface::registerToFieldMap(const char* name, FieldFunctionTuple* value)
		{
			m_field_map.insert(std::make_pair(name, value));
		}
		void TypeMetaRegisterinterface::registerToMethodMap(const char* name, MethodFunctionTuple* value)
		{
			m_method_map.insert(std::make_pair(name, value));
		}

		//���map��Ϣ
		void TypeMetaRegisterinterface::unregisterAll() {
			for (const auto& itr : m_class_map) {
				delete itr.second;
			}
			m_class_map.clear();

			for (const auto& itr : m_field_map) {
				delete itr.second;
			}
			m_field_map.clear();

			for (const auto& itr : m_array_map) {
				delete itr.second;
			}
			m_array_map.clear();
		}
		//**********************************TypeMeta��********************************************//
		//��ʼ��
		TypeMeta::TypeMeta() : m_type_name(k_unknown_type), m_is_valid(false) { m_fields.clear(); m_methods.clear();}
		TypeMeta::TypeMeta(std::string type_name) : m_type_name(type_name){
			m_is_valid = false;
			m_fields.clear();
			m_methods.clear();

			//�ҵ������͵������ֶΡ�������Ȼ�󱣴�
			auto fileds_iter = m_field_map.equal_range(type_name);
			while (fileds_iter.first != fileds_iter.second){
				FieldAccessor field(fileds_iter.first->second);
				m_fields.emplace_back(field);
				m_is_valid = true;

				++fileds_iter.first;
			}
			auto methods_iter = m_method_map.equal_range(type_name);
			while (methods_iter.first != methods_iter.second){
				MethodAccessor method(methods_iter.first->second);
				m_methods.emplace_back(method);
				m_is_valid = true;

				++methods_iter.first;
			}
		}

		bool TypeMeta::newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor){
			//���ע�������������飬�������������鴦����
			auto iter = m_array_map.find(array_type_name);
			if (iter != m_array_map.end())
			{
				ArrayAccessor new_accessor(iter->second);
				accessor = new_accessor;
				return true;
			}
			return false;
		}

		ReflectionInstance TypeMeta::newFromNameAndJson(std::string type_name, const Json& json_context){
			//��ע���б����ҵ���Ӧ������������ʵ�������򴴽���ʵ��
			auto iter = m_class_map.find(type_name);
			if (iter != m_class_map.end()){
				return ReflectionInstance(TypeMeta(type_name), (std::get<1>(*iter->second)(json_context)));
			}
			return ReflectionInstance();
		}

		Json TypeMeta::writeByName(std::string type_name, void* instance){
			//��ע���б����ҵ���Ӧ��������json�����򴴽���json
			auto iter = m_class_map.find(type_name);
			if (iter != m_class_map.end()){
				return std::get<2>(*iter->second)(instance);
			}
			return Json();
		}

		int TypeMeta::getFieldsList(FieldAccessor*& out_list){
			int count = m_fields.size();//��ȡ�ֶ���
			out_list = new FieldAccessor[count];//�½��ֶ�����
			for (int i = 0; i < count; ++i){
				out_list[i] = m_fields[i];
			}
			return count;
		}
		int TypeMeta::getMethodsList(MethodAccessor*& out_list){
			int count = m_methods.size();//��ȡ������
			out_list = new MethodAccessor[count];//�½���������
			for (int i = 0; i < count; ++i){
				out_list[i] = m_methods[i];
			}
			return count;
		}

		int TypeMeta::getBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance){
			//��ע���б����ҵ���Ӧ������������ʵ���б�����ʵ����
			auto iter = m_class_map.find(m_type_name);
			if (iter != m_class_map.end()){
				return (std::get<0>(*iter->second))(out_list, instance);
			}
			return 0;
		}

		FieldAccessor TypeMeta::getFieldByName(const char* name){
			//��Ԫ���͵������ֶ�����ָ���ֶε�ָ��
			const auto it = std::find_if(m_fields.begin(), m_fields.end(), [&](const auto& i) {
				return std::strcmp(i.getFieldName(), name) == 0;
				});
			if (it != m_fields.end()) return *it;
			return FieldAccessor(nullptr);
		}
		MethodAccessor TypeMeta::getMethodByName(const char* name){
			//��Ԫ���͵����к�������ָ��������ָ��
			const auto it = std::find_if(m_methods.begin(), m_methods.end(), [&](const auto& i) {
				return std::strcmp(i.getMethodName(), name) == 0;
			});
			if (it != m_methods.end()) return *it;
			return MethodAccessor(nullptr);
		}

		TypeMeta& TypeMeta::operator=(const TypeMeta& dest)
		{
			if (this == &dest)
			{
				return *this;
			}
			m_fields.clear();
			m_fields = dest.m_fields;

			m_methods.clear();
			m_methods = dest.m_methods;

			m_type_name = dest.m_type_name;
			m_is_valid = dest.m_is_valid;

			return *this;
		}
		//**********************************FieldAccessor��********************************************//
		//��ʼ��
		FieldAccessor::FieldAccessor():m_function(nullptr), m_field_name(k_unknown), m_field_type_name(k_unknown_type){}
		FieldAccessor::FieldAccessor(FieldFunctionTuple* functions) : m_function(functions){
			m_field_type_name = k_unknown_type;
			m_field_name = k_unknown;
			if (m_function == nullptr) return;
			
			m_field_type_name = (std::get<4>(*m_function))();//��ȡ�ֶ�������
			m_field_name = (std::get<3>(*m_function))();//��ȡ�ֶ���
		}

		bool FieldAccessor::getTypeMeta(TypeMeta& field_type){
			TypeMeta type(m_field_type_name);
			field_type = type;
			return type.m_is_valid;
		}

		FieldAccessor& FieldAccessor::operator=(const FieldAccessor& dest) {
			if (this == &dest) return *this;
			m_function = dest.m_function;
			m_field_name = dest.m_field_name;
			m_field_type_name = dest.m_field_type_name;
			return *this;
		}
		//**********************************ArrayAccessor��********************************************//
		ArrayAccessor::ArrayAccessor():m_functions(nullptr), m_array_type_name(k_unknown_type), m_element_type_name(k_unknown_type){}
		ArrayAccessor::ArrayAccessor(ArrayFunctionTuple* array_func) : m_functions(array_func){
			m_array_type_name = k_unknown_type;
			m_element_type_name = k_unknown_type;
			if (m_functions == nullptr){
				return;
			}

			m_array_type_name = std::get<3>(*m_functions)();
			m_element_type_name = std::get<4>(*m_functions)();
		}
		
		void ArrayAccessor::set(int index, void* instance, void* element_value){
			size_t count = getSize(instance);
			if (index >= count || index < 0) {
				std::cout << "��������";
				return;
			}
			std::get<0>(*m_functions)(index, instance, element_value);
		}

		void* ArrayAccessor::get(int index, void* instance){
			size_t count = getSize(instance);
			if (index >= count || index < 0) {
				std::cout << "��������";
				return nullptr;
			}
			return std::get<1>(*m_functions)(index, instance);
		}

		ArrayAccessor& ArrayAccessor::operator=(ArrayAccessor& dest){
			if (this == &dest){
				return *this;
			}
			m_functions = dest.m_functions;
			m_array_type_name = dest.m_array_type_name;
			m_element_type_name = dest.m_element_type_name;
			return *this;
		}

		//**********************************MethodAccessor��********************************************//

		MethodAccessor::MethodAccessor():m_method_name(k_unknown),m_functions(nullptr){}
		MethodAccessor::MethodAccessor(MethodFunctionTuple* functions) : m_functions(functions)
		{
			m_method_name = k_unknown;
			if (m_functions == nullptr){
				return;
			}

			m_method_name = (std::get<0>(*m_functions))();
		}

		MethodAccessor& MethodAccessor::operator=(const MethodAccessor& dest)
		{
			if (this == &dest){
				return *this;
			}
			m_functions = dest.m_functions;
			m_method_name = dest.m_method_name;
			return *this;
		}

		//**********************************ReflectionInstance��********************************************//
		ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance& dest)
		{
			if (this == &dest)
			{
				return *this;
			}
			m_instance = dest.m_instance;
			m_meta = dest.m_meta;

			return *this;
		}

		ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance&& dest)
		{
			if (this == &dest)
			{
				return *this;
			}
			m_instance = dest.m_instance;
			m_meta = dest.m_meta;

			return *this;
		}
	}
}