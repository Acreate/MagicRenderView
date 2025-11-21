#include "infoStack.h"
const void * InfoStack::createTypePtr( ) {
	if( createFunction == nullptr )
		return nullptr;
	auto resultPtr = createFunction( );
	if( resultPtr == nullptr )
		return nullptr;
	size_t count = stackVarPtr.size( );
	auto arrayPtr = stackVarPtr.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == nullptr ) {
			arrayPtr[ index ] = resultPtr;
			return resultPtr;
		}
	stackVarPtr.emplace_back( resultPtr );
	return resultPtr;
}
bool InfoStack::deleteTypePtr( const void *delete_obj_ptr ) {
	if( deleteFunction == nullptr )
		return false;
	size_t count = stackVarPtr.size( );
	auto arrayPtr = stackVarPtr.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == delete_obj_ptr ) {
			deleteFunction( arrayPtr[ index ] );
			arrayPtr[ index ] = nullptr;
			return true;
		}
	return false;
}
