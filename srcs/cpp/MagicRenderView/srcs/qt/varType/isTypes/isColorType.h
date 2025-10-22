#ifndef ISCOLORTYPE_H_H_HEAD__FILE__
#define ISCOLORTYPE_H_H_HEAD__FILE__
#pragma once
#include <qcolor.h>

#include "../I_IsType.h"

class IsColorType : public I_IsType {

	using t_current_type = QColor;
public:
	IsColorType( );
	bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const override;
};

#endif // ISCOLORTYPE_H_H_HEAD__FILE__
