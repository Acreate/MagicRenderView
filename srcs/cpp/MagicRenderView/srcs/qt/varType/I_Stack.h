#ifndef I_STACK_H_H_HEAD__FILE__
#define I_STACK_H_H_HEAD__FILE__
#pragma once
#include <cstdint>

#include <alias/type_alias.h>

class VarGenerate;
class I_Stack {
	// 需要用到的变量列表
protected:
	/// @brief 类型
	const type_info &generateTypeInfo;
	/// @brief 变量生成器
	VarGenerate *varGenerate;
	/// @brief 存储生成的变量
	std_vector< void * > stackVarPtr;

	// 删除函数
public:
	I_Stack( const I_Stack &other ) = delete;
	I_Stack & operator=( const I_Stack &other ) = delete;

	// 构造与析构
public:
	I_Stack( const type_info &generate_type_info );
	virtual ~I_Stack( ) = default;

	// 虚函数
public:
	/// @brief 获取当前生成对象类型
	/// @return 对象类型
	virtual const type_info & getGenerateTypeInfo( ) const { return generateTypeInfo; }
	/// @brief 检查指针类型
	/// @param check_var_ptr 检查的指针
	/// @param result_type 返回类型
	/// @return 匹配成功返回 true
	virtual bool getPtrTypeInfo( const void *check_var_ptr, const type_info *&result_type ) const;
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
	/// @param create_call_function 创建的指针对象成功时，调用该函数
	/// @return 成功创建返回 true，并且调用 create_call_function，此时用户用变量保存值
	virtual bool createTarget( const type_info &target_type_info, const std_function< void( void *create_obj_ptr ) > &create_call_function ) { return false; }

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
	/// @param source_data_ptr
	/// @param source_data_count
	/// @return 成功使用数据返回 true
	virtual bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) { return false; }
protected:
	/// @brief 二进制填充数组
	/// @param source_data_ptr 获取源
	/// @param source_ptr_count 获取个数 
	/// @param result_mirror_image_bin_vector 填充目标
	/// @return 填充个数
	virtual size_t fillBinVector( const void *source_data_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) const;
	/// @brief 填充字符串到二进制数组当中
	/// @param var_type 字符串
	/// @param result_bin_data_vector 填充对象，填充期间会实现清空
	/// @return 填充个数
	virtual size_t fillBinVector( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) const;
	/// @brief 填充数据到目标
	/// @param target_var_ptr 目标指针
	/// @param target_need_count 需要个数
	/// @param source_data_ptr 源指针
	/// @param source_ptr_count 源个数
	/// @return 返回使用个数
	virtual size_t fillObjVector( void *target_var_ptr, const size_t &target_need_count, const uint8_t *source_data_ptr, const size_t &source_ptr_count ) const;
	/// @brief 填充到字符串
	/// @param target_var_ptr 目标字符串
	/// @param source_data_ptr 源指针
	/// @param source_ptr_count 源个数
	/// @return 使用个数
	virtual size_t fillObjVector( QString *target_var_ptr, const uint8_t *source_data_ptr, const size_t &source_ptr_count ) const;
};

#endif // I_STACK_H_H_HEAD__FILE__
