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
	virtual bool toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) = 0;
public:
	virtual bool toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data );
	virtual bool getTypeNameAtData( std::vector< uint8_t > &result_data );
	virtual bool getDataAtTypeName( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QString &result_type_name );
	virtual bool toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) = 0;
public:
	static bool fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result );
	static bool fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count );
	static bool fillObjTarget( uint64_t &result_count, const void *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( uint8_t * ) ptr, ptr_size, result );
	}
	template< typename TSourceType >
	static bool fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( const uint8_t * ) ptr, sizeof( TSourceType ) / sizeof( uint8_t ), result );
	}
	template< typename TSourceType >
	static bool fillTypeVectorAtVar( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		return fillObjTarget( result_count, source_ptr, source_count, ( uint8_t * ) target_var_ptr, sizeof( TSourceType ) / sizeof( uint8_t ) );
	}
	template<>
	static bool fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result );
	template<>
	static bool fillTypeVectorAtVar< QString >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr );
};
#endif // INFOSTACK_H_H_HEAD__FILE__
