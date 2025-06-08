#include "IVarStack.h"

#include "qt/type/baseType/nullTypeObject.h"

std_vector< std_shared_ptr< IVarStack > > IVarStack::instanceVector;

std_shared_ptr< ITypeObject > IVarStack::setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) {
	auto iterator = storage.begin( );
	auto end = storage.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			std::shared_ptr< ITypeObject > typeObject = iterator->first;
			iterator->first = storage_obj;
			return typeObject;
		}

	return std_shared_ptr< ITypeObject >( new NullTypeObject( ) );
}
std_shared_ptr< ITypeObject > IVarStack::getStorageVar( const QString &storage_name ) const {
	auto iterator = storage.begin( );
	auto end = storage.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name )
			return iterator->first;
	return std_shared_ptr< ITypeObject >( new NullTypeObject( ) );
}
std_shared_ptr< ITypeObject > IVarStack::removeStorageVar( const QString &storage_name ) {
	auto iterator = storage.begin( );
	auto end = storage.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			std::shared_ptr< ITypeObject > typeObject = iterator->first;
			storage.erase( iterator );
			return typeObject;
		}

	return std_shared_ptr< ITypeObject >( new NullTypeObject( ) );
}