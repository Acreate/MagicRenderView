#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../varType/I_Type.h"

class I_Conver;
class VarGenerate : public QObject {
	Q_OBJECT;
protected:
	/// @brief 转换列表
	std_vector< std_shared_ptr< I_Conver > > converVector;
	/// @brief 堆栈列表
	std_vector< std_shared_ptr< I_Stack > > stackVector;
protected:
	/// @brief 追加一个赋值类型对象
	/// @param new_conver 对象指针
	virtual void appendConverInstance( const std_shared_ptr< I_Conver > &new_conver ) {
		converVector.emplace_back( new_conver );
	}
	/// @brief 追加一个赋值类型对象
	/// @param new_stack 对象指针
	virtual void appendConverInstance( const std_shared_ptr< I_Stack > &new_stack ) {
		stackVector.emplace_back( new_stack );
	}
public:
	~VarGenerate( ) override = default;
	/// @brief 类型转换赋值
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool conver( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right );

	/// @brief 类型加法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool add( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right );

	/// @brief 类型减法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	virtual bool sub( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right );

	/// @brief 类型乘法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	virtual bool mul( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right );

	/// @brief 类型除法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	virtual bool div( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right );

	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool );

	/// @brief 删除指针指针
	/// @param target_type_info 指向的类型
	/// @param target_ptr 删除的指针
	/// @return 成功删除返回 true
	virtual bool deleteTarget( const type_info &target_type_info, void *target_ptr );
	/// @brief 期望删除指针
	/// @param target_ptr 删除的指针
	/// @return 成功删除返回 true
	virtual bool deleteTarget( void *target_ptr );
	/// @brief 创建指针对象
	/// @param target_type_info 指向的类型
	/// @param create_call_function  创建的指针
	/// @return 成功创建返回 true，并且改变 target_ptr 指向，使其指向创建对象
	virtual bool createTarget( const type_info &target_type_info, const std_function< void( void *create_obj_ptr ) > &create_call_function );

	/// @brief 存储序列化
	/// @param target_type_info 序列化对象类型
	/// @param target_ptr 序列化对象指针
	/// @param result_vector 返回二进制数据
	/// @param result_count 二进制数据的量
	/// @return 成功序列化返回 true
	virtual bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count );

	/// @brief 加载序列化
	/// @param target_type_info 序列化当中实例化的对象类型
	/// @param target_ptr 序列化加载的返回指针
	/// @param result_count 使用数据量
	/// @param source_data_ptr 指向数据段的起始指针
	/// @param source_data_count 指向数据段的长度
	/// @return 成功使用数据返回 true
	virtual bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count );

	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_Conver *base_ptr ) {
			base_ptr = ptr;
		}
	void appendConverInstance( ) {
		appendConverInstance( std_shared_ptr< I_Conver >( new ttype ) );
	}

	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_Stack *base_ptr ) {
			base_ptr = ptr;
		}
	void appendStackInstance( ) {
		appendConverInstance( std_shared_ptr< I_Stack >( new ttype ) );
	}
};

#endif // VARGENERATE_H_H_HEAD__FILE__
