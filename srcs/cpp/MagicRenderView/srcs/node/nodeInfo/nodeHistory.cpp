#include "nodeHistory.h"
NodeHistory::NodeHistory( const std::function< void( ) > &current_operate, const std::function< void( ) > &cancel_operate ) : currentOperate( current_operate ), cancelOperate( cancel_operate ) { }
NodeHistory * NodeHistory::callCurrentOperate( ) {
	if( currentOperate == nullptr )
		return nullptr;
	currentOperate( );
	return new NodeHistory( currentOperate, cancelOperate );
}
NodeHistory * NodeHistory::callCancelOperate( ) {
	if( cancelOperate == nullptr )
		return nullptr;
	cancelOperate( );
	return new NodeHistory( cancelOperate, currentOperate );
}
