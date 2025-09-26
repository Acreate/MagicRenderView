#ifndef STRINGTOSTRING_H_H_HEAD__FILE__
#define STRINGTOSTRING_H_H_HEAD__FILE__
#pragma once

#include "../../I_Conver.h"

class StringToString : public I_Conver {
public:
	bool fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) override;
	bool addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) override;
	bool subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) override;
	bool mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) override;
	bool divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) override;
	bool equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) override;
	bool greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) override;
	bool greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) override;
	bool lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) override;
	bool lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) override;
};

#endif // STRINGTOSTRING_H_H_HEAD__FILE__
