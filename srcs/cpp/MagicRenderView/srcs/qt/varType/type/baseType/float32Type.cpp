#include "float32Type.h"

Float32Type::Float32Type( ) : I_Stack( typeid( t_current_type ) ) {
	childcreateFunction = [] ( const type_info &target_type_info, const void *target_data_ptr, const size_t &target_data_count ) {
		auto p = new t_current_type( );
		return p;
	};
	childDeleteFunction = [] ( void *target_ptr ) {
		delete ( t_current_type * ) target_ptr;
		return true;
	};
}
bool Float32Type::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
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
bool Float32Type::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != generateTypeInfo )
		return false;
	size_t needCount = 0;
	size_t typeUseCount = sizeof( size_t );
	size_t count = fillObjVector( &needCount, typeUseCount, source_data_ptr, source_data_count );
	size_t mod = source_data_count - count;
	if( needCount > mod )
		return false;
	auto offerPtr = source_data_ptr + count;
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
