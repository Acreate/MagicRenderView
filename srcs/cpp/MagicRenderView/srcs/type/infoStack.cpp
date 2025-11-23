#include "infoStack.h"

InfoStack::~InfoStack( ) {
}
bool InfoStack::isTypeName( const QString &check_type_name ) const {
	return check_type_name == typeName;
}
bool InfoStack::isAliasTypeNames( const QString &check_type_name ) const {
	size_t count = aliasTypeNames.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = aliasTypeNames.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == check_type_name )
			return true;
	return false;
}
bool InfoStack::hasVarPtr( const void *check_obj_ptr ) const {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == check_obj_ptr )
			return true;
	return false;
}
uint64_t InfoStack::size( ) const {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return 0;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == nullptr )
			return index + 1;
	return count;
}
void * const* InfoStack::arrayPtr( ) const {
	return allVarPtrVector.data( );
}
void ** InfoStack::arrayPtr( ) {
	return allVarPtrVector.data( );
}
uint64_t InfoStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return 0;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( obj_start_ptr == arrayPtr[ index ] )
			return toVectorData( arrayPtr[ index ], result_data );
	return 0;
}
uint64_t InfoStack::getTypeNameAtData( std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	qint64 count = typeName.size( );
	if( count <= 0 )
		return 0;
	uint64_t converVar = count;
	if( converVar != count )
		return 0;
	converVar *= sizeof( QChar ) / sizeof( uint8_t );
	if( fillTypeVarAtVector< uint64_t >( &converVar, result_data ) == 0 )
		return 0;
	QChar *data = typeName.data( );
	if( toVector( data, converVar, buff ) == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
uint64_t InfoStack::getDataAtTypeName( const uint8_t *source_ptr, const size_t &source_count, QString &result_type_name ) {
	uint64_t converVar = *( uint64_t * ) source_ptr;
	size_t sizeTypeCount = sizeof( uint64_t );
	size_t mod = source_count - sizeTypeCount;
	if( mod < converVar )
		return 0;
	auto offset = source_ptr + sizeTypeCount;
	size_t newSize = converVar / ( sizeof( QChar ) / sizeof( uint8_t ) );
	result_type_name.resize( newSize );
	auto data = ( uint8_t * ) result_type_name.data( );
	size_t index = 0;
	for( ; index < converVar; ++index )
		data[ index ] = offset[ index ];
	return converVar + sizeTypeCount;
}
uint64_t InfoStack::toVector( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
	result.resize( ptr_size );
	auto data = result.data( );
	for( size_t index = 0; index < ptr_size; ++index )
		data[ index ] = ptr[ index ];
	return ptr_size;
}
uint64_t InfoStack::toVar( const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count ) {
	if( source_count < target_var_count )
		return 0;
	for( size_t index = 0; index < target_var_count; ++index )
		target_var_ptr[ index ] = source_ptr[ index ];
	return target_var_count;
}
template<>
uint64_t InfoStack::fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result ) {
	QString *stringPtr = ( QString * ) ptr;
	std::vector< uint8_t > buff;
	qint64 count = stringPtr->size( );
	uint64_t converVar = count;
	if( converVar != count )
		return 0;
	converVar *= sizeof( QChar ) / sizeof( uint8_t );
	if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == 0 )
		return 0;
	if( converVar == 0 )
		return result.size( );
	QChar *data = stringPtr->data( );
	if( toVector( data, converVar, buff ) == 0 )
		return 0;
	result.append_range( buff );
	return result.size( );
}
template<>
uint64_t InfoStack::fillTypeVectorAtVar< QString >( const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
	QString *stringPtr = ( QString * ) target_var_ptr;
	uint64_t converVar = *( uint64_t * ) source_ptr;
	size_t sizeTypeCount = sizeof( uint64_t );
	if( converVar == 0 ) // 字符串为空时，直接返回长度匹配大小
		return sizeTypeCount;
	size_t mod = source_count - sizeTypeCount;
	if( mod < converVar )
		return 0;
	auto offset = source_ptr + sizeTypeCount;
	size_t newSize = converVar / ( sizeof( QChar ) / sizeof( uint8_t ) );
	stringPtr->resize( newSize );
	auto data = ( uint8_t * ) stringPtr->data( );
	size_t index = 0;
	for( ; index < converVar; ++index )
		data[ index ] = offset[ index ];
	return converVar + sizeTypeCount;
}
bool operator==( const InfoStack &lhs, const InfoStack &rhs ) {
	if( lhs.typeName == rhs.typeName )
		return true;
	size_t rightCount = rhs.aliasTypeNames.size( );
	size_t leftCount = lhs.aliasTypeNames.size( );

	auto rightArratPtr = rhs.aliasTypeNames.data( );
	auto leftArratPtr = lhs.aliasTypeNames.data( );
	size_t rightIndex = 0;
	for( ; rightIndex < rightCount; ++rightIndex )
		if( lhs.typeName == rightArratPtr[ rightIndex ] )
			return true;
	size_t leftIndex = 0;
	for( ; leftIndex < leftCount; ++leftIndex )
		if( rhs.typeName == leftArratPtr[ leftIndex ] )
			return true;
	if( leftCount == 0 || rightCount == 0 )
		return false;
	for( rightIndex = 0; rightIndex < rightCount; ++rightIndex )
		for( leftIndex = 0; leftIndex < leftCount; ++leftIndex )
			if( rightArratPtr[ rightIndex ] == leftArratPtr[ leftIndex ] )
				return true;
	return false;
}
