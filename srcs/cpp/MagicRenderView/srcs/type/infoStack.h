#ifndef INFOSTACK_H_H_HEAD__FILE__
#define INFOSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <vector>
#include <qstring.h>

#include "../enums/typeEnum.h"
class InfoStack : public QObject {
	Q_OBJECT;
	friend class VarDirector;
private:
	std::function< void*( ) > newObjTypeFunction;
	std::function< bool( void * ) > deleteObjTypeFunction;
protected:
	virtual bool init( ) =0;
protected:
	virtual void setNewObjTypeFunction( const std::function< void *( ) > &new_obj_type_function ) { newObjTypeFunction = new_obj_type_function; }
	virtual void setDeleteObjTypeFunction( const std::function< bool( void * ) > &delete_obj_type_function ) { deleteObjTypeFunction = delete_obj_type_function; }
protected:
	QString typeName;
	std::vector< QString > aliasTypeNames;
	std::vector< void * > allVarPtrVector;
protected:
	InfoStack( );
public:
	~InfoStack( ) override;
public:
	virtual void * createTypePtr( );
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
	virtual uint64_t toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) = 0;
public:
	virtual uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data );
	virtual uint64_t getTypeNameAtData( std::vector< uint8_t > &result_data );
	virtual uint64_t getDataAtTypeName( const uint8_t *source_ptr, const size_t &source_count, QString &result_type_name );
	virtual uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) = 0;
protected:
	virtual uint64_t toVector( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result );
	virtual uint64_t toVar( const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count );
	virtual uint64_t toVector( const void *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
		return toVector( ( uint8_t * ) ptr, ptr_size, result );
	}
	template< typename TSourceType >
	uint64_t fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
		return toVector( ( const uint8_t * ) ptr, sizeof( TSourceType ) / sizeof( uint8_t ), result );
	}
	template< typename TSourceType >
	uint64_t fillTypeVectorAtVar( const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		return toVar( source_ptr, source_count, ( uint8_t * ) target_var_ptr, sizeof( TSourceType ) / sizeof( uint8_t ) );
	}
	template<>
	uint64_t fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result );
	template<>
	uint64_t fillTypeVectorAtVar< QString >( const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr );
};
#endif // INFOSTACK_H_H_HEAD__FILE__
