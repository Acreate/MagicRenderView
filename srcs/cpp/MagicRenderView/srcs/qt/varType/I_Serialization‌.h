#ifndef I_SERIALIZATION__H_H_HEAD__FILE__
#define I_SERIALIZATION__H_H_HEAD__FILE__
#pragma once
#include "../../alias/type_alias.h"

class VarGenerate;
class Application;
class I_Type;
/// @brief 用于自定义数组或类型子类实现序列化的对象
class I_Serialization‌ {
protected:
	Application *applicationInstancePtr;
	VarGenerate *varInstance;
	const type_info &typeInfo;
	std_vector_pairt< const I_Type *, std_vector< uint8_t > > serializationMap;
	std_vector_pairt< const type_info &, std_vector< QString > > typeMap;
public:
	I_Serialization‌( const type_info &set_type_info );
	/// @brief 检查类型是否正确，正确返回 true
	/// @param check_type_info 检查类型
	/// @return 适配当前类型返回 true
	static bool checkTypeInfo( const type_info &check_type_info ) { return false; }
	virtual ~I_Serialization‌( ) = default;
	/// @brief 增加一个序列化对象
	/// @param append_unity 真的序列化对象指针
	/// @return 无法序列化返回 false
	virtual bool appendVarType( const I_Type *append_unity ) = 0;
	/// @brief 删除一个序列化对象
	/// @param append_unity 删除的序列化对象指针
	/// @return 成功返回 true
	virtual bool removeVarType( const I_Type *append_unity ) = 0;
	/// @brief 获取指定下表的序列化对象指针
	/// @param index 下标
	/// @param result_unity 返回的指针
	/// @return 失败返回 false
	virtual bool get( const size_t &index, const I_Type *&result_unity ) const = 0;
	/// @brief 重置指定下表的序列化对象
	/// @param index 下标
	/// @param new_unity 新的序列化对象指针
	/// @return 失败返回 false
	virtual bool set( const size_t &index, const I_Type *new_unity ) = 0;
	/// @brief 获取二进制数据
	/// @param result_bin 返回的二进制数据
	/// @return 0 表示失败
	virtual size_t getBinVector( std_vector< uint8_t > &result_bin ) const = 0;
	/// @brief 配置二进制数据
	/// @param init_bin_data_ptr 配置的二进制数据
	/// @param init_bin_data_count
	/// @return 失败返回 0，成功返回使用数据数量
	virtual size_t setBinVector( const uint8_t *init_bin_data_ptr, const size_t &init_bin_data_count ) const = 0;
	/// @brief 根据字符串获取支持类型
	/// @param type_name 类型字符串名称
	/// @param result_type 返回的支持类型
	/// @return 不支持返回 false
	virtual bool getTypeInfo( const QString &type_name, I_Type *result_type ) const;
};

#endif // I_SERIALIZATION__H_H_HEAD__FILE__
