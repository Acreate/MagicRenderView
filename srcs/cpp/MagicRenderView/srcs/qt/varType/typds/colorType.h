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
	using t_current_type = QColor;
	t_current_type *var;
protected:
	ColorType( QObject *parent );
	ColorType( );
public:
	~ColorType( ) override;
	void resetVar( ) override;
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};

#endif // COLORTYPE_H_H_HEAD__FILE__
