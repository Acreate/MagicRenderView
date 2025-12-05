#include "nodeHistory.h"
NodeHistory::NodeHistory( const std::function< NodeHistory*( ) > &current_operate, const std::function< NodeHistory*( ) > &cancel_operate ) : currentOperate( current_operate ), cancelOperate( cancel_operate ) { }
NodeHistory * NodeHistory::callCurrentOperate( ) {
	if( currentOperate == nullptr )
		return nullptr;
	
	return currentOperate( );
}
NodeHistory * NodeHistory::callCancelOperate( ) {
	if( cancelOperate == nullptr )
		return nullptr;
	
	return cancelOperate( );
}
