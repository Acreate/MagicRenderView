#include "baseVarStackEx.h"
#include <ranges>

#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"

BaseVarStackEx::BaseVarStackEx( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent ) : BaseVarStack( get_stack_function_get_function, parent ) {
	stackTypeNames.clear( );
	stackTypeNames.emplace_back( BaseVarStackEx::staticMetaObject.className( ) );
	generateInfosEx.emplace_back( std_pairt( std_vector< QString > { "file" }, [this]( )->ITypeObject * {
		auto lambda = []( ) {
			QMetaObject staticMetaObject = BaseVarStackEx::staticMetaObject;
			return IVarStack::getInstance( staticMetaObject.className( ) );
		};
		auto ptr = new CombinationTypeObject( lambda, { "file", CombinationTypeObject::staticMetaObject.className( ) } );
		std_shared_ptr< ITypeObject > path( BaseVarStack::newVar( "string" ) );
		std_shared_ptr< ITypeObject > bitSize( BaseVarStack::newVar( "int" ) );
		std_shared_ptr< ITypeObject > createTime( BaseVarStack::newVar( "int" ) );
		std_shared_ptr< ITypeObject > changeTime( BaseVarStack::newVar( "int" ) );
		ptr->setVarObject( path, "fileName" );
		ptr->setVarObject( bitSize, "bitSize" );
		ptr->setVarObject( createTime, "createTime" );
		ptr->setVarObject( changeTime, "changeTime" );
		return ptr;
	} ) );
}
ITypeObject * BaseVarStackEx::newVar( const QString &type_name ) const {
	for( auto &element : generateInfosEx ) {
		auto end = element.first.end( );
		auto result = std::find( element.first.begin( ), end, type_name );
		if( result != end )
			return element.second( );
	}

	return nullptr;
}
ITypeObject * BaseVarStackEx::_generateUBVar( const QString &type_name ) const {
	auto generateUbVar = BaseVarStack::_generateUBVar( type_name );
	if( generateUbVar == nullptr /* 使用该类的名称 */ )
		return BaseVarStackEx::newVar( type_name );
	return generateUbVar;
}
std_vector< std_pairt< QString, std_vector< QString > > > BaseVarStackEx::permissionVarType( ) const {
	std_vector< std_pairt< QString, std_vector< QString > > > result;
	for( auto key : generateInfos | std::views::keys )
		result.emplace_back( key );

	for( auto key : generateInfosEx | std::views::keys )
		result.emplace_back( key[ 0 ], key );
	return result;
}
