#ifndef ISERIALIZE_H_H_HEAD__FILE__
#define ISERIALIZE_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

class ISerialize {
protected:
	/// @brief 类型信息长度
	using type_size_t = uint64_t;
public:
	/// @brief 数据序列化到参数
	/// @param result_data_vector 返回被序列化后的数据
	/// @return 失败返回 false
	virtual bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
		return false;
	}
	/// @brief 从数据当中获取信息，并且重新初始化对象
	/// @param read_data_vector 源数据序列
	/// @param data_count
	/// @return 使用数据的个数
	virtual size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
		return 0;
	}
	virtual ~ISerialize( ) { }
public:
	/// @brief 是否大端
	/// @return 返回 true 表示大端
	static uint8_t isBegEndian( );

	/// @brief 大小端转换
	/// @param ptr 数据起始地址
	/// @param size 数据长度
	static void converEndian( uint8_t *ptr, uint64_t size );

	/// @brief 约束模版类型
	/// @param t_type_ 约束的模版类型参数
	/// @param same_type_ 定义模版参数的类型范围
#define std_is_same( t_type_, same_type_ ) std::is_same< t_type_, same_type_ >::value

	/// @brief 模版基本类型约束列表
	/// @param t_type_ 约束的模版类型参数
#define std_is_same_base_var_type( t_type_ ) \
		std_is_same( t_type_, int8_t ) \
		|| std_is_same( t_type_, int16_t ) \
		|| std_is_same( t_type_, int32_t ) \
		|| std_is_same( t_type_, int64_t ) \
		|| std_is_same( t_type_, uint8_t ) \
		|| std_is_same( t_type_, uint16_t ) \
		|| std_is_same( t_type_, uint32_t ) \
		|| std_is_same( t_type_, uint64_t ) \
		|| std_is_same( t_type_, float ) \
		|| std_is_same( t_type_, double )

	template< typename TUnity_Data_Type,
		typename = typename std::enable_if< std_is_same_base_var_type( TUnity_Data_Type ) > >
	static void toData( const TUnity_Data_Type &data, std_vector< uint8_t > *result_std_uint8_vector ) {
		auto dataSize = sizeof( TUnity_Data_Type );
		auto sourceDataPtr = ( uint8_t * ) &data;
		result_std_uint8_vector->resize( dataSize );
		auto targetDataPtr = result_std_uint8_vector->data( );
		for( size_t index = 0; index < dataSize; ++index )
			targetDataPtr[ index ] = sourceDataPtr[ index ];
	}
	template< typename TUnity_Data_Type,
		typename = typename std::enable_if< std_is_same_base_var_type( TUnity_Data_Type ) > >
	static std_vector< uint8_t > toData( const TUnity_Data_Type &data ) {
		std_vector< uint8_t > result;
		toData( data, &result );
		return result;
	}
	template< typename TUnity_Data_Type,
		typename = typename std::enable_if< std_is_same_base_var_type( TUnity_Data_Type ) > >
	static void converEndian( TUnity_Data_Type &ptr, uint64_t size ) {
		converEndian( ( uint8_t * ) &ptr, size );
	}
#undef std_is_same
#undef std_is_same_base_var_type

};

#endif // ISERIALIZE_H_H_HEAD__FILE__
