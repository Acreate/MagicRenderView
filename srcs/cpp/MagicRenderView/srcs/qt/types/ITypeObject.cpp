#include "ITypeObject.h"

#include "qt/stacks/varStack/IVarStack.h"
#include "qt/stacks/varStack/base/baseVarStack.h"
void ITypeObject::disconnectDestGen( QObject *ptr ) {
	if( generateThisVarStackPtr == ptr )
		generateThisVarStackPtr = nullptr;
}
ITypeObject::ITypeObject( IVarStack *generate_this_var_stack_ptr_ptr, const std_function< std_shared_ptr< IVarStack > ( ) > &get_stack_function_get_function, const std_vector< QString > &alias_type_name, QObject *parent ): QObject( parent ), getStackFunction( get_stack_function_get_function ), generateThisVarStackPtr( generate_this_var_stack_ptr_ptr ) {
	if( !getStackFunction )
		getStackFunction = [] {
			return IVarStack::getInstance< BaseVarStack >( );
		};
	varStackSharedPtr = getStackFunction( );
	thisPtr = this;
	size_t count = alias_type_name.size( );
	if( count != 0 ) {
		auto datas = alias_type_name.data( );
		// 扩张
		currentTypeName.resize( count );
		auto targetPtr = currentTypeName.data( );
		for( size_t index = 0; index < count; ++index ) {
			QString trimmed = datas[ index ].trimmed( );
			if( !trimmed.isEmpty( ) )
				targetPtr[ index ] = trimmed;
		}
	}
	if( generateThisVarStackPtr )
		connect( generate_this_var_stack_ptr_ptr, &QObject::destroyed, this, &ITypeObject::disconnectDestGen );
}
ITypeObject::ITypeObject( const ITypeObject &other ): QObject( other.parent( ) ) {
	currentTypeName = other.currentTypeName;
	getStackFunction = other.getStackFunction;
	thisPtr = other.thisPtr;
	varStackSharedPtr = other.varStackSharedPtr;
	generateThisVarStackPtr = other.generateThisVarStackPtr;
	connect( generateThisVarStackPtr, &QObject::destroyed, this, &ITypeObject::disconnectDestGen );
}
ITypeObject & ITypeObject::operator=( const ITypeObject &other ) {
	if( this == nullptr || thisPtr == nullptr )
		return *this;
	if( this == &other )
		return *this;
	if( other.thisPtr != nullptr ) {
		setParent( other.parent( ) );
		currentTypeName = other.currentTypeName;
		thisPtr = &other;
		getStackFunction = other.getStackFunction;
		varStackSharedPtr = other.varStackSharedPtr;
		uiTypeName = other.uiTypeName;
		if( generateThisVarStackPtr )
			disconnect( generateThisVarStackPtr, &QObject::destroyed, this, &ITypeObject::disconnectDestGen );
		generateThisVarStackPtr = other.generateThisVarStackPtr;
		connect( generateThisVarStackPtr, &QObject::destroyed, this, &ITypeObject::disconnectDestGen );
	} else
		thisPtr = nullptr;

	return *this;
}
std_vector< QString > ITypeObject::getStackTypeNames( ) const {
	if( getStackFunction )
		return getStackFunction( )->getStackTypeNames( );
	return { };
}
bool equ( const ITypeObject &left, const void *right ) {
	if( right == nullptr )
		if( &left == nullptr || left.isNullptr( ) )
			return true;
		else
			return false;
	if( &left == nullptr || left.isNullptr( ) )
		return false;
	if( &left != right )
		return false;
	return true;
}
