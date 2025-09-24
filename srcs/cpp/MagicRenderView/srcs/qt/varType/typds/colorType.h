#ifndef COLORTYPE_H_H_HEAD__FILE__
#define COLORTYPE_H_H_HEAD__FILE__
#pragma once


#include "../baseVarType.h"
class ColorType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class BaseVarType;
	friend class StringType;
	friend class IntType;
	friend class NullptrType;
protected:
	using t_current_type = double;
	t_current_type *var;
public:
	ColorType( QObject *parent );
	ColorType( );
	~ColorType( ) override;
	void resetVar( ) override {
		*var = t_current_type( );
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};

#endif // COLORTYPE_H_H_HEAD__FILE__
