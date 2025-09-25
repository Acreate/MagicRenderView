#ifndef STRINGTYPE_H_H_HEAD__FILE__
#define STRINGTYPE_H_H_HEAD__FILE__
#pragma once

#include "../baseVarType.h"
class StringType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class BaseVarType;
	friend class FloatType;
	friend class IntType;
	friend class NullptrType;
protected:
	using t_current_type = QString;
	t_current_type *var;
public:
	StringType( QObject *parent );
	StringType( ) : StringType( nullptr ) { }
	~StringType( ) override {
	}
	void resetVar( ) override {
		*var = t_current_type( );
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}

};
#endif // STRINGTYPE_H_H_HEAD__FILE__
