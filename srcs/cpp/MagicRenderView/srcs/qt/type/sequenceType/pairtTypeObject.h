#ifndef PAIRTTYPEOBJECT_H_H_HEAD__FILE__
#define PAIRTTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

class PairtTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< ITypeObject > first;
	std_shared_ptr< ITypeObject > scond;
public:
	PairtTypeObject( QObject *parent = nullptr );
	PairtTypeObject( QObject *const parent, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond )
		: ITypeObject( parent ),
		first( first ),
		scond( scond ) { }
	PairtTypeObject( const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond )
		: first( first ),
		scond( scond ) { }
	PairtTypeObject( const PairtTypeObject &other )
		: ITypeObject( other ),
		first( other.first ),
		scond( other.scond ) {
	}
	PairtTypeObject & operator=( const PairtTypeObject &other ) {
		if( this == &other )
			return *this;
		ITypeObject::operator =( other );
		first = other.first;
		scond = other.scond;
		return *this;
	}
	const ITypeObject * getFirst( ) const { return first.get( ); }
	const ITypeObject * getScond( ) const { return scond.get( ); }
	void setFirst( const std_shared_ptr< ITypeObject > &first ) { this->first = first; }
	void setScond( const std_shared_ptr< ITypeObject > &scond ) { this->scond = scond; }
	size_t typeMemorySize( ) const override {
		return ( first ? first->typeMemorySize( ) : 0 ) + ( scond ? scond->typeMemorySize( ) : 0 );
	}
	int compare( const ITypeObject &rhs ) const override {
		const ITypeObject *typeObject = &rhs;
		if( this == typeObject )
			return 0;
		auto pairtTypeObject = qobject_cast< PairtTypeObject * >( typeObject );
		if( pairtTypeObject == nullptr )
			return -2;
		int compare = first->compare( *pairtTypeObject->first );
		if( compare != 0 )
			return compare;
		compare = scond->compare( *pairtTypeObject->scond );
		if( compare != 0 )
			return compare;
		return 0;
	}
	QString toString( ) const override;
	QString typeName( ) const override {
		return "PairtTypeObject";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // PAIRTTYPEOBJECT_H_H_HEAD__FILE__
