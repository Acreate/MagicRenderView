#ifndef BINGENERATE_H_H_HEAD__FILE__
#define BINGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../tools/tools.h"

class BinGenerate final {

public:
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
protected:
	static size_t fillBin( const void *source_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		result_mirror_image_bin_vector.resize( source_ptr_count );
		auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
		auto copyTargetDataPtr = ( const uint8_t * ) source_ptr;
		for( size_t index = 0; index < source_ptr_count; ++index )
			pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
		return source_ptr_count;
	}

	static size_t fillBin( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		std_vector< uint8_t > buff;
		auto byteArray = var_type.toUtf8( );
		fillBin( byteArray.data( ), byteArray.size( ), buff );
		fillBin( buff.size( ), result_bin_data_vector );
		result_bin_data_vector.append_range( buff );
		return result_bin_data_vector.size( );
	}
	static size_t fillBin( const uint8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof uint8_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const uint16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof uint16_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const uint32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof uint32_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const uint64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof uint64_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const float_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof float_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const double_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( &var_type, sizeof double_t, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const std::string &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		QString fromStdString = QString::fromStdString( var_type );
		return fillBin( fromStdString, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const std::wstring &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		QString fromStdString = QString::fromStdWString( var_type );
		return fillBin( fromStdString, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const int8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( ( uint8_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const int16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( ( const uint16_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const int32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( ( const uint32_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t fillBin( const int64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
		return fillBin( ( const uint64_t ) var_type, result_mirror_image_bin_vector );
	}
	static size_t fillObj( QString *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t count;
		auto add = fillObj( &count, source_ptr, source_ptr_count );
		const char *sourcePtr = ( const char * ) source_ptr + add;
		if( count > source_ptr_count - add )
			return 0;
		QByteArray array( sourcePtr, count );
		*target_var_ptr = QString::fromUtf8( array );
		return count + add;
	}
	static size_t fillObj( uint8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint8_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( uint16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint16_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( uint32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint32_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( uint64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( uint64_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( float_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( float_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( double_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( double_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}

	static size_t fillObj( std::string *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		QString buff;
		auto count = fillObj( &buff, source_ptr, source_ptr_count );
		if( count == 0 )
			return 0;
		*target_var_ptr = buff.toStdString( );
		return count;
	}

	static size_t fillObj( std::wstring *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		QString buff;
		auto count = fillObj( &buff, source_ptr, source_ptr_count );
		if( count == 0 )
			return 0;
		*target_var_ptr = buff.toStdWString( );
		return count;
	}
	static size_t fillObj( int8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int8_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( int16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int16_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( int32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int32_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
	static size_t fillObj( int64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
		size_t checkCount = sizeof( int64_t );
		if( checkCount > source_ptr_count )
			return 0;
		memcpy( target_var_ptr, source_ptr, checkCount );
		return checkCount;
	}
public:
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toBin( const TBaseType &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		/*
		 * 对象类型信息
		 */
		std_vector< uint8_t > typeNameVector;
		QString typeName = typeid( TBaseType ).name( );
		BinGenerate::fillBin( typeName, typeNameVector );
		/*
		 * 对象存储信息
		 */
		std_vector< uint8_t > varDataVector;
		BinGenerate::fillBin( var_type, varDataVector );
		std_vector< uint8_t > varDataVectorCountVector;
		BinGenerate::fillBin( varDataVector.size( ), varDataVectorCountVector );
		/*
		 * 总长度 = 对象类型信息长度+对象存储信息长度
		 */
		std_vector< uint8_t > dataCountVector;
		BinGenerate::fillBin( typeNameVector.size( ) + varDataVectorCountVector.size( ) + varDataVector.size( ), dataCountVector );
		/*
		* 存储到返回
		*/
		result_bin_data_vector.clear( );
		// 总长
		result_bin_data_vector.append_range( dataCountVector );
		// 变量类型信息内容
		result_bin_data_vector.append_range( typeNameVector );
		// 变量存储信息长度
		result_bin_data_vector.append_range( varDataVectorCountVector );
		// 变量存储信息内容
		result_bin_data_vector.append_range( varDataVector );
		return result_bin_data_vector.size( );
	}

	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType > &obj, std_vector< uint8_t > &result_bin ) {

		std_vector< uint8_t > resultBinBuff;
		std_vector< uint8_t > nameBin;
		std_vector< uint8_t > nameCountBin;

		QString typeName = typeid( std_vector< TVectorIteratorType > ).name( );
		BinGenerate::fillBin( typeName, nameBin );

		resultBinBuff.append_range( nameBin );
		auto count = obj.size( );
		BinGenerate::fillBin( count, nameBin );
		resultBinBuff.append_range( nameBin );
		size_t index = 0;
		auto data = obj.data( );
		for( ; index < count; ++index ) {
			BinGenerate::toBin( data[ index ], nameBin );
			resultBinBuff.append_range( nameBin );
		}

		BinGenerate::fillBin( resultBinBuff.size( ), nameCountBin );
		result_bin.clear( );
		result_bin.append_range( nameCountBin );
		result_bin.append_range( resultBinBuff );
		return result_bin.size( );
	}
	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType * > &obj, std_vector< uint8_t > &result_bin ) {

		std_vector< uint8_t > resultBinBuff;
		std_vector< uint8_t > nameBin;
		std_vector< uint8_t > nameCountBin;

		QString typeName = typeid( std_vector< TVectorIteratorType > ).name( );
		BinGenerate::fillBin( typeName, nameBin );

		resultBinBuff.append_range( nameBin );
		auto count = obj.size( );
		BinGenerate::fillBin( count, nameCountBin );
		resultBinBuff.append_range( nameCountBin );
		size_t index = 0;
		auto data = obj.data( );
		for( ; index < count; ++index ) {
			BinGenerate::toBin( *data[ index ], nameBin );
			resultBinBuff.append_range( nameBin );
		}

		BinGenerate::fillBin( resultBinBuff.size( ), nameCountBin );
		result_bin.clear( );
		result_bin.append_range( nameCountBin );
		result_bin.append_range( resultBinBuff );
		return result_bin.size( );
	}
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toObj( TBaseType *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		/*
		 * 总数量
		 */
		// 从数据当中获取长度
		size_t minCount;
		auto offsetPtr = source_data_ptr + BinGenerate::fillObj( &minCount, source_data_ptr, source_data_count );
		size_t validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		if( minCount > validSourceDataCount ) {
			tools::debug::printError( "需求存储元素数量不匹配" );
			return 0;// 无法满足数据需求
		}

		/*
		 * 校对对象类型信息
		 */
		// 获取对象类型信息长度
		QString typeName;
		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		offsetPtr += BinGenerate::fillObj( &typeName, offsetPtr, validSourceDataCount );

		// 获取参数当中的类型
		QString paramTypeName = typeid( TBaseType ).name( );
		if( paramTypeName != typeName ) {
			tools::debug::printError( "类型名称不匹配" );
			return 0; // 类型名称不匹配
		}
		/*
		 * 校对对象存储信息
		 */
		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		offsetPtr += BinGenerate::fillObj( &validSourceDataCount, offsetPtr, validSourceDataCount );
		offsetPtr += BinGenerate::fillObj( var_type, offsetPtr, validSourceDataCount );
		return offsetPtr - source_data_ptr;
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		size_t minCount = *( size_t * ) source_data_ptr;

		auto offsetPtr = BinGenerate::fillObj( &minCount, source_data_ptr, source_data_count ) + source_data_ptr;

		size_t validSourceDataCount = source_data_count - ( offsetPtr - source_data_ptr );
		if( minCount > validSourceDataCount ) {
			tools::debug::printError( "需求存储元素数量不匹配" );
			return 0;// 无法满足数据需求
		}
		std_vector< uint8_t > resultBinBuff;
		QString typeName = typeid( std_vector< TVectorIteratorType > ).name( );

		QString loadTypeName;
		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		offsetPtr += BinGenerate::fillObj( &loadTypeName, offsetPtr, validSourceDataCount );
		if( loadTypeName != typeName ) {
			tools::debug::printError( "类型名称不匹配" );
			return 0;
		}

		size_t count;
		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		offsetPtr += BinGenerate::fillObj( &count, offsetPtr, validSourceDataCount );

		var_type->resize( count );
		auto pastDataPtr = var_type->data( );
		for( size_t index = 0; index < count; ++index ) {
			TVectorIteratorType var;
			validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
			offsetPtr += BinGenerate::toObj( &var, offsetPtr, validSourceDataCount );
			pastDataPtr[ index ] = var;
		}
		return offsetPtr - source_data_ptr;
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType * > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		size_t minCount;
		auto offsetPtr = BinGenerate::fillObj( &minCount, source_data_ptr, source_data_count ) + source_data_ptr;

		size_t validSourceDataCount = source_data_count - ( offsetPtr - source_data_ptr );
		if( minCount > validSourceDataCount ) {
			tools::debug::printError( "需求存储元素数量不匹配" );
			return 0;// 无法满足数据需求
		}

		QString typeName = typeid( std_vector< TVectorIteratorType * > ).name( );
		QString loadTypeName;
		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		offsetPtr += BinGenerate::fillObj( &loadTypeName, offsetPtr, validSourceDataCount );
		if( loadTypeName != typeName ) {
			tools::debug::printError( "类型名称不匹配" );
			return 0;
		}

		validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
		size_t count;
		offsetPtr += BinGenerate::fillObj( &count, offsetPtr, validSourceDataCount );
		var_type->resize( count );
		auto pastDataPtr = var_type->data( );
		for( size_t index = 0; index < count; ++index ) {
			TVectorIteratorType *var = new TVectorIteratorType( );
			validSourceDataCount = source_data_count - ( source_data_ptr - offsetPtr );
			offsetPtr += BinGenerate::toObj( var, offsetPtr, validSourceDataCount );
			pastDataPtr[ index ] = var;
		}
		return offsetPtr - source_data_ptr;
	}
};

#endif // BINGENERATE_H_H_HEAD__FILE__
