#ifndef FLOATTYPE_H_H_HEAD__FILE__
#define FLOATTYPE_H_H_HEAD__FILE__
#pragma once

#include "../baseVarType.h"

class FloatType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
protected:
	using t_current_type = double;
	t_current_type *var;
	FloatType( QObject *parent );
public:
	~FloatType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override;
};

#endif // FLOATTYPE_H_H_HEAD__FILE__
