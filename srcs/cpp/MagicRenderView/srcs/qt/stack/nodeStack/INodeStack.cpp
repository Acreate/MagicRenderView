#include "./INodeStack.h"

#include <QMenu>

#include "../../menu/nodeAddMenu.h"

std_vector< std_shared_ptr< INodeStack > > INodeStack::instanceVector;

INodeStack::INodeStack( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function ): getStackFunction( get_stack_function ) {
	INodeStackThis = std_shared_ptr< INodeStack >( this, [] ( INodeStack * ) { } );
}
INodeStack::~INodeStack( ) {
}
std_shared_ptr< INodeStack > INodeStack::getStdSharedPtrInstance( const QString &stack_name ) {
	for( auto &ptr : instanceVector )
		if( ptr->metaObject( )->className( ) == stack_name && qobject_cast< INodeStack * >( ptr.get( ) ) )
			return ptr;
		else
			for( auto &name : ptr->getStackTypeNames( ) )
				if( name == stack_name && qobject_cast< INodeStack * >( ptr.get( ) ) )
					return ptr;
	return nullptr;
}
INodeStack * INodeStack::getInstance( const QString &stack_name ) {
	return getStdSharedPtrInstance( stack_name ).get( );
}
