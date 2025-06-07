#include "baseStack.h"

#include <ranges>

#include "qt/type/baseType/dataTypeObject.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"
#include "qt/type/lineType/vectorTypeObject.h"

#define emplace_back_generateInfos( element_, type_, ...  )\
	element.first.first = type_::staticMetaObject.className( ) ;\
	element.first.second = {__VA_ARGS__ };\
	element_.second = [this]( ) -> ITypeObject * {\
		return  new type_( std_vector< QString >( {type_::staticMetaObject.className( ),__VA_ARGS__} )) ;\
	};\
	generateInfos.emplace_back( element )

BaseStack::BaseStack( QObject *parent ): IVarStack( parent ) {
	std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > element;

	element.first.first = IntTypeObject::staticMetaObject.className( );
	element.first.second = { "int" };
	element.second = [this]( ) ->ITypeObject * {
		auto intTypeObject = new IntTypeObject( );

		return intTypeObject;
	};
	generateInfos.emplace_back( element );
	emplace_back_generateInfos( element, IntTypeObject, "int" );
	emplace_back_generateInfos( element, FloatTypeObject, "float" );
	emplace_back_generateInfos( element, NullTypeObject, "nullptr" );
	emplace_back_generateInfos( element, DataTypeObject, "binary" );
	emplace_back_generateInfos( element, StringTypeObject, "string" );
	emplace_back_generateInfos( element, CombinationTypeObject, "struct" );
	emplace_back_generateInfos( element, VectorTypeObject, "array" );
	emplace_back_generateInfos( element, PairtTypeObject, "pairt" );
}
ITypeObject * BaseStack::newVar( const QString &type_name ) const {
	for( auto &element : generateInfos )
		if( element.first.first == type_name )
			return element.second( );
		else
			for( auto &name : element.first.second )
				if( name == type_name )
					return element.second( );
	return new NullTypeObject( );
}
ITypeObject * BaseStack::_generateUBVar( const QString &type_name ) const {
	return newVar( type_name );
}
std_shared_ptr< ITypeObject > BaseStack::generateVar( const QString &type_name ) const {
	return std_shared_ptr< ITypeObject >( _generateUBVar( type_name ) );
}
std_shared_ptr< ITypeObject > BaseStack::setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) {
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
std_shared_ptr< ITypeObject > BaseStack::getStorageVar( const QString &storage_name ) const {
	auto iterator = storage.begin( );
	auto end = storage.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name )
			return iterator->first;
	return std_shared_ptr< ITypeObject >( new NullTypeObject( ) );
}
std_shared_ptr< ITypeObject > BaseStack::removeStorageVar( const QString &storage_name ) {
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
std_vector< std_pairt< QString, std_vector< QString > > > BaseStack::permissionVarType( ) const {
	std_vector< std_pairt< QString, std_vector< QString > > > result;
	for( auto key : generateInfos | std::views::keys )
		result.emplace_back( key );
	return result;
}
