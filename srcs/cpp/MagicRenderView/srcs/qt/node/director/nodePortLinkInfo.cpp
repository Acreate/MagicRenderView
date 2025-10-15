#include "nodePortLinkInfo.h"

#include "../item/nodeItem.h"

#include "../nodeItemMenu/nodeItemMenu.h"

#include "../prot/outputProt/nodeOutputPort.h"

NodePortLinkInfo::~NodePortLinkInfo( ) {
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
		if( unLink( link_output_port ) )
			emit unlinkNodePort( this, this->inputPort, link_output_port );
	} );
	emit linkNodePort( this, this->inputPort, link_output_port );
	outputPorts.emplace_back( link_output_port, removeAction );
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
				qDebug( ) << "成功删除";
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
