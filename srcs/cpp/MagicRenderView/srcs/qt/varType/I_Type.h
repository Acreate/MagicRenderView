#ifndef I_TYPE_H_H_HEAD__FILE__
#define I_TYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

class I_Stack;
/// @brief 类型接口
class I_Type {
protected:
	std_shared_ptr< I_Stack > createObjStack;
	const type_info &typeInfo;
	void *p;
	I_Type( const std_shared_ptr< I_Stack > &create_obj_stack, void *var_p );
	I_Type( type_info &type_info ) = delete;
	I_Type( const I_Type &other ) = delete;
public:
	virtual ~I_Type( );
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }
	virtual void * getPtr( ) const { return p; }
	/// @brief 是否私有话指针
	/// @return 返回 true 表示私有化
	virtual bool isPrivateVarPtr( ) const { return true; }
};

#endif // I_TYPE_H_H_HEAD__FILE__
