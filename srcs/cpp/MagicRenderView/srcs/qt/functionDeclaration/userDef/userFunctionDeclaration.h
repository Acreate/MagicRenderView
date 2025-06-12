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
	bool serializeToVectorData( std_vector<uint8_t> *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;

};

#endif // USERFUNCTIONDECLARATION_H_H_HEAD__FILE__
