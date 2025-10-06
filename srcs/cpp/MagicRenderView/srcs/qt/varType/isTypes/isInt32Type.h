#ifndef ISINT32TYPE_H_H_HEAD__FILE__
#define ISINT32TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsInt32Type : public I_IsType{
	
	using t_current_type = int32_t;
public:
	IsInt32Type( );
	bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function<bool(I_Var *create_var_ptr)> &create_is_right_call_back_function ) const override;
	bool getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector<QString> &result_alias_name_list ) const override;
};

#endif // ISINT32TYPE_H_H_HEAD__FILE__
