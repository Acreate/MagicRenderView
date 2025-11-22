#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <qstring.h>
#include <vector>

class StackSerialize;
class InfoStack;
class VarGenerate : public QObject {
	Q_OBJECT;
protected:
	std::vector< InfoStack * > stacks;
public:
	VarGenerate( );
	~VarGenerate( ) override;
protected:
	virtual void * create( const QString &create_type_name );
public:
	virtual bool getObjPtrAtTypeName( const void *check_obj_ptr, QString &result_type_name );
	virtual bool realease( const void *delete_obj_ptr );
	virtual bool getTypeName( const type_info &type_info_ref, QString &result_type_name );
	virtual bool getTypeName( const QString &type_info_ref, QString &result_type_name );
	template< typename TCreateType >
	TCreateType * create( ) {
		return ( TCreateType * ) create( typeid( TCreateType ).name( ) );
	}
};
#endif // VARGENERATE_H_H_HEAD__FILE__
