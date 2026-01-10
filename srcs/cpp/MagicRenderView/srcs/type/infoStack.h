#ifndef INFOSTACK_H_H_HEAD__FILE__
#define INFOSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <vector>
#include <qstring.h>

#include <enums/typeEnum.h>
class InfoStack : public QObject {
	Q_OBJECT;
	friend class VarDirector;
private:
	std::function< void*( ) > newObjTypeFunction;
	std::function< bool( void * ) > deleteObjTypeFunction;
protected:
	virtual bool init( VarDirector *var_director );
protected:
	virtual void setNewObjTypeFunction( const std::function< void *( ) > &new_obj_type_function ) { newObjTypeFunction = new_obj_type_function; }
	virtual void setDeleteObjTypeFunction( const std::function< bool( void * ) > &delete_obj_type_function ) { deleteObjTypeFunction = delete_obj_type_function; }
	virtual bool deleteObjTypeFunctionIsNull( ) const { return deleteObjTypeFunction == nullptr; }
	virtual bool NewObjTypeFunctionIsNull( ) const { return newObjTypeFunction == nullptr; }
protected:
	VarDirector *varDirector;
	QString typeName;
	std::vector< QString > aliasTypeNames;
	std::vector< void * > allVarPtrVector;
protected:
	InfoStack( );
public:
	~InfoStack( ) override;
public:
	virtual bool createTypePtr( void *&result_create_obj_ptr );
	virtual bool deleteTypePtr( const void *delete_obj_ptr );
public:
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual const std::vector< QString > & getAliasTypeNames( ) const { return aliasTypeNames; }
	virtual bool isTypeName( const QString &check_type_name ) const;
	virtual bool isAliasTypeNames( const QString &check_type_name ) const;
	virtual bool hasVarPtr( const void *check_obj_ptr ) const;
	virtual uint64_t size( ) const;
	virtual void * const* arrayPtr( ) const;
	virtual void ** arrayPtr( );
	virtual TypeEnum::Type getType( ) = 0;
public:
	friend bool operator==( const InfoStack &lhs, const InfoStack &rhs );
	friend bool operator!=( const InfoStack &lhs, const InfoStack &rhs ) { return !( lhs == rhs ); }
protected:
	virtual bool toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) = 0;
public:
	virtual bool toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data );
	virtual bool getTypeNameAtData( std::vector< uint8_t > &result_data );
	virtual bool getDataAtTypeName( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QString &result_type_name );
	virtual bool toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) = 0;
public:
};
#endif // INFOSTACK_H_H_HEAD__FILE__
