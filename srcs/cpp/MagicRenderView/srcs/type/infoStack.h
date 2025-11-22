#ifndef INFOSTACK_H_H_HEAD__FILE__
#define INFOSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <vector>
#include <functional>
#include <qstring.h>

#include "../enums/typeEnum.h"

#define Stack_Type_Name( _Type ) typeName = #_Type; aliasTypeNames.emplace_back( typeid( _Type ).name(   ) )

class InfoStack : public QObject {
	Q_OBJECT;
protected:
	QString typeName;
	std::vector< QString > aliasTypeNames;
	std::vector< void * > allVarPtrVector;
protected:
	InfoStack( ) { }
public:
	~InfoStack( ) override;
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual const std::vector< QString > & getAliasTypeNames( ) const { return aliasTypeNames; }
	virtual void * createTypePtr( ) = 0;
	virtual bool deleteTypePtr( const void *delete_obj_ptr ) = 0;
	virtual bool isTypeName( const QString &check_type_name ) const;
	virtual bool isAliasTypeNames( const QString &check_type_name ) const;
	virtual bool hasVarPtr( const void *check_obj_ptr ) const;
	virtual uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) =0;
	virtual uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) = 0;
	virtual TypeEnum::Type getType( ) = 0;
	friend bool operator==( const InfoStack &lhs, const InfoStack &rhs );
	friend bool operator!=( const InfoStack &lhs, const InfoStack &rhs ) { return !( lhs == rhs ); }
};
#endif // INFOSTACK_H_H_HEAD__FILE__
