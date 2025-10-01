#ifndef I_VAR_H_H_HEAD__FILE__
#define I_VAR_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

class I_Type;
class I_Var {
protected:
	/// @brief 类型信息
	std_shared_ptr< I_Type > typeInfo;
	void *p;
	QString varName;
	I_Var( ) { }
};

#endif // I_VAR_H_H_HEAD__FILE__
