#include "baseStackEx.h"

#include "qt/type/blendType/combinationTypeObject.h"

 void BaseStackEx:: appendMap(  const std_vector< QString > &type_name, const std_function< ITypeObject *( ) > &create_function ) {
	generateInfosEx.emplace_back( std_pairt( type_name, create_function ) );
}

BaseStackEx::BaseStackEx( ) {

}
ITypeObject * BaseStackEx::generateUBVar( const QString &type_name ) const {
	auto generateUbVar = BaseStack::generateUBVar( type_name );
	if( generateUbVar == nullptr /* 使用该类的名称 */ ) {
	}
	return generateUbVar;
}
