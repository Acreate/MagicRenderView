#include "baseStackEx.h"
#include <ranges>

#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"

BaseStackEx::BaseStackEx( ) {
	generateInfosEx.emplace_back( std_pairt( std_vector< QString > { "file" }, [this]( )->ITypeObject * {
		auto ptr = new CombinationTypeObject( { "file" } );
		std_shared_ptr< ITypeObject > path( BaseStack::newVar( "string" ) );
		std_shared_ptr< ITypeObject > bitSize( BaseStack::newVar( "int" ) );
		std_shared_ptr< ITypeObject > createTime( BaseStack::newVar( "int" ) );
		std_shared_ptr< ITypeObject > changeTime( BaseStack::newVar( "int" ) );
		ptr->setVarObject( path, "fileName" );
		ptr->setVarObject( bitSize, "bitSize" );
		ptr->setVarObject( createTime, "createTime" );
		ptr->setVarObject( changeTime, "changeTime" );
		return ptr;
	} ) );
}
ITypeObject * BaseStackEx::_generateUBVar( const QString &type_name ) const {
	auto generateUbVar = BaseStack::_generateUBVar( type_name );
	if( generateUbVar == nullptr /* 使用该类的名称 */ ) {
	}
	return generateUbVar;
}
std_vector< std_pairt< QString, std_vector< QString > > > BaseStackEx::permissionVarType( ) const {
	std_vector< std_pairt< QString, std_vector< QString > > > result;
	for( auto key : generateInfos | std::views::keys )
		result.emplace_back( key );

	for( auto key : generateInfosEx | std::views::keys )
		result.emplace_back( key[ 0 ], key );
	return result;
}
