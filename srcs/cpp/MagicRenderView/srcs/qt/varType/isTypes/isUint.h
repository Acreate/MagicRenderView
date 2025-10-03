#ifndef ISUINT_H_H_HEAD__FILE__
#define ISUINT_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsUint :public I_IsType{
public:
	bool isInt( const type_info &check_type_info, void *check_type_data_ptr ) const override;
	bool isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const override;
	bool isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const override;
	bool isString( const type_info &check_type_info, void *check_type_data_ptr ) const override;
	bool getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const override;
};

#endif // ISUINT_H_H_HEAD__FILE__
