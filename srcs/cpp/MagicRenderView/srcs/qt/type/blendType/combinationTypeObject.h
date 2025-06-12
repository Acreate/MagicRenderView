#ifndef COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#define COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/sequenceType/pairtTypeObject.h"

class CombinationTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	/// @brief 数据结构
	std_shared_ptr< std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > > dataStruct;
public:
	CombinationTypeObject( const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : ITypeObject( alias_type_name, parent ), dataStruct( new std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > >( ) ) {
	}
	Def_Clone_Move_override_function( CombinationTypeObject );
	CombinationTypeObject & operator=( const CombinationTypeObject &other ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &other;
		if( typeObject != nullptr && other.thisPtr != nullptr ) {
			if( this == typeObject )
				return *this;
			ITypeObject::operator =( other );
			dataStruct.reset( new std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > >( ) );
			*dataStruct = *other.dataStruct;
		} else
			thisPtr = nullptr;
		return *this;
	}
	virtual std_shared_ptr< ITypeObject > removeBeginElemnt( ) {
		size_t count = dataStruct->size( );
		if( count > 0 ) {
			auto iterator = dataStruct->begin( ) + count - 1;
			std_shared_ptr< ITypeObject > result = iterator->get( )->first;
			dataStruct->erase( iterator );
			return result;
		}
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}

	virtual std_shared_ptr< ITypeObject > removeEndElemnt( ) {
		size_t count = dataStruct->size( );
		if( count > 0 ) {
			auto iterator = dataStruct->begin( ) + count - 1;
			std_shared_ptr< ITypeObject > result = iterator->get( )->first;
			dataStruct->erase( iterator );
			return result;
		}
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}

	virtual std_shared_ptr< ITypeObject > removeItem( const QString &&var_name ) {
		auto itorater = dataStruct->begin( );
		auto end = dataStruct->end( );
		for( ; itorater != end; ++itorater )
			if( itorater->get( )->second == var_name ) {
				std::shared_ptr< ITypeObject > result = itorater->get( )->first;
				dataStruct->erase( itorater );
				return result;
			}
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}

	virtual std_shared_ptr< ITypeObject > setVarObject( const std_shared_ptr< ITypeObject > &new_type, const QString &var_name ) {
		for( auto &pair : *dataStruct )
			if( pair->second == var_name ) {
				std_shared_ptr< ITypeObject > element = pair->first; // 用于覆盖返回
				pair->first = new_type;
				return element;
			}

		auto ptr = std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > >( new std_pairt< std_shared_ptr< ITypeObject >, QString >( ) );
		ptr->first = new_type;
		ptr->second = var_name;
		dataStruct->emplace_back( ptr );
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}
	/// @brief 获取成员变量
	/// @param var_name 成员名称
	/// @return 变量
	virtual std_shared_ptr< ITypeObject > getVarObject( const QString &var_name ) const {
		for( auto pair : *dataStruct )
			if( pair->second == var_name )
				return pair->first;
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}
	/// @brief 获取匹配的结构体成员
	/// @param var_name 成员名称
	/// @return 成员
	virtual std_shared_ptr< ITypeObject > operator[]( const QString &var_name ) const {
		return getVarObject( var_name );
	}
	/// @brief 获取当前成员列表
	/// @return 成员列表
	virtual const std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > & getStructInfo( ) const {
		return *dataStruct;
	}
	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr == this ) {
			size_t thisCount = dataStruct->size( );
			size_t rCount = result_ptr->dataStruct->size( );
			if( thisCount > rCount )
				return 1;
			if( thisCount < rCount )
				return -1;
			for( size_t index = 0; index < thisCount; ++index ) {
				int compare = dataStruct->at( index )->first->compare( *result_ptr->dataStruct->at( index )->first );
				if( compare != 0 )
					return compare;
				compare = dataStruct->at( index )->second.compare( result_ptr->dataStruct->at( index )->second );
				if( compare != 0 )
					return compare;
			}
		}

		return result;
	}

	size_t typeMemorySize( ) const override {
		size_t result = 0;
		for( auto pair : *dataStruct )
			result += pair->first->typeMemorySize( ) + ( pair->second.size( ) + 1 ) * sizeof( QChar );
		return result;
	}
	QString toString( ) const override {
		QStringList result;
		for( auto pair : *dataStruct )
			result.append( pair->second + "( " + pair->first->toString( ) + " )" );
		return QString( metaObject( )->className( ) ) + " { " + result.join( ", " ) + " }";
	}
	bool serializeToVectorData( std_vector<uint8_t> *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
};

#endif // COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
