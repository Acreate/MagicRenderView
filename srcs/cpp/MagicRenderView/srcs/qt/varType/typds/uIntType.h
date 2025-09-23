#ifndef UINTTYPE_H_H_HEAD__FILE__
#define UINTTYPE_H_H_HEAD__FILE__
#pragma once
#include "../baseVarType.h"

class UIntType : public BaseVarType {
	Q_OBJECT;
protected:
	using t_current_type = uint64_t;
	t_current_type *var;
public:
	UIntType( QObject *parent );
	~UIntType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};
#endif // UINTTYPE_H_H_HEAD__FILE__
