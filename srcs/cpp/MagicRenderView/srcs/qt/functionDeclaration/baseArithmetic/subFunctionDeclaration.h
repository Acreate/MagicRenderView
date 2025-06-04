#ifndef SUBFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define SUBFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once

#include "qt/functionDeclaration/IFunctionDeclaration.h"

class SubFunctionDeclaration : public IFunctionDeclaration {
public:
	SubFunctionDeclaration( );
	void call( ) const override {
		if( callFcuntion )
			callFcuntion( );
	}

};


#endif // SUBFUNCTIONDECLARATION_H_H_HEAD__FILE__
