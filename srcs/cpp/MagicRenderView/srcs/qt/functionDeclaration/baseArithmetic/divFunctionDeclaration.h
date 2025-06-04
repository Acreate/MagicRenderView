#ifndef DIVFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define DIVFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once

#include "qt/functionDeclaration/IFunctionDeclaration.h"

class DivFunctionDeclaration : public IFunctionDeclaration {
public:
	DivFunctionDeclaration( );
	void call( ) const override {
		if( callFcuntion )
			callFcuntion( );
	}

};
	


#endif // DIVFUNCTIONDECLARATION_H_H_HEAD__FILE__
