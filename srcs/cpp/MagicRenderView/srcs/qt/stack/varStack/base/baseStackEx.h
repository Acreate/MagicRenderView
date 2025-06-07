#ifndef BASESTACKEX_H_H_HEAD__FILE__
#define BASESTACKEX_H_H_HEAD__FILE__
#pragma once
#include "baseStack.h"

class BaseStackEx : public BaseStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	/// @brief 生成信息对象列表
	std_vector< std_pairt< std_vector< QString >, std_function< ITypeObject *( ) > > > generateInfosEx;
private:
	void appendMap( const std_vector< QString > &type_name, const std_function< ITypeObject *( ) > &create_function );
protected:
	BaseStackEx( );
	ITypeObject * generateUBVar( const QString &type_name ) const override;
public:
	~BaseStackEx( ) override {
	}
};

#endif // BASESTACKEX_H_H_HEAD__FILE__
