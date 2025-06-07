#include "baseStackEx.h"

#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"

BaseStackEx::BaseStackEx( ) {
	generateInfosEx.emplace_back( std_pairt( std_vector< QString > { "file" }, []( )->ITypeObject * {
		auto ptr = new CombinationTypeObject( {  { "file" } } );
		new StringTypeObject({"string"});
		ptr->setVarObject(  );
		return ptr;
	} ) );
}
ITypeObject * BaseStackEx::generateUBVar( const QString &type_name ) const {
	auto generateUbVar = BaseStack::generateUBVar( type_name );
	if( generateUbVar == nullptr /* 使用该类的名称 */ ) {
	}
	return generateUbVar;
}
