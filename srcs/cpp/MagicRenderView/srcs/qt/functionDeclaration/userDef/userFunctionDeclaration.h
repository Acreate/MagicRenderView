#ifndef USERFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define USERFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once
#include "qt/functionDeclaration/IFunctionDeclaration.h"

class UserFunctionDeclaration : public IFunctionDeclaration {
public:
	UserFunctionDeclaration( const QString &function_declaration_name, const std_call &call_function )
		: IFunctionDeclaration( function_declaration_name, call_function ) {
	}
	UserFunctionDeclaration( const QString &function_declaration_name)
		: IFunctionDeclaration( function_declaration_name, nullptr ) {
	}
	

};

#endif // USERFUNCTIONDECLARATION_H_H_HEAD__FILE__
