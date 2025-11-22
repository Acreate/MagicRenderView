#include "infoStack.h"

InfoStack::~InfoStack( ) {
	auto iterator = stackVarPtr.begin( );
	auto end = stackVarPtr.end( );
	for( ; iterator != end; ++iterator )
		deleteTypePtr( *iterator );
	stackVarPtr.clear( );
}
void * InfoStack::createTypePtr( ) {
	if( createFunction == nullptr )
		return nullptr;
	auto resultPtr = createFunction( );
	if( resultPtr == nullptr )
		return nullptr;
	stackVarPtr.emplace_back( resultPtr );
	return resultPtr;
}
bool InfoStack::deleteTypePtr( const void *delete_obj_ptr ) {
	if( deleteFunction == nullptr )
		return false;
	auto iterator = stackVarPtr.begin( );
	auto end = stackVarPtr.end( );
	for( ; iterator != end; ++iterator )
		if( *iterator == delete_obj_ptr ) {
			deleteFunction( *iterator );
			stackVarPtr.erase( iterator );
			return true;
		}
	return false;
}
bool InfoStack::isType( const QString &check_type_name ) {
	if( check_type_name == typeName )
		return true;
	size_t count = aliasTypeNames.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = aliasTypeNames.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == check_type_name )
			return true;
	return false;
}
bool InfoStack::isAliasTypeNames( const QString &check_type_name ) {
	size_t count = aliasTypeNames.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = aliasTypeNames.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == check_type_name )
			return true;
	return false;
}
bool InfoStack::hasVarPtr( const void *check_obj_ptr ) {
	auto iterator = stackVarPtr.begin( );
	auto end = stackVarPtr.end( );
	for( ; iterator != end; ++iterator )
		if( *iterator == check_obj_ptr )
			return true;
	return false;
}
