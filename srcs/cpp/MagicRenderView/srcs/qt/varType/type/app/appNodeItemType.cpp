#include "appNodeItemType.h"

#include <qt/tools/tools.h>
#include <qt/node/item/nodeItem.h>
AppNodeItemType::AppNodeItemType( ) : I_Stack( typeid( t_current_type ) ) {
	childcreateFunction = [] {
		tools::debug::printError( "该对象不具备创建与释放功能" );
		return nullptr;
	};
	childDeleteFunction = [this] ( void *target_ptr ) {
		tools::debug::printError( "该对象不具备创建与释放功能" );
		return false;
	};
}
bool AppNodeItemType::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
	if( generateTypeInfo.before( target_type_info ) == false )
		return false;
	return I_Stack::toBinVector( target_type_info, target_ptr, result_vector, result_count );
}
bool AppNodeItemType::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( generateTypeInfo.before( target_type_info ) == false )
		return false;
	return I_Stack::toOBjVector( target_type_info, target_ptr, result_count, source_data_ptr, source_data_count );
}
