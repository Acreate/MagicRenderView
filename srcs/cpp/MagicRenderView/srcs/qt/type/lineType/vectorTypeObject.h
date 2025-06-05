#ifndef VECTORTYPEOBJECT_H_H_HEAD__FILE__
#define VECTORTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "alias/type_alias.h"

#include "qt/tools/tools.h"
#include "qt/type/ITypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"

class VectorTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_vector< std_shared_ptr< ITypeObject > > > vector;
public:
	VectorTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ), vector( new std_vector< std_shared_ptr< ITypeObject > >( ) ) {
	}
	VectorTypeObject( const VectorTypeObject &other )
		: ITypeObject( other.parent( ) ),
		vector( other.vector ) {
	}
	VectorTypeObject & operator=( const VectorTypeObject &other ) {
		if( this == &other )
			return *this;
		ITypeObject::operator =( other );
		vector = other.vector;
		return *this;
	}
	virtual void append( const std_shared_ptr< ITypeObject > &append_object ) {
		vector->emplace_back( append_object );
	}
	virtual size_t count( ) const {
		return vector->size( );
	}
	virtual size_t size( ) const {
		return vector->size( );
	}
	virtual void clear( ) {
		vector->clear( );
	}
	virtual std_shared_ptr< ITypeObject > operator[]( const size_t index ) const {
		size_t count = vector->size( );
		if( count > index )
			return vector->at( index );
		tools::debug::printError( "访问下标越界" );
		return nullptr;
	}
	virtual std_vector< std_shared_ptr< ITypeObject > > getVector( ) const { return *vector; }
	virtual std_vector< std_shared_ptr< ITypeObject > > & getRefVector( ) const { return *vector; }
	virtual void setVector( const std_shared_ptr< std_vector< std_shared_ptr< ITypeObject > > > &vector = nullptr ) {
		if( vector == nullptr )
			this->clear( );
		else
			this->vector = vector;
	}
	virtual void setVector( const std_vector< std_shared_ptr< ITypeObject > > &vector ) { *this->vector = vector; }
	/// @brief 查找元素
	/// @param find_function 查找的函数，当返回 true 时，返回该匹配的元素
	/// @return 失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > find( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const {
		for( auto elemt : *vector )
			if( find_function( elemt ) )
				return elemt;
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}
	/// @brief 查找元素
	/// @param find_function 查找的函数，当返回 true 时，返回该匹配的元素
	/// @return 失败返回空的序列容器
	virtual std_vector< std_shared_ptr< ITypeObject > > findAll( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const {
		std_vector< std_shared_ptr< ITypeObject > > result;
		for( auto elemt : *vector )
			if( find_function( elemt ) )
				result.emplace_back( elemt );
		return result;
	}

	/// @brief 删除第一个元素
	/// @return 成功返回 true
	virtual bool removeStartElemt( ) {
		if( vector->size( ) == 0 )
			return false;
		vector->erase( vector->begin( ) );
		return true;
	}

	/// @brief 删除末尾元素
	/// @return 成功返回 true
	virtual bool removeLastElemt( ) {
		if( vector->size( ) == 0 )
			return false;
		vector->pop_back( );
		return true;
	}
	/// @brief 删除第一个匹配到的元素，使用到参数的比较规则实现删除
	/// @param remove_elemt 删除元素
	/// @return 成功返回 true
	virtual bool removeFirst( const std_shared_ptr< ITypeObject > &remove_elemt ) {
		std_vector< std_shared_ptr< ITypeObject > > result;
		auto iterator = vector->begin( );
		auto end = vector->end( );

		for( ; iterator != end; ++iterator )
			if( remove_elemt->compare( **iterator ) == 0 ) {
				vector->erase( iterator );
				return true;
			}
		return false;
	}

	/// @brief 删除第一个匹配到的元素，使用到参数的比较规则实现删除
	/// @param remove_elemt 删除元素
	/// @return 成功返回 true
	virtual size_t removeAll( const std_shared_ptr< ITypeObject > &remove_elemt ) {
		std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
		std::vector< std::shared_ptr< ITypeObject > >::iterator end;

		iterator = vector->begin( );
		end = vector->end( );
		size_t start = 0, removeCount = 0;
		for( ; iterator != end; ++iterator, ++start )
			if( remove_elemt->compare( **iterator ) == 0 ) {
				vector->erase( iterator );
				iterator = vector->begin( ) + start - 1;
				end = vector->end( );
				++removeCount;
			}
		return removeCount;
	}
	/// @brief 删除匹配的第一个元素
	/// @param find_function 匹配函数
	virtual void removeFind( const std_function< bool( const ITypeObject * ) > &find_function ) {
		std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
		std::vector< std::shared_ptr< ITypeObject > >::iterator end;

		iterator = vector->begin( );
		end = vector->end( );
		for( ; iterator != end; ++iterator )
			if( find_function( iterator->get( ) ) ) {
				vector->erase( iterator );
				return;
			}
	}
	/// @brief 删除全部匹配元素
	/// @param find_function 匹配函数
	virtual void removeFindAll( const std_function< bool( const ITypeObject * ) > &find_function ) {
		std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
		std::vector< std::shared_ptr< ITypeObject > >::iterator end;

		iterator = vector->begin( );
		end = vector->end( );
		size_t start = 0;
		for( ; iterator != end; ++iterator, ++start )
			if( find_function( iterator->get( ) ) ) {
				vector->erase( iterator );
				iterator = vector->begin( ) + start - 1;
				end = vector->end( );
			}
	}
	size_t typeMemorySize( ) const override {
		size_t result = 0;
		for( auto elemt : *vector )
			result += elemt->typeMemorySize( );
		return result;
	}
	int compare( const ITypeObject &rhs ) const override {
		const ITypeObject *typeObject = &rhs;
		if( this == typeObject )
			return 0;
		auto vectorTypeObject = qobject_cast< VectorTypeObject * >( typeObject );
		if( vectorTypeObject == nullptr )
			return -2;
		auto thisCount = this->vector->size( );
		auto otherCount = vectorTypeObject->vector->size( );
		if( thisCount > otherCount )
			return 1;
		if( thisCount < otherCount )
			return -1;
		for( size_t index = 0; index < otherCount; ++index ) {
			int compare = this->vector->at( index )->compare( *vectorTypeObject->vector->at( index ) );
			if( compare != 0 )
				return compare;
		}
		return 0;
	}
	QString toString( ) const override;
	QString typeName( ) const override {
		return "VectorTypeObject";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // VECTORTYPEOBJECT_H_H_HEAD__FILE__
