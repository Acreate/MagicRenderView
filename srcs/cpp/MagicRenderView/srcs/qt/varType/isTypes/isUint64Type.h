#ifndef ISUINT64TYPE_H_H_HEAD__FILE__
#define ISUINT64TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsUint64Type : public I_IsType {
	using t_current_type = uint64_t;
public:
	IsUint64Type( );
	bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function<bool(I_Var *create_var_ptr)> &create_is_right_call_back_function ) const override;
};

#endif // ISUINT64TYPE_H_H_HEAD__FILE__
