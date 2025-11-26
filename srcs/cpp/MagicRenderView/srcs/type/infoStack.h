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
namespace infoTool {
	bool fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result );
	bool fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count );
	inline bool fillObjTarget( uint64_t &result_count, const void *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( uint8_t * ) ptr, ptr_size, result );
	}
	template< typename TSourceType >
	bool fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( const uint8_t * ) ptr, sizeof( TSourceType ) / sizeof( uint8_t ), result );
	}
	template< typename TSourceType >
	bool fillTypeVectorAtVar( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		return fillObjTarget( result_count, source_ptr, source_count, ( uint8_t * ) target_var_ptr, sizeof( TSourceType ) / sizeof( uint8_t ) );
	}
	template<>
	inline bool fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result ) {
		QString *stringPtr = ( QString * ) ptr;
		std::vector< uint8_t > buff;
		auto local8Bit = stringPtr->toUtf8( );
		auto converVar = local8Bit.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		char *data = local8Bit.data( );
		if( fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QString >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *target_var_ptr ) {
		QString *stringPtr = ( QString * ) target_var_ptr;
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		*stringPtr = QString::fromUtf8( ( const char * ) offset, result_count );
		result_count = result_count + sizeTypeCount;
		return result_count;
	}
}
#endif // INFOSTACK_H_H_HEAD__FILE__
