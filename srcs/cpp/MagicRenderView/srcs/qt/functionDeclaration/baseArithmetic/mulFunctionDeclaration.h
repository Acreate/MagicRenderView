#ifndef MULFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define MULFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once

#include "qt/functionDeclaration/IFunctionDeclaration.h"

class MulFunctionDeclaration : public IFunctionDeclaration {
public:
	MulFunctionDeclaration( );
	void call( ) const override {
		if( callFcuntion )
			callFcuntion( );
	}

};

#endif // MULFUNCTIONDECLARATION_H_H_HEAD__FILE__
