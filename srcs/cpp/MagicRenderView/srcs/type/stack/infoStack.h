#ifndef INFOSTACK_H_H_HEAD__FILE__
#define INFOSTACK_H_H_HEAD__FILE__
#pragma once
#include <vector>
#include <functional>
#include <qstring.h>
class InfoStack {
	friend class InfoStackGenerate;
protected:
	QString typeName;
	std::vector< QString > aliasTypeNames;
	std::function< void*( ) > createFunction;
	std::function< void ( void *p ) > deleteFunction;
	std::list< void * > stackVarPtr;
public:
	virtual ~InfoStack( );
	virtual void * createTypePtr( );
	virtual bool deleteTypePtr( const void *delete_obj_ptr );
	virtual bool isType( const QString &check_type_name );
	virtual bool isAliasTypeNames( const QString &check_type_name );
	virtual bool hasVarPtr( const void *check_obj_ptr );
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual const std::vector< QString > & getAliasTypeNames( ) const { return aliasTypeNames; }
};

#endif // INFOSTACK_H_H_HEAD__FILE__
