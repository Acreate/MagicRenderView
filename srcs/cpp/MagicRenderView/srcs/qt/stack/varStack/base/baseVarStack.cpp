#include "BaseVarStack.h"

#include <ranges>

#include "qt/type/baseType/dataTypeObject.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"
#include "qt/type/lineType/vectorTypeObject.h"
#include "qt/type/sequenceType/pairtTypeObject.h"

#define emplace_back_generateInfos(  element_, type_, ...  )\
	element.first.first = type_::staticMetaObject.className( ) ;\
	element.first.second = {#type_,__VA_ARGS__ };\
	element_.second = [this]( )  {\
		return  new type_(	[this]()  {\
			return IVarStack::getInstance( this->metaObject(  )->className(  ) );\
	}, std_vector< QString >( {type_::staticMetaObject.className( ),#type_,__VA_ARGS__} )) ;\
	};\
	generateInfos.emplace_back( element )

BaseVarStack::BaseVarStack( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent ): IVarStack( get_stack_function_get_function, parent ) {
	stackTypeNames.clear( );
	stackTypeNames.emplace_back( BaseVarStack::staticMetaObject.className( ) );

	std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > element;;
	emplace_back_generateInfos( element, IntTypeObject, "int", "int_t", "char", "char_t", "size_t", "count" );
	emplace_back_generateInfos( element, FloatTypeObject, "float", "double", "double_t", "float_t" );
	emplace_back_generateInfos( element, NullTypeObject, "nullptr", "null", "null", "void", "NULL" );
	emplace_back_generateInfos( element, DataTypeObject, "binary" );
	emplace_back_generateInfos( element, StringTypeObject, "string", "text" );
	emplace_back_generateInfos( element, CombinationTypeObject, "struct", "class" );
	emplace_back_generateInfos( element, VectorTypeObject, "array", "vector" );
	emplace_back_generateInfos( element, PairtTypeObject, "pairt", "map" );
}
ITypeObject * BaseVarStack::newVar( const QString &type_name ) const {
	for( auto &element : generateInfos )
		if( element.first.first == type_name )
			return element.second( );
		else
			for( auto &name : element.first.second )
				if( name == type_name )
					return element.second( );
	return nullptr;
}
ITypeObject * BaseVarStack::_generateUBVar( const QString &type_name ) const {
	return newVar( type_name );
}
std_shared_ptr< ITypeObject > BaseVarStack::generateVar( const QString &type_name ) const {
	return std_shared_ptr< ITypeObject >( _generateUBVar( type_name ) );
}
std_vector< std_pairt< QString, std_vector< QString > > > BaseVarStack::permissionVarType( ) const {
	std_vector< std_pairt< QString, std_vector< QString > > > result;
	for( auto key : generateInfos | std::views::keys )
		result.emplace_back( key );
	return result;
}
