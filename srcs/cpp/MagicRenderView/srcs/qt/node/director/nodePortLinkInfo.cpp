#include "nodePortLinkInfo.h"

#include "../item/nodeItem.h"

#include "../nodeItemMenu/nodeItemMenu.h"

#include "../prot/outputProt/nodeOutputPort.h"

void NodePortLinkInfo::appendReleaseNodeItemEvent( NodeOutputPort *link_output_port ) {
	auto parentItem = link_output_port->getParentItem( );
	size_t count = nodeItemEvent.size( );
	if( count != 0 ) {
		auto data = nodeItemEvent.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == parentItem )
				return;
	}
	connect( parentItem, &NodeItem::releaseThiNodeItem, [this, parentItem]( ) {
		if( inputPort == nullptr )
			return;
		size_t count = outputPorts.size( );
		if( count != 0 )
			do {
				auto data = outputPorts.data( );
				size_t index = 0;
				for( ; index < count; ++index )
					if( data[ index ].first->getParentItem( ) == parentItem ) {
						std::pair< NodeOutputPort *, QAction * > pair = data[ index ];
						outputPorts.erase( outputPorts.begin( ) + index );
						emit unlinkNodePort( this, this->inputPort, pair.first );
						tools::debug::printInfo( "成功删除" );
						delete pair.second;
						break;
					}
				if( index == count )
					break;
				count = outputPorts.size( );
			} while( count != 0 );
		count = nodeItemEvent.size( );
		auto data = nodeItemEvent.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == parentItem ) {
				nodeItemEvent.erase( nodeItemEvent.begin( ) + index );
				break;
			}
	} );
	nodeItemEvent.emplace_back( parentItem );
}
NodePortLinkInfo::~NodePortLinkInfo( ) {
	emit releaseThis( this );
	this->disconnect( );
	outputPorts.clear( );
	delete removeLinkMenu;
}
NodePortLinkInfo::NodePortLinkInfo( NodeInputPort *input_port ) : inputPort( input_port ) {
	removeLinkMenu = new QMenu( );
}
bool NodePortLinkInfo::link( NodeOutputPort *link_output_port ) {
	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == link_output_port )
				return true; // 已经链接，即刻返回
	}

	QString actionTitleFrom( "删除 %1[%2] 输入" );
	QString activeTitle;
	activeTitle = actionTitleFrom.arg( link_output_port->getParentItem( )->getNodeTitleName( ) ).arg( link_output_port->getTitle( ) );
	auto removeAction = removeLinkMenu->addAction( activeTitle );
	connect( removeAction, &QAction::triggered, [this, link_output_port] {
		unLink( link_output_port );
	} );
	emit linkNodePort( this, this->inputPort, link_output_port );
	outputPorts.emplace_back( link_output_port, removeAction );
	appendReleaseNodeItemEvent( link_output_port );
	return true;
}
bool NodePortLinkInfo::unLink( NodeOutputPort *link_output_port ) {
	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == link_output_port ) {
				std::pair< NodeOutputPort *, QAction * > pair = data[ index ];
				outputPorts.erase( outputPorts.begin( ) + index );
				emit unlinkNodePort( this, this->inputPort, link_output_port );
				tools::debug::printInfo( "成功删除" );
				delete pair.second;
				return true; // 删除成功，即刻返回
			}
	}
	return false;
}
std_vector< NodeOutputPort * > NodePortLinkInfo::getOutputPorts( ) const {

	size_t count = outputPorts.size( );
	std_vector< NodeOutputPort * > result( count );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			result[ index ] = data[ index ].first;
	}
	return result;
}
