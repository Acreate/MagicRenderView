#include "./varGenerate.h"

#include "../tools/tools.h"

#include "../varType/I_Conver.h"
#include "../varType/I_Stack.h"

bool VarGenerate::appendVarTypeGenerateInstance( const type_info &generate_var_type_info, const std_function< void *( void * ) > &generate_var_function, const std_vector< QString > &generate_var_name_vector ) {
	for( auto &[ key,val ] : generateTypeInfos )
		if( key.first->getTypeInfo( ) == generate_var_type_info ) {
			key.second = generate_var_function;
			val = generate_var_name_vector;
			return true;
		}
	auto typeShared = std_shared_ptr< I_Type >( new I_Type( generate_var_type_info ) );
	std_pairt unity( std_pairt( typeShared, generate_var_function ), generate_var_name_vector );
	generateTypeInfos.emplace_back( unity );
	return true;
}
bool VarGenerate::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		size_t index = 0;
		I_Conver *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->supportType( left_type_info, right_type_info ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的左值右值操作" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::conver( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::add( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::sub( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::mul( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::div( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
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
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::deleteTarget( const type_info &target_type_info, void *target_ptr ) {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		size_t index = 0;
		I_Stack *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->deleteTarget( target_type_info, target_ptr ) )
				return true;
	}
	QString msg( "未发现 %1 类型的释放功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}
bool VarGenerate::deleteTarget( void *target_ptr ) {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		size_t index = 0;
		I_Stack *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->deleteTarget( target_ptr ) )
				return true;
	}
	QString msg( "未发现 %1 类型的释放功能" );
	tools::debug::printError( msg.arg( ( size_t ) target_ptr, 0, 16 ) );
	return false;
}
bool VarGenerate::createTarget( const type_info &target_type_info, const std_function< void( void *create_obj_ptr ) > &create_call_function ) {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		size_t index = 0;
		I_Stack *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->createTarget( target_type_info, create_call_function ) )
				return true;
	}
	QString msg( "未发现 %1 类型的创建功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}

bool VarGenerate::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		size_t index = 0;
		I_Stack *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->toBinVector( target_type_info, target_ptr, result_vector, result_count ) )
				return true;
	}
	QString msg( "未发现 %1 类型的序列化功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}
bool VarGenerate::toOBjVector( const type_info &target_type_info, void **target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		size_t index = 0;
		I_Stack *extent;
		for( ; index < count; ++index )
			if( extent = data[ index ].get( ), extent->toOBjVector( target_type_info, target_ptr, result_count, source_data_ptr, source_data_count ) )
				return true;
	}
	QString msg( "未发现 %1 类型的反序列化功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}
bool VarGenerate::getTypeInfoGenerateInfo( const QString &generate_type_name, std_pairt< std_pairt< std_shared_ptr< I_Type >, std_function< void *( void * ) > >, std_vector< QString > > &result_info ) const {

	size_t count = generateTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateTypeInfos.data( );
	for( size_t index = 0; index < count; ++index )
		for( auto &typeName : data[ index ].second )
			if( typeName == generate_type_name ) {
				auto &first = data[ index ].first;
				std_pairt key( first.first, first.second );
				result_info.first = key;
				result_info.second = data[ index ].second;
				return true;
			}

	return false;
}
bool VarGenerate::getTypeInfoGenerateInfo( const type_info &generate_type_info, std_pairt< std_vector< QString >, std_function< void *( void * ) > > &result_info ) const {

	size_t count = generateTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateTypeInfos.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first.first->getTypeInfo( ) == generate_type_info ) {
			result_info.first = data[ index ].second;
			result_info.second = data[ index ].first.second;
			return true;
		}

	return false;
}
