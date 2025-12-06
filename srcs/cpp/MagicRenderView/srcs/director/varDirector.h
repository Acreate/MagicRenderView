#ifndef VARDIRECTOR_H_H_HEAD__FILE__
#define VARDIRECTOR_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <typeinfo>
#include <qstring.h>
#include <vector>

#include "../enums/typeEnum.h"

class PrinterDirector;
class StackSerialize;
class InfoStack;
class Application;
class VarDirector : public QObject {
	Q_OBJECT;
	friend class Application;
protected:
	std::vector< InfoStack * > stacks;
	Application *instancePtr;
	PrinterDirector *printerDirector;
public:
	VarDirector( );
	~VarDirector( ) override;
public:
	virtual bool init( );
	virtual bool getObjPtrAtTypeName( const void *check_obj_ptr, QString &result_type_name );
	virtual bool release( const void *delete_obj_ptr );
	virtual bool getTypeName( const QString &type_info_ref, QString &result_type_name );
	virtual bool getTypeName( const std::type_info &type_info_ref, QString &result_type_name ) {
		QString typeInfoName = type_info_ref.name( );
		return getTypeName( typeInfoName, result_type_name );
	}
	virtual bool getObjPtrType( const void *check_obj_ptr, TypeEnum::Type &result_bool );
	virtual bool create( const QString &create_type_name, void *&result_create_obj_ptr );
	virtual bool toVar( size_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *&target_var_ptr );
	virtual bool toVector( const void *ptr, std::vector< uint8_t > &result );
public:
	template< typename TCreateType >
	bool create( TCreateType * &result_ptr ) {
		void *result_create_ptr;
		if( create( typeid( TCreateType ).name( ), result_create_ptr ) == false )
			return false;
		result_ptr = ( TCreateType * ) result_create_ptr;
		return true;
	}

	template< typename TCreateType >
	bool cast_ptr( void *ptr, TCreateType * &result_ptr ) {
		if( ptr == nullptr )
			return false;
		QString converTypeName;
		// 检查是否存在指定的类型
		if( getObjPtrAtTypeName( ptr, converTypeName ) == false )
			return false;
		QString typeInfoName = typeid( TCreateType ).name( );
		QString targetTypeName;
		// 获取转换的目标匹配类型名称
		if( getTypeName( typeInfoName, targetTypeName ) == false )
			return false;
		// 如果目标类型名称与当前类型名称不相等，则不是同一类型
		if( targetTypeName != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( TCreateType * ) ptr;
		return true;
	}

	template< typename TCreateType >
	bool cast_ptr( const void *ptr, const TCreateType * &result_ptr ) {
		if( ptr == nullptr )
			return false;
		QString converTypeName;
		// 检查是否存在指定的类型
		if( getObjPtrAtTypeName( ptr, converTypeName ) == false )
			return false;
		QString typeInfoName = typeid( TCreateType ).name( );
		QString targetTypeName;
		// 获取转换的目标匹配类型名称
		if( getTypeName( typeInfoName, targetTypeName ) == false )
			return false;
		// 如果目标类型名称与当前类型名称不相等，则不是同一类型
		if( targetTypeName != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( const TCreateType * ) ptr;
		return true;
	}

};
#endif // VARDIRECTOR_H_H_HEAD__FILE__
