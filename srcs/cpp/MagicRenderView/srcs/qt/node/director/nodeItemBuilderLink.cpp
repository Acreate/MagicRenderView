#include "nodeItemBuilderLink.h"

#include "nodeItemInfo.h"
#include "nodePortLinkInfo.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"

#include "../prot/inputProt/nodeInputPort.h"
NodeItemBuilderLink::~NodeItemBuilderLink( ) {
	emit releaseThisSignal( this );
}
bool NodeItemBuilderLink::appendNodeItemInfo( NodeItemInfo *append_nodeite_info ) {
	if( append_nodeite_info == nullptr )
		return true;
	size_t count = nodeItemInfos.size( );
	if( count != 0 ) {
		auto data = nodeItemInfos.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == append_nodeite_info )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = append_nodeite_info;
				emit appendNodeItemInfoSignal( append_nodeite_info );
				return true;
			}
	}
	nodeItemInfos.emplace_back( append_nodeite_info );
	emit appendNodeItemInfoSignal( append_nodeite_info );
	return true;
}
bool NodeItemBuilderLink::appendNodePortLinkInfo( NodePortLinkInfo *append_node_port_link_info ) {
	if( append_node_port_link_info == nullptr )
		return true;
	size_t count = nodePortLinkInfos.size( );
	if( count != 0 ) {
		auto data = nodePortLinkInfos.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == append_node_port_link_info )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = append_node_port_link_info;
				emit appendNodePortLinkInfoSignal( append_node_port_link_info );
				return true;
			}
	}
	nodePortLinkInfos.emplace_back( append_node_port_link_info );
	emit appendNodePortLinkInfoSignal( append_node_port_link_info );
	return true;
}
bool NodeItemBuilderLink::appendNodeItemInfoVector( const std_vector< NodeItemInfo * > &append_nodeite_info ) {
	size_t appendCount = append_nodeite_info.size( );
	if( appendCount == 0 )
		return true;
	auto appendArrayPtr = append_nodeite_info.data( );

	for( size_t appendIndex = 0; appendIndex < appendCount; ++appendIndex )
		appendNodeItemInfo( appendArrayPtr[ appendIndex ] );

	return true;
}
bool NodeItemBuilderLink::appendNodePortLinkInfoVector( const std_vector< NodePortLinkInfo * > &append_node_port_link_info ) {
	size_t appendCount = append_node_port_link_info.size( );
	if( appendCount == 0 )
		return true;
	auto appendArrayPtr = append_node_port_link_info.data( );

	for( size_t appendIndex = 0; appendIndex < appendCount; ++appendIndex )
		appendNodePortLinkInfo( appendArrayPtr[ appendIndex ] );

	return true;
}
bool NodeItemBuilderLink::removeNodeItemInfo( NodeItemInfo *remove_nodeite_info ) {
	if( remove_nodeite_info == nullptr )
		return true;
	size_t count = nodeItemInfos.size( );
	if( count != 0 ) {
		auto data = nodeItemInfos.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == remove_nodeite_info ) {

				emit removeNodeItemInfoSignal( remove_nodeite_info );
				data[ index ] = nullptr;
				return true;
			}
	}
	return false;
}
bool NodeItemBuilderLink::removeNodePortLinkInfo( NodePortLinkInfo *remove_node_port_link_info ) {
	if( remove_node_port_link_info == nullptr )
		return true;
	size_t count = nodePortLinkInfos.size( );
	if( count != 0 ) {
		auto data = nodePortLinkInfos.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == remove_node_port_link_info ) {
				emit removeNodePortLinkInfoSignal( remove_node_port_link_info );
				data[ index ] = nullptr;
				return true;
			}
	}
	return false;
}
bool NodeItemBuilderLink::removeNodeItemInfoVector( const std_vector< NodeItemInfo * > &remove_nodeite_info ) {
	size_t appendCount = remove_nodeite_info.size( );
	if( appendCount == 0 )
		return true;
	auto appendArrayPtr = remove_nodeite_info.data( );
	for( size_t appendIndex = 0; appendIndex < appendCount; ++appendIndex )
		removeNodeItemInfo( appendArrayPtr[ appendIndex ] );
	return true;
}
bool NodeItemBuilderLink::removeNodePortLinkInfoVector( const std_vector< NodePortLinkInfo * > &remove_node_port_link_info ) {
	size_t appendCount = remove_node_port_link_info.size( );
	if( appendCount == 0 )
		return true;
	auto appendArrayPtr = remove_node_port_link_info.data( );
	for( size_t appendIndex = 0; appendIndex < appendCount; ++appendIndex )
		removeNodePortLinkInfo( appendArrayPtr[ appendIndex ] );
	return true;
}
void NodeItemBuilderLink::clearNodeItemInfoVector( ) {
	nodeItemInfos.clear( );
}
void NodeItemBuilderLink::clearNodePortLinkInfoVector( ) {
	nodePortLinkInfos.clear( );
}
void NodeItemBuilderLink::clear( ) {
	clearNodeItemInfoVector( );
	clearNodePortLinkInfoVector( );
}

bool NodeItemBuilderLink::generateBuilderInfo( ) {
	// todo : 1. 实现编译节点
	return true;
}

bool NodeItemBuilderLink::next( ) {
	// todo : 2. 编译下一个模块
	return false;
}
bool NodeItemBuilderLink::isRun( ) const {
	// todo : 4. 是否可以运行
	return false;
}
bool NodeItemBuilderLink::run( ) {
	// todo : 5. 运行期间是否正确
	return false;
}
bool NodeItemBuilderLink::getRunNodeItems( std_vector< NodeItemInfo * > &result_current_run_info_vector ) {
	// todo : 3. 获取当前模块的运行节点
	return false;
}
