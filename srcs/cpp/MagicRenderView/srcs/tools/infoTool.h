#ifndef INFOTOOL_H_H_HEAD__FILE__
#define INFOTOOL_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

namespace infoTool {
	bool fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result );
	bool fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count );
	inline bool fillObjTarget( uint64_t &result_count, const void *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( uint8_t * ) ptr, ptr_size, result );
	}
	template< typename TSourceType >
	bool fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( const uint8_t * ) ptr, sizeof( TSourceType ) / sizeof( uint8_t ), result );
	}
	template< typename TSourceType >
	bool fillTypeVectorAtVar( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		return fillObjTarget( result_count, source_ptr, source_count, ( uint8_t * ) target_var_ptr, sizeof( TSourceType ) / sizeof( uint8_t ) );
	}
	template<>
	inline bool fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result ) {
		QString *stringPtr = ( QString * ) ptr;
		std::vector< uint8_t > buff;
		auto local8Bit = stringPtr->toUtf8( );
		auto converVar = local8Bit.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		char *data = local8Bit.data( );
		if( fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QString >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		QString *stringPtr = ( QString * ) target_var_ptr;
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		*stringPtr = QString::fromUtf8( ( const char * ) offset, result_count );
		result_count = result_count + sizeTypeCount;
		return result_count;
	}
}

#endif // INFOTOOL_H_H_HEAD__FILE__
