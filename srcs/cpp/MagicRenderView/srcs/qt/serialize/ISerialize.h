#ifndef ISERIALIZE_H_H_HEAD__FILE__
#define ISERIALIZE_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/tools/tools.h"

class ISerialize {
public:
	/// @brief 类型信息长度
	using type_size_t = uint64_t;
	/// @brief 序列化信息
	class SerializeInfo final {
		/// @brief 原始数据
		std_vector< uint8_t > data;
		/// @brief 从原始数据当中获取到的类型名称列表
		std_vector< QString > stackNames;
		/// @brief 从原始数据当中获取到的类型名称列表
		std_vector< QString > typeNames;
		/// @brief 从原始数据当中获取到的 qt 媒体类名
		std_vector< QString > metaObjectClassNames;
		/// @brief 从原始数据当中获取到的大小端标识
		uchar begEndian;
		/// @brief 从原始数据当中获取到的数据大小
		type_size_t size;
		/// @brief 从原始数据当中解析实现的结尾指针，该内容可能是真实的数据值
		size_t infoLastPtr;
		/// @brief 是否初始化成功
		bool isInitTrue;
	public:
		SerializeInfo( const uint8_t *data_ptr, const size_t &data_size );
		bool init( );
		const std_vector< uint8_t > & getData( ) const { return data; }
		const std_vector< QString > & getTypeNames( ) const { return typeNames; }
		const std_vector< QString > & getMetaObjectClassNames( ) const { return metaObjectClassNames; }
		uchar getBegEndian( ) const { return begEndian; }
		type_size_t getSize( ) const { return size; }
		const uint8_t * getInfoLastPtr( ) const { return infoLastPtr + data.data( ); }
		bool isIsInitTrue( ) const { return isInitTrue; }
		const std_vector< QString > & getStackNames( ) const { return stackNames; }

		/// @brief 从数据当中获取值
		/// @param data_ptr 数据起始位置
		/// @param data_size 数据大小
		/// @param result_is_beg_endian 返回的大小端
		/// @param result_stack_type_name 返回的堆栈名称
		/// @param result_qt_meta_names 返回的媒体类型名称
		/// @param result_obj_type_names 返回的对象类型名称
		/// @return 使用数据的量
		static type_size_t getSerializeInfo( const uint8_t *data_ptr, const size_t &data_size, uint8_t *result_is_beg_endian, std_vector< QString > *result_stack_type_name, std_vector< QString > *result_qt_meta_names, std_vector< QString > *result_obj_type_names );
	};
public:
	/// @brief 数据序列化到参数
	/// @param result_data_vector 返回被序列化后的数据
	/// @return 失败返回 false
	virtual bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const = 0;
	/// @brief 从数据当中获取信息，并且重新初始化对象
	/// @param read_data_vector 源数据序列
	/// @param data_count
	/// @return 使用数据的个数
	virtual size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) = 0;
	virtual ~ISerialize( ) { }
public:
	/// @brief 返回值 -1 则为转换数据的最后一个数据
	/// @brief 数据排列 : sizeof( uint8_t) /* (大小端标识) */ + sizeof( type_size_t ) /* (总体长度:大小端+type_size_t+QMetaObject+append_size) */ + sizeof(QMetaObject) /* (媒体对象) */ + append_size /* (追加的大小) */
	/// @brief 转换多媒体数据，并且返回追加元素的首要下标
	/// @param result_data 返回的数据序列
	/// @param meta_object_ptr 转化的多媒体对象指针
	/// @param stack_type_name 堆栈类型名称
	/// @param native_type_name 多媒体对象变量别名
	/// @param append_size 追加的大小
	/// @return 最后转换元素位置的下一个元素
	static uint8_t * converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const QStringList &stack_type_name, const QStringList &native_type_name, const size_t &append_size );
	/// @brief 返回值 -1 则为转换数据的最后一个数据
	/// @brief 数据排列 : sizeof( uint8_t) /* (大小端标识) */ + sizeof( type_size_t ) /* (总体长度:大小端+type_size_t+QMetaObject+append_size) */ + sizeof(QMetaObject) /* (媒体对象) */ + append_size /* (追加的大小) */
	/// @brief 转换多媒体数据，并且返回追加元素的首要下标
	/// @param result_data 返回的数据序列
	/// @param meta_object_ptr 转化的多媒体对象指针
	/// @param stack_type_name 堆栈类型名称
	/// @param native_type_name 多媒体对象变量别名
	/// @param append_size 追加的大小
	/// @return 最后转换元素位置的下一个元素
	static uint8_t * converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const std_vector< QString > &stack_type_name, const std_vector< QString > &native_type_name, const size_t &append_size );
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
	template< typename TUnity_Data_Type,
		typename = typename std::enable_if< std_is_same_base_var_type( TUnity_Data_Type ) > >
	static void converEndian( TUnity_Data_Type &ptr ) {
		converEndian( ( uint8_t * ) &ptr, sizeof( TUnity_Data_Type ) );
	}
	//#undef std_is_same
	//#undef std_is_same_base_var_type

};

#endif // ISERIALIZE_H_H_HEAD__FILE__
