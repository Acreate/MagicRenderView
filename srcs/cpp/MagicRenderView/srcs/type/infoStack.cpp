#include "infoStack.h"

#include "../app/application.h"

#include "../director/printerDirector.h"
InfoStack::InfoStack( ) {
	newObjTypeFunction = nullptr;
	deleteObjTypeFunction = nullptr;
}
InfoStack::~InfoStack( ) {

	if( deleteObjTypeFunction == nullptr ) {
		Application::getInstancePtr( )->getPrinterDirector( )->error( "未初始化创建函数表达式，请初始化 deleteObjTypeFunction 函数指向调用" );
	} else {
		size_t count = allVarPtrVector.size( );
		auto arrayPtr = allVarPtrVector.data( );
		for( size_t index = 0; index < count; ++index )
			if( nullptr != arrayPtr[ index ] )
				deleteObjTypeFunction( arrayPtr[ index ] );
			else
				break;
		allVarPtrVector.clear( );
	}

}
bool InfoStack::createTypePtr( void *&result_create_obj_ptr ) {
	if( newObjTypeFunction == nullptr ) {
		Application::getInstancePtr( )->getPrinterDirector( )->error( "未初始化创建函数表达式，请初始化 newObjTypeFunction 函数指向调用" );
		return false;
	}
	result_create_obj_ptr = newObjTypeFunction( );
	if( result_create_obj_ptr == nullptr )
		return false;
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] ) {
			arrayPtr[ index ] = result_create_obj_ptr;
			return arrayPtr[ index ];
		}
	allVarPtrVector.emplace_back( result_create_obj_ptr );
	return true;
}
bool InfoStack::deleteTypePtr( const void *delete_obj_ptr ) {
	if( deleteObjTypeFunction == nullptr ) {
		Application::getInstancePtr( )->getPrinterDirector( )->error( "未初始化创建函数表达式，请初始化 deleteObjTypeFunction 函数指向调用" );
		return false;
	}
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			if( deleteObjTypeFunction( arrayPtr[ index ] ) == false )
				return false;
			count -= 1;
			for( ; index < count; --count )
				if( nullptr == arrayPtr[ count ] ) {
					arrayPtr[ index ] = arrayPtr[ count ];
					return true;
				}
			return true;
		}
	return false;
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
	if( check_obj_ptr == nullptr )
		return false;
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count && arrayPtr[ index ] != nullptr; ++index )
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

bool InfoStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	auto result_count = allVarPtrVector.size( );
	if( result_count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	std::vector< uint8_t > buff;
	for( size_t index = 0; index < result_count; ++index )
		if( obj_start_ptr == arrayPtr[ index ] ) {
			if( toVectorData( arrayPtr[ index ], buff ) == false )
				return false;
			if( getTypeNameAtData( result_data ) == false )
				return false;
			result_data.append_range( buff );
			return true;
		}
	return false;
}
bool InfoStack::getTypeNameAtData( std::vector< uint8_t > &result_data ) {
	return fillTypeVarAtVector< QString >( &typeName, result_data );
}
bool InfoStack::getDataAtTypeName( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QString &result_type_name ) {
	uint64_t converVar = *( uint64_t * ) source_ptr;
	result_count = sizeof( uint64_t );
	size_t mod = source_count - result_count;
	if( mod < converVar )
		return false;
	auto offset = source_ptr + result_count;
	size_t newSize = converVar / ( sizeof( QChar ) / sizeof( uint8_t ) );
	result_type_name.resize( newSize );
	auto data = ( uint8_t * ) result_type_name.data( );
	size_t index = 0;
	for( ; index < converVar; ++index )
		data[ index ] = offset[ index ];
	result_count = converVar + result_count;
	return true;
}
bool InfoStack::fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
	result.resize( ptr_size );
	auto data = result.data( );
	for( size_t index = 0; index < ptr_size; ++index )
		data[ index ] = ptr[ index ];
	return true;
}
bool InfoStack::fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count ) {
	if( source_count < target_var_count )
		return false;
	for( size_t index = 0; index < target_var_count; ++index )
		target_var_ptr[ index ] = source_ptr[ index ];
	result_count = target_var_count;
	return true;
}
template<>
bool InfoStack::fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result ) {
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
bool InfoStack::fillTypeVectorAtVar< QString >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
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
