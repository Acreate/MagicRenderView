#include "ITypeObject.h"

#include "qt/stack/varStack/IVarStack.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
ITypeObject::ITypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &get_stack_function_get_function, const std_vector< QString > &alias_type_name, QObject *parent ): QObject( parent ), getStackFunction( get_stack_function_get_function ) {
	if( !getStackFunction )
		getStackFunction = [] {
			return IVarStack::getInstance< BaseVarStackEx >( );
		};
	varStackSharedPtr = getStackFunction( );
	thisPtr = this;
	size_t count = alias_type_name.size( );
	if( count == 0 )
		return;
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
ITypeObject::ITypeObject( const ITypeObject &other ): QObject( other.parent( ) ) {
	currentTypeName = other.currentTypeName;
	getStackFunction = other.getStackFunction;
	thisPtr = other.thisPtr;
	varStackSharedPtr = other.varStackSharedPtr;
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
