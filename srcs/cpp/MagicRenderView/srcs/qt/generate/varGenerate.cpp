#include "./varGenerate.h"

#include "../tools/tools.h"

#include "../varType/I_Conver.h"
#include "../varType/baseVarType.h"
#include "../varType/I_Type.h"
class BaseVarType;
std_vector< std_shared_ptr< I_Conver > > VarGenerate::converVector;
std_vector< BaseVarType * > VarGenerate::baseVarStack;
std_vector< std_pairt< std_shared_ptr< I_Type >, std_function< BaseVarType*( QObject * ) > > > VarGenerate::varTypeGenerateVector;
void VarGenerate::appendConverInstance( const std_shared_ptr< I_Conver > &new_conver ) {
	converVector.emplace_back( new_conver );
}
void VarGenerate::appendVarTypeGenerateInstance( const std_shared_ptr< I_Type > &info, const std_function< BaseVarType*( QObject * ) > &generate_instance_function ) {
	varTypeGenerateVector.insert( varTypeGenerateVector.begin( ), std_pairt { info, generate_instance_function } );
}

bool VarGenerate::conver( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->fillTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的转换" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::add( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->addTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的加法运算转换" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::sub( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->subTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的减法运算转换" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::mul( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->mulTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的乘法运算转换" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::div( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->divTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的除法运算转换" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->equThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->greaterThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的大于比较运算" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->lessThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的小于比较运算" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的大于等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
bool VarGenerate::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的小于等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info->getTypeInfo( ).name( ) ).arg( right_type_info->getTypeInfo( ).name( ) ) );
	return false;
}
BaseVarType * VarGenerate::createVarType( const I_Type &create_type, QObject *parent ) {
	size_t count = varTypeGenerateVector.size( );
	if( count != 0 ) {
		auto data = varTypeGenerateVector.data( );
		size_t index = 0;
		for( ; index < count; ++index ) {
			auto &pair = data[ index ];
			I_Type &leftType = *pair.first.get( );
			if( leftType != create_type )
				continue;
			auto sharedPtr = pair.second( parent );
			if( sharedPtr == nullptr )
				continue;
			return sharedPtr;
		}
	}
	QString msg( "未发现 %1 类型的创建函数" );
	tools::debug::printError( msg.arg( create_type.getTypeInfo( ).name( ) ) );
	return nullptr;
}

std_vector< std_shared_ptr< I_Type > > VarGenerate::getSupporType( ) {
	std_vector< std_shared_ptr< I_Type > > result;
	size_t count = varTypeGenerateVector.size( );
	if( count == 0 ) {
		QString msg( "未发现任意的支持类型" );
		tools::debug::printError( msg );
		return result;
	}
	auto data = varTypeGenerateVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		result.emplace_back( data[ index ].first );
	return result;
}
