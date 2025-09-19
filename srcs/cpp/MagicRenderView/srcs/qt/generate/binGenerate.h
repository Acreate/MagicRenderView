#ifndef BINGENERATE_H_H_HEAD__FILE__
#define BINGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

class BinGenerate final {

public:
	/// @brief 获取数据当中的类名称信息{内名称信息长度(size_t 类型),类名称信息内容(QByteArray 类型-utf8编码)}
	/// @param result_type_info 类名称信息
	/// @param source_data_ptr 源
	/// @param source_count 源数据上限
	/// @return 数据使用量
	static size_t getMetaInfo( QString *result_type_info, const uint8_t *source_data_ptr, const size_t &source_count ) {
		size_t metaCount = *( size_t * ) source_data_ptr;
		size_t sizeSize = sizeof( size_t );
		source_data_ptr += sizeSize;
		toObj( result_type_info, source_data_ptr, metaCount );
		return metaCount + sizeSize;
	}
	/// @brief 类型转换到元信息
	/// @tparam TType 类型
	/// @param set_vector 返回二进制 
	/// @return 转换个数
	template< typename TType >
	static size_t setMetaInfo( std_vector< uint8_t > &set_vector ) {
		QString typeInfo = typeid( TType ).name( );
		std_vector< uint8_t > typeNameVector;
		toVectorUInt8Data( typeInfo, typeNameVector );
		size_t count = typeNameVector.size( );
		std_vector< uint8_t > countVector;
		toVectorUInt8Data( count, countVector );
		set_vector.clear( );
		set_vector.append_range( countVector );
		set_vector.append_range( typeNameVector );
		return set_vector.size( );
	}
	/// @brief 平台是否小端
	/// @return true 表示小端
	static bool isLittleEndian( ) {
		union {
			int i;
			char c;
		} un;	// 匿名联合体
		un.i = 1;
		// 小端：返回 1，说明数据的低字节在内存的低地址存放
		return un.c == 1;
	}
	static size_t toVectorUInt8Data( const void *source_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		result_mirror_image_bin_vector.resize( source_ptr_count );
		auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
		auto copyTargetDataPtr = ( const uint8_t * ) source_ptr;
		for( size_t index = 0; index < source_ptr_count; ++index )
			pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
		return source_ptr_count;
	}

	static size_t toVectorUInt8Data( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		auto byteArray = var_type.toUtf8( );
		return toVectorUInt8Data( byteArray.data( ), byteArray.size( ), result_bin_data_vector );
	}
	static size_t toVectorUInt8Data( const uint8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof uint8_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const uint16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof uint16_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const uint32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof uint32_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const uint64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof uint64_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const float_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof float_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const double_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( &var_type, sizeof double_t, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const std::string &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		QString fromStdString = QString::fromStdString( var_type );
		return toVectorUInt8Data( fromStdString, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const std::wstring &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		QString fromStdString = QString::fromStdWString( var_type );
		return toVectorUInt8Data( fromStdString, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const int8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( ( uint8_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const int16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( ( const uint16_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const int32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( ( const uint32_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t toVectorUInt8Data( const int64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return toVectorUInt8Data( ( const uint64_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t toObj( QString *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		const char *sourcePtr = ( const char * ) source_ptr;
		QByteArray array( sourcePtr, source_ptr_count );
		*target_var_ptr = QString::fromUtf8( array );
		return source_ptr_count;
	}
	static size_t toObj( uint8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint8_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( uint16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint16_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( uint32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint32_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( uint64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint64_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( float_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( float_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( double_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( double_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}

	static size_t toObj( std::string *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		QString buff;
		auto count = toObj( &buff, source_ptr, source_ptr_count );
		if( count == 0 )
			return 0;
		*target_var_ptr = buff.toStdString( );
		return count;
	}

	static size_t toObj( std::wstring *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		QString buff;
		auto count = toObj( &buff, source_ptr, source_ptr_count );
		if( count == 0 )
			return 0;
		*target_var_ptr = buff.toStdWString( );
		return count;
	}
	static size_t toObj( int8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int8_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( int16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int16_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( int32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int32_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t toObj( int64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int64_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}

	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toVectorBin( const TBaseType &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		/*
		 * 对象类型信息
		 */
		QString typeName = typeid( TBaseType ).name( );
		std_vector< uint8_t > typeNameVector;
		size_t dataCount = BinGenerate::toVectorUInt8Data( typeName, typeNameVector );
		std_vector< uint8_t > typeNameVectorCountVector;
		BinGenerate::toVectorUInt8Data( dataCount, typeNameVectorCountVector );
		/*
		 * 对象存储信息
		 */
		std_vector< uint8_t > varDataVector;
		dataCount = BinGenerate::toVectorUInt8Data( var_type, varDataVector );
		std_vector< uint8_t > varDataVectorCountVector;
		BinGenerate::toVectorUInt8Data( dataCount, varDataVectorCountVector );
		/*
		 * 总长度 = 对象类型信息长度+对象存储信息长度
		 */
		dataCount = typeNameVectorCountVector.size( ) + typeNameVector.size( ) + varDataVectorCountVector.size( ) + varDataVector.size( );
		std_vector< uint8_t > dataCountVector;
		BinGenerate::toVectorUInt8Data( dataCount, dataCountVector );
		/*
		* 存储到返回
		*/
		result_bin_data_vector.clear( );
		// 总长
		result_bin_data_vector.append_range( dataCountVector );
		// 变量类型信息长度
		result_bin_data_vector.append_range( typeNameVectorCountVector );
		// 变量类型信息内容
		result_bin_data_vector.append_range( typeNameVector );
		// 变量存储信息长度
		result_bin_data_vector.append_range( varDataVectorCountVector );
		// 变量存储信息内容
		result_bin_data_vector.append_range( varDataVector );
		return true;
	}

	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t fillObjPtr( TBaseType *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		/*
		 * 总数量
		 */
		// 从数据当中获取长度
		size_t minCount = *( size_t * ) source_data_ptr;
		// 长度数据的占用
		size_t size_tTypeSize = sizeof( size_t );
		if( source_data_count < size_tTypeSize )
			return 0;
		// 有效大小
		size_t validSourceDataCount = source_data_count - size_tTypeSize;
		if( minCount > validSourceDataCount )
			return 0;// 无法满足数据需求
		// 移动到对象类型信息起始位置
		source_data_ptr += size_tTypeSize;
		/*
		 * 校对对象类型信息
		 */
		// 获取对象类型信息长度
		size_t typeNameSize = *( size_t * ) source_data_ptr;
		// 指向类型信息起始位置
		source_data_ptr += size_tTypeSize;
		QByteArray array( ( const char * ) source_data_ptr, typeNameSize );
		QString typeName = QString::fromUtf8( array );
		// 获取参数当中的类型
		QString paramTypeName = typeid( TBaseType ).name( );
		if( paramTypeName != typeName )
			return 0; // 类型名称不匹配
		// 指向对象存储信息
		source_data_ptr += typeNameSize;
		/*
		 * 校对对象存储信息
		 */
		validSourceDataCount = *( size_t * ) source_data_ptr;
		source_data_ptr += size_tTypeSize;
		BinGenerate::toObj( var_type, source_data_ptr, validSourceDataCount );

		return minCount;
	}
	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toVectorBin( const std_vector< TVectorIteratorType > &obj, std_vector< uint8_t > &result_bin ) {

		std_vector< uint8_t > resultBinBuff;
		QString typeName = typeid( std_vector< TVectorIteratorType > ).name( );
		std_vector< uint8_t > nameBin;
		BinGenerate::toVectorUInt8Data( typeName, nameBin );
		std_vector< uint8_t > nameCountBin;
		BinGenerate::toVectorUInt8Data( nameBin.size( ), nameCountBin );
		resultBinBuff.append_range( nameCountBin );
		resultBinBuff.append_range( nameBin );
		auto count = obj.size( );
		BinGenerate::toVectorUInt8Data( count, nameCountBin );
		resultBinBuff.append_range( nameCountBin );
		size_t index = 0;
		auto data = obj.data( );
		for( ; index < count; ++index ) {
			BinGenerate::toVectorUInt8Data( data[ index ], nameBin );
			nameCountBin.clear( );
			BinGenerate::toVectorUInt8Data( nameBin.size( ), nameCountBin );
			resultBinBuff.append_range( nameCountBin );
			resultBinBuff.append_range( nameBin );
		}

		BinGenerate::toVectorUInt8Data( resultBinBuff.size( ), nameCountBin );
		result_bin.clear( );
		result_bin.append_range( nameCountBin );
		result_bin.append_range( resultBinBuff );
		return result_bin.size( );
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t fillObjPtr( std_vector< TVectorIteratorType > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		size_t minCount = *( size_t * ) source_data_ptr;
		size_t size_tTypeSize = sizeof( size_t );
		if( source_data_count < size_tTypeSize )
			return 0;
		size_t validSourceDataCount = source_data_count - size_tTypeSize;
		if( minCount > validSourceDataCount )
			return 0;
		source_data_ptr += size_tTypeSize;

		std_vector< uint8_t > resultBinBuff;
		QString typeName = typeid( std_vector< TVectorIteratorType > ).name( );
		std_vector< uint8_t > nameBin;
		BinGenerate::toVectorUInt8Data( typeName, nameBin );
		std_vector< uint8_t > nameCountBin;
		size_t count = nameBin.size( ), index = 0;
		BinGenerate::toVectorUInt8Data( count, nameCountBin );
		resultBinBuff.append_range( nameCountBin );
		resultBinBuff.append_range( nameBin );
		count = resultBinBuff.size( );
		auto data = resultBinBuff.data( );
		for( ; index < count; ++index )
			if( data[ index ] != source_data_ptr[ index ] )
				return 0;
		source_data_ptr = source_data_ptr + count;
		count = *( size_t * ) source_data_ptr;
		source_data_ptr += size_tTypeSize;
		var_type->resize( count );
		auto pastDataPtr = var_type->data( );
		for( index = 0; index < count; ++index ) {
			TVectorIteratorType var;
			validSourceDataCount = *( size_t * ) source_data_ptr;
			source_data_ptr += size_tTypeSize;
			BinGenerate::toObj( &var, source_data_ptr, validSourceDataCount );
			pastDataPtr[ index ] = var;
			source_data_ptr += validSourceDataCount;
		}
		return minCount;
	}

};

#endif // BINGENERATE_H_H_HEAD__FILE__
