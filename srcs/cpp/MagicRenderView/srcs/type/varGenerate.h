#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <qstring.h>
#include <vector>

#include "../enums/typeEnum.h"

class StackSerialize;
class InfoStack;
class VarGenerate : public QObject {
	Q_OBJECT;
protected:
	std::vector< InfoStack * > stacks;
public:
	VarGenerate( );
	~VarGenerate( ) override;
public:
	virtual bool getObjPtrAtTypeName( const void *check_obj_ptr, QString &result_type_name );
	virtual bool realease( const void *delete_obj_ptr );
	virtual bool getTypeName( const type_info &type_info_ref, QString &result_type_name );
	virtual bool getTypeName( const QString &type_info_ref, QString &result_type_name );
	virtual bool getObjPtrType( const void *check_obj_ptr, TypeEnum::Type &result_bool );
	virtual void * create( const QString &create_type_name );
	virtual uint64_t toVar( const uint8_t *source_ptr, const size_t &source_count, void *&target_var_ptr );
	virtual uint64_t toVector( const void *ptr, std::vector< uint8_t > &result );
public:
	template< typename TCreateType >
	TCreateType * create( ) {
		return ( TCreateType * ) create( typeid( TCreateType ).name( ) );
	}

	template< typename TCreateType >
	TCreateType * cast_ptr( void *ptr ) {
		if( ptr == nullptr )
			return nullptr;
		QString converTypeName;
		// 检查是否存在指定的类型
		if( getObjPtrAtTypeName( ptr, converTypeName ) == false )
			return nullptr;
		QString typeInfoName = typeid( TCreateType ).name( );
		QString targetTypeName;
		// 获取转换的目标匹配类型名称
		if( getTypeName( typeInfoName, targetTypeName ) == false )
			return nullptr;
		// 如果目标类型名称与当前类型名称不相等，则不是同一类型
		if( targetTypeName != converTypeName )
			return nullptr;
		// 同一类型返回转换后的类型对象指针
		return ( TCreateType * ) ptr;
	}

	template< typename TCreateType >
	const TCreateType * cast_ptr( const void *ptr ) {
		if( ptr == nullptr )
			return nullptr;
		QString converTypeName;
		// 检查是否存在指定的类型
		if( getObjPtrAtTypeName( ptr, converTypeName ) == false )
			return nullptr;
		QString typeInfoName = typeid( TCreateType ).name( );
		QString targetTypeName;
		// 获取转换的目标匹配类型名称
		if( getTypeName( typeInfoName, targetTypeName ) == false )
			return nullptr;
		// 如果目标类型名称与当前类型名称不相等，则不是同一类型
		if( targetTypeName != converTypeName )
			return nullptr;
		// 同一类型返回转换后的类型对象指针
		return ( const TCreateType * ) ptr;
	}

};
#endif // VARGENERATE_H_H_HEAD__FILE__
