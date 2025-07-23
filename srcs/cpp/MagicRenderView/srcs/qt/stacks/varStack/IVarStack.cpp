#include "IVarStack.h"

#include "base/baseVarStack.h"
#include "base/baseVarStackEx.h"

#include "qt/types/baseType/nullTypeObject.h"

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

	return std_shared_ptr< ITypeObject >( new NullTypeObject( nullptr ) );
}
std_shared_ptr< ITypeObject > IVarStack::getStorageVar( const QString &storage_name ) const {
	auto iterator = storage.begin( );
	auto end = storage.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name )
			return iterator->first;
	return std_shared_ptr< ITypeObject >( new NullTypeObject( nullptr ) );
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

	return std_shared_ptr< ITypeObject >( new NullTypeObject( [] {
		return IVarStack::getInstance< BaseVarStackEx >( );
	} ) );
}
bool IVarStack::appendInstance( const std_shared_ptr< IVarStack > &append_unity ) {
	auto egName = append_unity->metaObject( )->className( );
	for( auto &ptr : instanceVector )
		if( ptr->metaObject( )->className( ) == egName )
			return false;
	instanceVector.emplace_back( append_unity );
	return true;
}
std_shared_ptr< IVarStack > IVarStack::getInstance( const QString &stack_name ) {
	if( stack_name == BaseVarStack::staticMetaObject.className( ) )
		return getInstance< BaseVarStack >( );
	else if( stack_name == BaseVarStackEx::staticMetaObject.className( ) )
		return getInstance< BaseVarStackEx >( );
	std_shared_ptr< IVarStack > instance;
	instance = getInstance< BaseVarStackEx >( );
	for( auto &name : instance->getStackTypeNames( ) )
		if( name == stack_name )
			return instance;
	instance = getInstance< BaseVarStack >( );
	for( auto &name : instance->getStackTypeNames( ) )
		if( name == stack_name )
			return instance;
	return nullptr;
}
IVarStack * IVarStack::getTUBPtrInstance( const QString &stack_name ) {
	if( stack_name == BaseVarStack::staticMetaObject.className( ) )
		return getTUBPtrInstance< BaseVarStack >( );
	else if( stack_name == BaseVarStackEx::staticMetaObject.className( ) )
		return getTUBPtrInstance< BaseVarStackEx >( );

	IVarStack *instance = getTUBPtrInstance< BaseVarStackEx >( );
	for( auto &name : instance->getStackTypeNames( ) )
		if( name == stack_name )
			return instance;
	instance = getTUBPtrInstance< BaseVarStack >( );
	for( auto &name : instance->getStackTypeNames( ) )
		if( name == stack_name )
			return instance;
	return nullptr;
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
