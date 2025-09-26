#include "uInt64Type.h"
bool UInt64Type::createTarget( const type_info &target_type_info, const std_function< void( void *create_obj_ptr ) > &create_call_function ) {
	if( target_type_info != generateTypeInfo )
		return false;
	auto p = new t_current_type( );
	create_call_function( p );
	stackVarPtr.emplace_back( p );
	return true;
}
bool UInt64Type::deleteTarget( const type_info &target_type_info, void *target_ptr ) {
	if( target_type_info != generateTypeInfo )
		return false;
	return deleteTarget( target_ptr );
}
bool UInt64Type::deleteTarget( void *target_ptr ) {
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
bool UInt64Type::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) {
	if( target_type_info != generateTypeInfo )
		return false;

	std_vector< uint8_t > buff;
	std_vector< uint8_t > resultBuff;
	QString typeName = target_type_info.name( );
	size_t count = fillBinVector( typeName, resultBuff );
	count += fillBinVector( target_ptr, sizeof( t_current_type ), buff );
	resultBuff.append_range( buff );
	fillBinVector( &count, sizeof( size_t ), result_vector );
	result_vector.append_range( resultBuff );
	result_count = result_vector.size( );
	return true;
}
bool UInt64Type::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	if( target_type_info != generateTypeInfo )
		return false;
	size_t needCount = 0;
	size_t typeUseCount = sizeof( size_t );
	size_t count = fillObjVector( &needCount, typeUseCount, source_data_ptr, source_data_count );
	size_t mod = source_data_count - count;
	if( needCount > mod )
		return false;
	const uint8_t *offerPtr = source_data_ptr + count;
	QString typeName;
	count = fillObjVector( &typeName, offerPtr, mod );
	if( typeName != generateTypeInfo.name( ) )
		return false;
	offerPtr += count;
	mod -= count;
	offerPtr += fillObjVector( target_ptr, sizeof( t_current_type ), offerPtr, mod );
	result_count = offerPtr - source_data_ptr;
	return true;
}
