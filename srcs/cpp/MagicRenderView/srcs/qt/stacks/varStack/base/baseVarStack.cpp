#include "BaseVarStack.h"

#include <ranges>

#include "../../../application/application.h"

#include "qt/types/baseType/dataTypeObject.h"
#include "qt/types/baseType/floatTypeObject.h"
#include "qt/types/baseType/intTypeObject.h"
#include "qt/types/baseType/nullTypeObject.h"
#include "qt/types/baseType/stringTypeObject.h"
#include "qt/types/blendType/combinationTypeObject.h"
#include "qt/types/lineType/vectorTypeObject.h"
#include "qt/types/sequenceType/pairtTypeObject.h"

#define emplace_back_generateInfos(  element_, type_, ...  )\
	element.first.first = type_::staticMetaObject.className( ) ;\
	element.first.second = {#type_,__VA_ARGS__ };\
	element_.second = [this]( )  {\
		auto typeObject = new type_(this,	[this]()  {\
				auto applicationInstancePtr = Application::getApplicationInstancePtr( );\
			auto instances = applicationInstancePtr->findVarStacksAtType< BaseVarStack >( );\
			for( auto &item : instances )\
				if( item->getStackTypeName( ) == stackTypeName )\
					return item;\
			return std_shared_ptr<IVarStack>( new BaseVarStack( getStackFunction ));\
			}, std_vector< QString >( {type_::staticMetaObject.className( ),#type_,__VA_ARGS__} )) ;\
		typeObject->setUiTypeNames( { type_::staticMetaObject.className( ) , #type_, __VA_ARGS__ } );\
		return  typeObject;\
	};\
	generateInfos.emplace_back( element )

BaseVarStack::BaseVarStack( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent ): IVarStack( get_stack_function_get_function, parent ) {
	stackTypeName = "基本";

	std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > element;
	emplace_back_generateInfos( element, IntTypeObject, "int", "int_t", "char", "char_t", "size_t", "count", "整数", "计数", "字符" );
	emplace_back_generateInfos( element, FloatTypeObject, "float", "double", "double_t", "float_t", "浮点", "精度浮点", "双精度浮点" );
	emplace_back_generateInfos( element, NullTypeObject, "nullptr", "null", "null", "void", "NULL", "无", "错误", "异常" );
	emplace_back_generateInfos( element, DataTypeObject, "binary", "数据", "二进制" );
	emplace_back_generateInfos( element, StringTypeObject, "string", "text", "文本", "字符串", "路径", "path", "name", "名称" );
	emplace_back_generateInfos( element, CombinationTypeObject, "struct", "class", "混合", "结构体", "数据结构" );
	emplace_back_generateInfos( element, VectorTypeObject, "array", "vector", "序列", "数组", "列表" );
	emplace_back_generateInfos( element, PairtTypeObject, "pairt", "map", "映射", "键值对", "配对" );
	generateInfosRemoveRe( );
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
void BaseVarStack::generateInfosRemoveRe( ) {
	decltype(generateInfos) buff;
	std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > element;
	for( auto &[ item, function ] : generateInfos ) {
		auto baseName = item.first;
		auto buffIterator = buff.begin( );
		auto buffEnd = buff.end( );

		for( ; buffIterator != buffEnd; ++buffIterator ) {
			if( baseName == buffIterator->first.first ) {
				tools::debug::printError( "重复基本的类型名称，请留意 : " + baseName );
				break;
			} else {
				std::vector< QString > &second = buffIterator->first.second;
				auto vectorIterator = second.begin( );
				auto endIterator = second.end( );
				for( ; vectorIterator != endIterator; ++vectorIterator )
					if( baseName == *vectorIterator ) {
						tools::debug::printError( "重复别名的类型名称，请留意 : " + buffIterator->first.first );
						break;
					}
				if( vectorIterator != endIterator )
					break;
			}
		}
		if( buffIterator != buffEnd ) {
			throw std::exception( "重复的类型" );
			break;
		}
		std_vector< QString > aliNames;
		std::vector< QString > &charses = item.second;
		size_t index = 0, count = charses.size( ), targetIndex, targetCount;
		QString *data = charses.data( ), *targetPtr;
		for( ; index < count; ++index ) {
			QString &string = data[ index ];
			if( string == baseName )
				continue;
			targetPtr = aliNames.data( );
			targetCount = aliNames.size( );
			for( targetIndex = 0; targetIndex < targetCount; ++targetIndex )
				if( targetPtr[ targetIndex ] == string )
					break;
			if( targetIndex < targetCount )
				continue;
			aliNames.emplace_back( string );
		}
		element.first.first = baseName;
		element.first.second = aliNames;
		element.second = function;
		buff.emplace_back( element );
	}
	generateInfos = buff;
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
