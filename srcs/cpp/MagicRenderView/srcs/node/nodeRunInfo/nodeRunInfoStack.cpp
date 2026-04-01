#include "nodeRunInfoStack.h"

#include "nodeRunInfoData.h"
#include <stack>

#define List_Pop( _List_Var ) \
	auto end = create.end( ); \
	auto begin = create.begin( ); \
	if( begin == end ) \
		return false; \
	auto listIterator = --end; \
	auto resultUnity = *listIterator; \
	create.erase( listIterator ); \
	if( result_info.copyNodeRunInfoDataToThis( resultUnity ) == false ) \
		return false; \
	create.erase( listIterator ); \
	delete resultUnity; \
	return true;

#define List_Push( _List_Var, _Push_Var ) \
	auto newPoint = new NodeRunInfoData; \
	if( newPoint->copyNodeRunInfoDataToThis( _Push_Var ) ) { \
		_List_Var.emplace_back( newPoint ); \
		return true; \
	} \
	delete newPoint; \
	return false;

bool NodeRunInfoStack::popCreateStackLast( NodeRunInfoData &result_info ) {
	List_Pop( create );
}
bool NodeRunInfoStack::popPointStackLast( NodeRunInfoData &result_info ) {
	List_Pop( point );
}

bool NodeRunInfoStack::pushCreateStackLast( const NodeRunInfoData &push_create_node ) {
	List_Push( create, push_create_node );
}
bool NodeRunInfoStack::pushPointStackLast( const NodeRunInfoData &push_point_node ) {
	List_Push( create, push_point_node );
}
bool NodeRunInfoStack::popFcuntionStackLast( NodeRunInfoData &result_info ) {
	List_Pop( function );
}
bool NodeRunInfoStack::pushFcuntionStackLast( const NodeRunInfoData &push_function_node ) {
	List_Push( create, push_function_node );
}
NodeRunInfoStack::~NodeRunInfoStack( ) {
	auto begin = point.begin( );
	auto end = point.end( );
	for( ; begin != end; ++begin )
		delete *begin;

	begin = create.begin( );
	end = create.end( );
	for( ; begin != end; ++begin )
		delete *begin;

	begin = function.begin( );
	end = function.end( );
	for( ; begin != end; ++begin )
		delete *begin;

}
