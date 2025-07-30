#include "IVarStack.h"

#include "../../application/application.h"

#include "base/baseVarStack.h"

#include "qt/types/baseType/nullTypeObject.h"

std_shared_ptr< ITypeObject > IVarStack::setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) const {
	auto iterator = storage->begin( );
	auto end = storage->end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			std::shared_ptr< ITypeObject > typeObject = iterator->first;
			iterator->first = storage_obj;
			return typeObject;
		}
	storage->emplace_back( storage_obj, storage_name );
	return std_shared_ptr< ITypeObject >( new NullTypeObject( nullptr ) );
}
std_shared_ptr< ITypeObject > IVarStack::getStorageVar( const QString &storage_name ) const {
	auto iterator = storage->begin( );
	auto end = storage->end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name )
			return iterator->first;
	return std_shared_ptr< ITypeObject >( new NullTypeObject( nullptr ) );
}
std_shared_ptr< ITypeObject > IVarStack::removeStorageVar( const QString &storage_name ) {
	auto iterator = storage->begin( );
	auto end = storage->end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			std::shared_ptr< ITypeObject > typeObject = iterator->first;
			storage->erase( iterator );
			return typeObject;
		}

	return std_shared_ptr< ITypeObject >( new NullTypeObject( this ) );
}
bool IVarStack::init( ) {
	auto applicationInstancePtr = Application::getApplicationInstancePtr( );
	applicationInstancePtr->appendVarStacks< BaseVarStack >( );
	return true;
}
ITypeObject * IVarStack::generateUbVar( const QString &type_name, QObject *parnet ) const {
	ITypeObject *typeObject = _generateUBVar( type_name );
	if( typeObject )
		if( parnet ) {
			typeObject->setParent( parnet );
			return typeObject;
		} else
			return typeObject;
	return nullptr;
}
