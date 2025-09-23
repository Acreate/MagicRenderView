#ifndef STRINGTYPE_H_H_HEAD__FILE__
#define STRINGTYPE_H_H_HEAD__FILE__
#pragma once

#include "../baseVarType.h"

class StringType : public BaseVarType {
	Q_OBJECT;
protected:
	using t_current_type = QString;
	t_current_type *var;
public:
	StringType( QObject *parent );
	~StringType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};
#endif // STRINGTYPE_H_H_HEAD__FILE__
