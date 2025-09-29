#include "stdStringType.h"

#include <qt/generate/varGenerate.h>

bool StdStringType::createTarget( const type_info &target_type_info, const std_function< void( void *create_obj_ptr ) > &create_call_function ) {
	if( target_type_info != generateTypeInfo )
		return false;
	auto p = new t_current_type( );
	create_call_function( p );
	stackVarPtr.emplace_back( p );
	return true;
}
bool StdStringType::deleteTarget( const type_info &target_type_info, void *target_ptr ) {
	if( target_type_info != generateTypeInfo )
		return false;
	return deleteTarget( target_ptr );
}
bool StdStringType::deleteTarget( void *target_ptr ) {
	size_t count = stackVarPtr.size( );
	if( count == 0 )
		return false;
	auto data = stackVarPtr.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == target_ptr ) {
			delete ( t_current_type * ) data[ index ];
			stackVarPtr.erase( stackVarPtr.begin( ) + index );
			return true;
		}
	return false;
}
bool StdStringType::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) {
	if( target_type_info != generateTypeInfo )
		return false;
	// 转换到 qstring，使用 qstring 去实现
	QString buff = QString::fromStdString( *( std::string * ) target_ptr );

	return varGenerate->toBinVector( typeid( QString ), &buff, result_vector, result_count );
}
bool StdStringType::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	if( target_type_info != generateTypeInfo )
		return false;
	QString buff;
	bool oBjVector = varGenerate->toOBjVector( typeid( QString ), &buff, result_count, source_data_ptr, source_data_count );
	if( oBjVector == false )
		return false;
	*( std::string * ) target_ptr = buff.toStdString( );
	return true;
}
