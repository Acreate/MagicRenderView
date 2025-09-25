#ifndef NULLPTRTYPE_H_H_HEAD__FILE__
#define NULLPTRTYPE_H_H_HEAD__FILE__
#pragma once

#include "../I_Type.h"
#include "../baseVarType.h"

class NullptrType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
public:
	NullptrType( QObject *parent );
	NullptrType( );
	~NullptrType( ) override;
protected:
	void * getVarPtr( ) const override {
		return nullptr;
	}
public:
	void resetVar( ) override { }
};
#endif // NULLPTRTYPE_H_H_HEAD__FILE__
