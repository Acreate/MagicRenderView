#ifndef ADDFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define ADDFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once
#include "qt/functionDeclaration/IFunctionDeclaration.h"

class AddFunctionDeclaration : public IFunctionDeclaration {
public:
	AddFunctionDeclaration( );
	void call( ) const override {
		if( callFcuntion )
			callFcuntion( );
	}

};
	

#endif // ADDFUNCTIONDECLARATION_H_H_HEAD__FILE__
