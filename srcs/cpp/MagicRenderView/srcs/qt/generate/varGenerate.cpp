#include "./varGenerate.h"

#include "../tools/tools.h"

#include "../varType/I_Conver.h"
#include "../varType/I_IsType.h"
#include "../varType/I_Stack.h"

bool VarGenerate::appendVarTypeGenerateInstance( const type_info &generate_var_type_info, const std_function< void *( void * ) > &generate_var_function, const std_function< bool( void * ) > &release_var_function, const std_vector< QString > &generate_var_name_vector ) {
	auto typeShared = std_shared_ptr< I_Type >( new I_Type( generate_var_type_info, release_var_function, generate_var_function ) );
	for( auto &[ key,val ] : generateTypeInfos )
		if( key.first->getTypeInfo( ) == generate_var_type_info ) {
			key.first = typeShared;
			val = generate_var_name_vector;
			return true;
		}
	std_pairt unity( std_pairt( typeShared, generate_var_function ), generate_var_name_vector );
	generateTypeInfos.emplace_back( unity );
	return true;
}
bool VarGenerate::supportType( const type_info &left_type_info, const type_info &right_type_info, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->supportType( left_type_info, right_type_info ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的左值右值操作" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::conver( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->fillTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的转换" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::add( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->addTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的加法运算转换" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::sub( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->subTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的减法运算转换" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::mul( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->mulTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的乘法运算转换" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::div( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->divTarget( left_type_info, left, right_type_info, right ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的除法运算转换" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->equThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->greaterThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的大于比较运算" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->lessThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的小于比较运算" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的大于等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}
bool VarGenerate::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const {
	size_t count = converVector.size( );
	if( count != 0 ) {
		auto data = converVector.data( );
		I_Conver *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool ) )
				return true;
	}
	QString msg( "未发现 %1 与 %2 类型的小于等于比较运算" );
	tools::debug::printError( msg.arg( left_type_info.name( ) ).arg( right_type_info.name( ) ) );
	return false;
}

bool VarGenerate::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count, size_t &start_index ) const {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		I_Stack *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->toBinVector( target_type_info, target_ptr, result_vector, result_count ) )
				return true;
	}
	QString msg( "未发现 %1 类型的序列化功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}
bool VarGenerate::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count, size_t &start_index ) const {
	size_t count = stackVector.size( );
	if( count != 0 ) {
		auto data = stackVector.data( );
		I_Stack *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->toOBjVector( target_type_info, target_ptr, result_count, source_data_ptr, source_data_count ) )
				return true;
	}
	QString msg( "未发现 %1 类型的反序列化功能" );
	tools::debug::printError( msg.arg( target_type_info.name( ) ) );
	return false;
}
bool VarGenerate::getTypeInfoGenerateInfo( const QString &generate_type_name, std_pairt< std_vector< QString >, I_Type * > &result_info, size_t &start_index ) const {

	size_t count = generateTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateTypeInfos.data( );
	for( ; start_index < count; ++start_index )
		for( auto &typeName : data[ start_index ].second )
			if( typeName == generate_type_name ) {
				auto pair = data[ start_index ].first;
				result_info.second = pair.first.get( );
				result_info.first = data[ start_index ].second;
				return true;
			}

	QString msg( "未发现 %1 扩展类型的类型识别功能" );
	tools::debug::printError( msg.arg( generate_type_name ) );
	return false;
}
bool VarGenerate::getTypeInfoGenerateInfo( const type_info &generate_type_info, std_pairt< std_vector< QString >, I_Type * > &result_info, size_t &start_index ) const {

	size_t count = generateTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateTypeInfos.data( );
	for( ; start_index < count; ++start_index )
		if( data[ start_index ].first.first->getTypeInfo( ) == generate_type_info ) {
			result_info.first = data[ start_index ].second;
			result_info.second = data[ start_index ].first.first.get( );
			return true;
		}
	QString msg( "未发现 %1 扩展类型的类型识别功能" );
	tools::debug::printError( msg.arg( generate_type_info.name( ) ) );
	return false;
}
bool VarGenerate::getCheckTypeNames( const QString &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_pairt< const I_Type *, std_vector< QString > > &result_alias_name_list, size_t &start_index ) const {
	size_t count = isTypeVector.size( );
	if( count != 0 ) {
		auto data = isTypeVector.data( );
		I_IsType *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->getCheckTypeNames( check_type_info, check_type_data_ptr, check_type_data_count, result_alias_name_list ) )
				return true;
	}
	QString msg( "未发现 %1 类型的类型识别功能" );
	tools::debug::printError( msg.arg( check_type_info ) );
	return false;
}
bool VarGenerate::getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector< QString > &result_type_string_name, size_t &start_index ) {
	size_t count = isTypeVector.size( );
	if( count != 0 ) {
		auto data = isTypeVector.data( );
		I_IsType *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->getCheckTypeNames( check_type_info, check_type_data_ptr, check_type_data_count, result_type_string_name ) )
				return true;
	}
	QString msg( "未发现 %1 类型的类型识别功能" );
	tools::debug::printError( msg.arg( check_type_info.name( ) ) );
	return false;
}
bool VarGenerate::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function, size_t &start_index ) const {
	size_t count = isTypeVector.size( );
	if( count != 0 ) {
		auto data = isTypeVector.data( );
		I_IsType *extent;
		for( ; start_index < count; ++start_index )
			if( extent = data[ start_index ].get( ), extent->createCheckTypeName( check_type_info, create_name, create_is_right_call_back_function ) )
				return true;
	}
	QString msg( "未发现 %1 类型的类型创建功能" );
	tools::debug::printError( msg.arg( check_type_info.name( ) ) );
	return false;
}
