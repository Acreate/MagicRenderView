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
