#include "./varGenerate.h"

#include <qt/tools/tools.h>
#include <qt/varType/I_Conver.h>
#include <qt/varType/I_IsType.h>
#include <qt/varType/I_Stack.h>

bool VarGenerate::appendSortMap( const nodeItemEnum::Node_Item_Type &enum_type, const QString &dir_name, const QString &type_pro_name, const std_shared_ptr< I_Type > &type_ptr ) {

	// 查找已经存在的列表
	size_t count = nodeItemSortMap.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto topDataPtr = nodeItemSortMap.data( );
		for( ; index < count; ++index ) {
			auto &enumMap = topDataPtr[ index ];
			// 存在枚举
			if( enumMap.first == enum_type ) {
				count = enumMap.second.size( );
				if( count != 0 ) {
					auto dirDataPtr = enumMap.second.data( );
					index = 0;
					for( ; index < count; ++index ) {
						auto &dirMap = dirDataPtr[ index ];
						if( dirMap.first == dir_name ) {
							count = dirMap.second.size( );
							if( count != 0 ) {
								index = 0;
								auto data = dirMap.second.data( );
								for( ; index < count; ++index )
									if( data[ index ].first == type_pro_name ) {
										data[ index ].second = type_ptr;
										return true; // 覆盖
									}

							} // 找不到匹配的类名
							dirMap.second.emplace_back( type_pro_name, type_ptr );
							return true; // 处理节点名称
						}
					}

				} // 找不到匹配的目录

				node_name_type_vector_pairt nameMap;
				node_dir_type_vector_pairt dirMap;
				nameMap.emplace_back( type_pro_name, type_ptr );
				enumMap.second.emplace_back( dir_name, nameMap );
				return true; // 处理枚举序列
			}
		}
	} // 找不到匹配的枚举
	node_name_type_vector_pairt nameMap;
	node_dir_type_vector_pairt dirMap;
	nameMap.emplace_back( type_pro_name, type_ptr );
	dirMap.emplace_back( dir_name, nameMap );
	node_enum_type_vector_pairt enumPairt( enum_type, dirMap );
	nodeItemSortMap.emplace_back( enumPairt );
	return true;

}
bool VarGenerate::appendNodeItemGenerateInstance( const type_info &generate_var_type_info, const size_t &type_target_memory_size, const nodeItemEnum::Node_Item_Type &enum_type, const QString &dir_name, const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const createFunction &generate_var_function, const releaseFunction &release_var_function ) {
	auto typeShared = std_shared_ptr< I_Type >( new I_Type( generate_var_type_info, type_target_memory_size, type_pro_name, generate_var_name_vector, release_var_function, generate_var_function ) );
	std_shared_ptr< NodeItemGenerate > nodeItemGenerate( new NodeItemGenerate( typeShared, type_pro_name, dir_name, enum_type ) );
	for( auto &key : generateNodeItemTypeInfos )
		if( key->getType( )->getTypeInfo( ) == generate_var_type_info ) {
			if( appendSortMap( enum_type, dir_name, type_pro_name, typeShared ) == false )
				return false;
			key = nodeItemGenerate;
			return true;
		}
	if( appendSortMap( enum_type, dir_name, type_pro_name, typeShared ) == false ) {
		QString result;
		tools::debug::printError( QString( "%1/%2 [%3]节点排序失败" ).arg( dir_name, type_pro_name ).arg( nodeItemEnum::getEnumName( enum_type, result ) ) );
		return false;
	}
	generateNodeItemTypeInfos.emplace_back( nodeItemGenerate );
	return true;
}
bool VarGenerate::appendVarTypeGenerateInstance( const type_info &generate_var_type_info, const size_t &type_target_memory_size, const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const createFunction &generate_var_function, const releaseFunction &release_var_function ) {
	auto typeShared = std_shared_ptr< I_Type >( new I_Type( generate_var_type_info, type_target_memory_size, type_pro_name, generate_var_name_vector, release_var_function, generate_var_function ) );
	for( auto &key : generateAnyTypeInfos )
		if( key->getTypeInfo( ) == generate_var_type_info ) {
			key = typeShared;
			return true;
		}
	generateAnyTypeInfos.emplace_back( typeShared );
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
bool VarGenerate::getTypeInfoGenerateInfo( const QString &generate_type_name, I_Type *&result_info, size_t &start_index ) const {

	size_t count = generateAnyTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateAnyTypeInfos.data( );
	for( ; start_index < count; ++start_index )
		if( data[ start_index ]->getProTypeName( ) == generate_type_name ) {
			result_info = data[ start_index ].get( );
			return true;
		} else
			for( auto &typeName : data[ start_index ]->getAliasTypeName( ) )
				if( typeName == generate_type_name ) {
					result_info = data[ start_index ].get( );
					return true;
				}

	QString msg( "未发现 %1 扩展类型的类型识别功能" );
	tools::debug::printError( msg.arg( generate_type_name ) );
	return false;
}
bool VarGenerate::getTypeInfoGenerateInfo( const type_info &generate_type_info, I_Type *&result_info, size_t &start_index ) const {

	size_t count = generateAnyTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = generateAnyTypeInfos.data( );
	for( ; start_index < count; ++start_index )
		if( data[ start_index ]->getTypeInfo( ) == generate_type_info ) {
			result_info = data[ start_index ].get( );
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
NodeItem * VarGenerate::createNodeItem( const QString &dir_name, const QString &class_name ) {

	size_t count = generateNodeItemTypeInfos.size( );
	if( count == 0 )
		return nullptr;
	size_t index = 0;
	auto data = generateNodeItemTypeInfos.data( );
	NodeItemGenerate *nodeItemGenerate;
	for( ; index < count; ++index )
		if( nodeItemGenerate = data[ index ].get( ), nodeItemGenerate->isType( dir_name, class_name ) ) {
			auto create = nodeItemGenerate->getType( )->getCreate( );
			return ( NodeItem * ) create( );;
		}
	return nullptr;
}
