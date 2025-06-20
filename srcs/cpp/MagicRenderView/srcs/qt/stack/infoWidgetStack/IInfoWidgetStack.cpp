#include "./IInfoWidgetStack.h"


std_shared_ptr< IInfoWidgetStack > IInfoWidgetStack::getStdSharedPtrInstance( const QString &stack_name ) {
	for( auto &ptr : instanceVector )
		if( ptr->metaObject( )->className( ) == stack_name && qobject_cast< IInfoWidgetStack * >( ptr.get( ) ) )
			return ptr;
		else
			for( auto &name : ptr->getStackTypeNames( ) )
				if( name == stack_name && qobject_cast< IInfoWidgetStack * >( ptr.get( ) ) )
					return ptr;
	return nullptr;
}
IInfoWidgetStack * IInfoWidgetStack::getInstance( const QString &stack_name ) {
	return getStdSharedPtrInstance( stack_name ).get( );
}
