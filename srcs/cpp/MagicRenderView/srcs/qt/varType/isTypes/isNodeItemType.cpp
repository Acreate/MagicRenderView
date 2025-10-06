#include "isNodeItemType.h"

#include <qt/varType/I_IsType.h>

#include <qt/node/item/nodeItem.h>

#include "../I_Stack.h"

#include "../../generate/varGenerate.h"

IsNodeItemType::IsNodeItemType( ) : I_IsType( typeid( t_current_type ) ) {
}
bool IsNodeItemType::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {

	if( check_type_info != currentTypeInfo )
		return false;
	std_pairt< std_vector< QString >, I_Type * > result_info;
	if( varGenerate->getTypeInfoGenerateInfo( currentTypeInfo, result_info ) == false )
		return false;
	for( auto &typeName : result_info.first )
		if( typeName == create_name ) {
			auto ptr = new I_Var( *result_info.second, typeName );
			if( create_is_right_call_back_function( ptr ) == false )
				delete ptr;
			return true;
		}

	return false;
}
bool IsNodeItemType::getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector< QString > &result_alias_name_list ) const {

	if( check_type_info != currentTypeInfo )
		return false;
	size_t needCount;
	size_t useCount = I_Stack::fillObjVector( &needCount, sizeof( size_t ), check_type_data_ptr, check_type_data_count );
	if( useCount == 0 )
		return false;
	size_t mod = check_type_data_count - useCount;
	if( needCount > mod )
		return false;
	check_type_data_ptr += useCount;
	QString typeName;
	useCount = I_Stack::fillObjVector( &typeName, check_type_data_ptr, mod );
	if( useCount == 0 )
		return false;
	std_pairt< std_vector< QString >, I_Type * > resultInfo;

	if( varGenerate->getTypeInfoGenerateInfo( typeName, resultInfo ) == false )
		return false;
	result_alias_name_list = resultInfo.first;
	return true;
}
