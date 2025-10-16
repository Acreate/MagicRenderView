#include "nodePortLinkInfo.h"

#include "../item/nodeItem.h"

#include "../nodeItemMenu/nodeItemMenu.h"

#include "../prot/outputProt/nodeOutputPort.h"

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
	auto parentNodeItem = link_output_port->getParentItem( );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == parentNodeItem ) {
				auto &pairs = data[ index ].second;
				size_t pairCount = pairs.size( );
				auto pairArratData = pairs.data( );
				for( size_t pairIndex = 0; pairIndex < pairCount; ++pairIndex )
					if( pairArratData[ pairIndex ].first == link_output_port )
						return true; // 已经链接，即刻返回
				QString actionTitleFrom( "删除 %1[%2] 输入" );
				QString activeTitle;
				activeTitle = actionTitleFrom.arg( link_output_port->getParentItem( )->getNodeTitleName( ) ).arg( link_output_port->getTitle( ) );
				auto removeAction = removeLinkMenu->addAction( activeTitle );
				connect( removeAction, &QAction::triggered, [this, link_output_port] {
					unLink( link_output_port );
				} );
				emit linkNodePort( this, this->inputPort, link_output_port );
				pairs.emplace_back( link_output_port, removeAction );
				return true;
			}
	}

	QString actionTitleFrom( "删除 %1[%2] 输入" );
	QString activeTitle;
	activeTitle = actionTitleFrom.arg( link_output_port->getParentItem( )->getNodeTitleName( ) ).arg( link_output_port->getTitle( ) );
	auto removeAction = removeLinkMenu->addAction( activeTitle );
	connect( removeAction, &QAction::triggered, [this, link_output_port] {
		unLink( link_output_port );
	} );
	emit linkNodePort( this, this->inputPort, link_output_port );
	std_vector_pairt< NodeOutputPort *, QAction * > unity( 1 );
	unity.data( )[ 0 ] = std_pairt( link_output_port, removeAction );
	outputPorts.emplace_back( parentNodeItem, unity );
	return true;
}
bool NodePortLinkInfo::unLink( NodeOutputPort *link_output_port ) {
	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto parentItem = link_output_port->getParentItem( );
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == parentItem ) {
				auto &pairs = data[ index ].second;
				size_t pairCount = pairs.size( );
				auto pairArratData = pairs.data( );
				for( size_t pairIndex = 0; pairIndex < pairCount; ++pairIndex )
					if( pairArratData[ pairIndex ].first == link_output_port ) {
						std::pair< NodeOutputPort *, QAction * > pair = pairArratData[ index ];
						pairs.erase( pairs.begin( ) + index );
						emit unlinkNodePort( this, this->inputPort, link_output_port );
						tools::debug::printInfo( "成功删除" );
						delete pair.second;
						if( ( pairCount - 1 ) == pairIndex )
							outputPorts.erase( outputPorts.begin( ) + index ); // 删除节点
						return true; // 删除成功，即刻返回
					}
				return false; // 不存在输入链接
			}
	}
	return false; // 甚至找不到节点（本身没有连接）
}
bool NodePortLinkInfo::releaseNodeItemPtr( NodeItem *link_node_item ) {
	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == link_node_item ) {

				auto &vector = data[ index ].second;
				count = vector.size( );
				if( count != 0 ) {
					auto vectorData = vector.data( );
					for( size_t vectorDataIndex = 0; vectorDataIndex < count; ++vectorDataIndex )
						delete vectorData[ vectorDataIndex ].second;
				}
				outputPorts.erase( outputPorts.begin( ) + index );
				return true;
			}
	}
	return false;
}
bool NodePortLinkInfo::getLink( NodeItem *link_node_item, std_vector< NodeOutputPort * > result_link ) {

	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto data = outputPorts.data( );

		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == link_node_item ) {
				count = data[ index ].second.size( );
				result_link.resize( count );
				if( count == 0 )
					return false;
				auto pair = data[ index ].second.data( );
				auto resultLinkData = result_link.data( );
				for( index = 0; index < count; ++index )
					resultLinkData[ index ] = pair[ index ].first;
				return true;
			}
	}
	return false;
}
bool NodePortLinkInfo::getLink( std_vector< NodeOutputPort * > result_link ) {

	size_t count = outputPorts.size( );
	if( count != 0 ) {
		auto data = outputPorts.data( );
		result_link.clear( );
		for( size_t index = 0; index < count; ++index ) {
			count = data[ index ].second.size( );
			if( count == 0 )
				continue;
			auto pair = data[ index ].second.data( );
			for( index = 0; index < count; ++index )
				result_link.emplace_back( pair[ index ].first );
		}
		return result_link.size( ) != 0;
	}
	return false;
}
