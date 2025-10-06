#include "isStdStringType.h"
IsStdStringType::IsStdStringType( ): I_IsType( typeid( t_current_type ) ) { }
bool IsStdStringType::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function<bool(I_Var *create_var_ptr)> &create_is_right_call_back_function ) const {
	return I_IsType::createCheckTypeName( check_type_info, create_name, create_is_right_call_back_function );
}
bool IsStdStringType::getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector<QString> &result_alias_name_list ) const {
	return I_IsType::getCheckTypeNames( check_type_info, check_type_data_ptr, check_type_data_count, result_alias_name_list );
}
