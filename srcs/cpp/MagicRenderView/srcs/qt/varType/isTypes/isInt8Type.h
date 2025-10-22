#ifndef ISINT8TYPE_H_H_HEAD__FILE__
#define ISINT8TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsInt8Type : public I_IsType{
	
	using t_current_type = int8_t;
public:
	IsInt8Type( );
	bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function<bool(I_Var *create_var_ptr)> &create_is_right_call_back_function ) const override;
};

#endif // ISINT8TYPE_H_H_HEAD__FILE__
