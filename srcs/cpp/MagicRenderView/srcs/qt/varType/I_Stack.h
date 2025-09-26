#ifndef I_STACK_H_H_HEAD__FILE__
#define I_STACK_H_H_HEAD__FILE__
#pragma once
#include <cstdint>

#include <alias/type_alias.h>

class VarGenerate;
class I_Stack {
protected:
	/// @brief 类型
	const type_info &generateTypeInfo;
	/// @brief 变量生成器
	VarGenerate *varGenerate;
	/// @brief 存储生成的变量
	std_vector< void * > stackVarPtr;
public:
	I_Stack( const type_info &generate_type_info );
	/// @brief 获取当前生成对象类型
	/// @return 对象类型
	virtual const type_info & getGenerateTypeInfo( ) const { return generateTypeInfo; }
	/// @brief 检查指针类型
	/// @param check_var_ptr 检查的指针
	/// @param result_type 返回类型
	/// @return 匹配成功返回 true
	virtual bool getPtrTypeInfo( const void *check_var_ptr, const type_info *&result_type ) const;
	virtual ~I_Stack( ) = default;
	/// @brief 删除指针指针
	/// @param target_type_info 指向的类型
	/// @param target_ptr 删除的指针
	/// @return 成功删除返回 true
	virtual bool deleteTarget( const type_info &target_type_info, void *target_ptr ) { return false; }
	/// @brief 期望删除指针
	/// @param target_ptr 删除的指针
	/// @return 成功删除返回 true
	virtual bool deleteTarget( void *target_ptr ) { return false; }
	/// @brief 创建指针对象
	/// @param target_type_info 指向的类型
	/// @param target_ptr 创建的指针
	/// @return 成功创建返回 true，并且改变 target_ptr 指向，使其指向创建对象
	virtual bool createTarget( const type_info &target_type_info, void *&target_ptr ) { return false; }
	/// @brief 存储序列化
	/// @param target_type_info 序列化对象类型
	/// @param target_ptr 序列化对象指针
	/// @param result_vector 返回二进制数据
	/// @param result_count 二进制数据的量
	/// @return 成功序列化返回 true
	virtual bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) { return false; }

	/// @brief 加载序列化
	/// @param target_type_info 序列化当中实例化的对象类型
	/// @param target_ptr 序列化加载的返回指针
	/// @param result_count 使用数据量
	/// @param load_bin_vector 加载的二进制数据
	/// @return 成功使用数据返回 true
	virtual bool toOBjVector( const type_info &target_type_info, void *&target_ptr, size_t &result_count, const std_vector< uint8_t > &load_bin_vector ) { return false; }

};

#endif // I_STACK_H_H_HEAD__FILE__
