#ifndef PAIRTTYPEOBJECT_H_H_HEAD__FILE__
#define PAIRTTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"
#include <qt/type/baseType/nullTypeObject.h>

class PairtTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< ITypeObject > first;
	std_shared_ptr< ITypeObject > scond;
public:
	PairtTypeObject( const std_function< IVarStack*( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parnet = nullptr );
	PairtTypeObject( const std_function< IVarStack*( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *const parent, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond );
	PairtTypeObject( const std_function< IVarStack*( ) > &gener_var_stack, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond );

	Def_Clone_Move_override_function( PairtTypeObject );

	PairtTypeObject & operator=( const PairtTypeObject &other );
	const ITypeObject * getFirst( ) const { return first.get( ); }
	const ITypeObject * getScond( ) const { return scond.get( ); }
	void setFirst( const std_shared_ptr< ITypeObject > &first ) { this->first = first; }
	void setScond( const std_shared_ptr< ITypeObject > &scond ) { this->scond = scond; }
	size_t typeMemorySize( ) const override {
		return ( first ? first->typeMemorySize( ) : 0 ) + ( scond ? scond->typeMemorySize( ) : 0 );
	}

	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr == this ) {
			int compare = first->compare( *result_ptr->first );
			if( compare != 0 )
				return compare;
			compare = scond->compare( *result_ptr->scond );
			if( compare != 0 )
				return compare;
		}
		return result;
	}
	QString toString( ) const override {
		QString resultString( "(" );
		if( first )
			resultString = resultString + first->toString( );
		if( scond )
			resultString = resultString + "," + first->toString( ) + ")";
		return resultString;
	}
	size_t serializeToObjectData( const uint8_t *read_data_vector, size_t data_count ) override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
};

#endif // PAIRTTYPEOBJECT_H_H_HEAD__FILE__
