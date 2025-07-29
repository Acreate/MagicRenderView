#ifndef VECTORTYPEOBJECT_H_H_HEAD__FILE__
#define VECTORTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "alias/type_alias.h"

#include "qt/tools/tools.h"
#include "qt/types/ITypeObject.h"

class IVarStack;
class VectorTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_vector< std_shared_ptr< ITypeObject > > > vector;
protected:
	virtual ITypeObject * createType( const QString &type_name );
public:
	operator std_vector< std_shared_ptr< ITypeObject > >( ) const {
		std_vector< std_shared_ptr< ITypeObject > > result;
		for( auto ptr : *vector )
			result.emplace_back( ptr );
		return result;
	}
public:
	VectorTypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr );

	Def_Clone_Move_override_function( VectorTypeObject );

	VectorTypeObject & operator=( const VectorTypeObject &other );
	virtual void append( const std_shared_ptr< ITypeObject > &append_object );
	virtual size_t count( ) const;
	virtual size_t size( ) const;
	virtual void clear( );
	virtual std_shared_ptr< ITypeObject > operator[]( const size_t index ) const;
	virtual std_vector< std_shared_ptr< ITypeObject > > getVector( ) const { return *vector; }
	virtual std_vector< std_shared_ptr< ITypeObject > > & getRefVector( ) const { return *vector; }
	virtual void setVector( const std_shared_ptr< std_vector< std_shared_ptr< ITypeObject > > > &vector = nullptr );
	virtual void setVector( const std_vector< std_shared_ptr< ITypeObject > > &vector ) { *this->vector = vector; }
	/// @brief 查找元素
	/// @param find_function 查找的函数，当返回 true 时，返回该匹配的元素
	/// @return 失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > find( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const;
	/// @brief 查找元素
	/// @param find_function 查找的函数，当返回 true 时，返回该匹配的元素
	/// @return 失败返回空的序列容器
	virtual std_vector< std_shared_ptr< ITypeObject > > findAll( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const;
	virtual void resize( const size_t &count ) {
		vector->resize( count );
	}
	virtual std_shared_ptr< ITypeObject > * data( ) const {
		return vector->data( );
	}
	virtual void setVectorTypeObject( const VectorTypeObject *vector_type_object ) const;
	virtual void setVectorTypeObject( const std_shared_ptr< VectorTypeObject > &vector_type_object ) const {
		setVectorTypeObject( vector_type_object.get( ) );
	}
	/// @brief 删除第一个元素
	/// @return 成功返回 true
	virtual bool removeStartElemt( );

	/// @brief 删除末尾元素
	/// @return 成功返回 true
	virtual bool removeLastElemt( );
	/// @brief 删除第一个匹配到的元素，使用到参数的比较规则实现删除
	/// @param remove_elemt 删除元素
	/// @return 成功返回 true
	virtual bool removeFirst( const std_shared_ptr< ITypeObject > &remove_elemt );

	/// @brief 删除第一个匹配到的元素，使用到参数的比较规则实现删除
	/// @param remove_elemt 删除元素
	/// @return 成功返回 true
	virtual size_t removeAll( const std_shared_ptr< ITypeObject > &remove_elemt );
	/// @brief 删除匹配的第一个元素
	/// @param find_function 匹配函数
	virtual void removeFind( const std_function< bool( const ITypeObject * ) > &find_function );
	/// @brief 删除全部匹配元素
	/// @param find_function 匹配函数
	virtual void removeFindAll( const std_function< bool( const ITypeObject * ) > &find_function );
	size_t typeMemorySize( ) const override;
	int compare( const ITypeObject &rhs ) const override;
	QString toString( ) const override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;

	template< typename IType >
		requires requires ( ITypeObject *c, IType *b ) {
			c = b;
		}
	std_shared_ptr< IType > append( ) {
		ITypeObject *obj = createType( IType::staticMetaObject.className( ) );
		if( obj == nullptr )
			return nullptr;
		std_shared_ptr< IType > newType( ( IType * ) obj );
		append( newType );
		return newType;
	}
};

#endif // VECTORTYPEOBJECT_H_H_HEAD__FILE__
