#include "stdWStringType.h"

#include <qt/generate/varGenerate.h>

StdWStringType::StdWStringType( ) : I_Stack( typeid( t_current_type ) ) {
	createFunction = [this] {
		auto p = new t_current_type( );
		stackVarPtr->emplace_back( p );
		return p;
	};
	deleteFunction = [this] ( void *target_ptr ) {
		size_t count = stackVarPtr->size( );
		if( count == 0 )
			return false;
		auto data = stackVarPtr->data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == target_ptr ) {
				delete ( t_current_type * ) data[ index ];
				stackVarPtr->erase( stackVarPtr->begin( ) + index );
				return true;
			}
		return false;
	};
}
bool StdWStringType::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {

	if( target_type_info != generateTypeInfo )
		return false;
	// 转换到 qstring，使用 qstring 去实现
	QString buff = QString::fromStdWString( *( std::wstring * ) target_ptr );
	return varGenerate->toBinVector( typeid( QString ), &buff, result_vector, result_count );
}
bool StdWStringType::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != generateTypeInfo )
		return false;
	QString buff;
	bool oBjVector = varGenerate->toOBjVector( typeid( QString ), &buff, result_count, source_data_ptr, source_data_count );
	if( oBjVector == false )
		return false;
	*( std::wstring * ) target_ptr = buff.toStdWString( );
	return true;
}
