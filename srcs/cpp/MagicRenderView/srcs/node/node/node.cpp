#include "node.h"
#include <QPainter>

#include "../nodeEventInfo/nodeClickInfo.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
Node::~Node( ) {
	emit release_node_signal( this );
	size_t count, index;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		inputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			inputPortArrayPtr[ index ];
	}
	count = outputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			outputPortArrayPtr[ index ];
	}
}
Node::Node( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) { }
void Node::setNodeClickInfo( OutputPort *const output_port ) {
	nodeClickInfo->clickType = NodeEnum::NodeClickType::OutputPort;
	nodeClickInfo->clickNode = this;
	nodeClickInfo->inputPort = nullptr;
	nodeClickInfo->outputPort = output_port;
}
void Node::setNodeClickInfo( InputPort *const input_port ) {
	nodeClickInfo->clickType = NodeEnum::NodeClickType::InputPort;
	nodeClickInfo->clickNode = this;
	nodeClickInfo->inputPort = input_port;
	nodeClickInfo->outputPort = nullptr;
}
void Node::clearNodeClickInfo( ) {
	nodeClickInfo->clickType = NodeEnum::NodeClickType::None;
	nodeClickInfo->clickNode = nullptr;
	nodeClickInfo->inputPort = nullptr;
	nodeClickInfo->outputPort = nullptr;
}
void Node::setNodeTitleClickInfo( ) {
	nodeClickInfo->clickType = NodeEnum::NodeClickType::Titile;
	nodeClickInfo->clickNode = this;
	nodeClickInfo->inputPort = nullptr;
	nodeClickInfo->outputPort = nullptr;
}
void Node::setNodeOtherClickInfo( ) {
	nodeClickInfo->clickType = NodeEnum::NodeClickType::None;
	nodeClickInfo->clickNode = this;
	nodeClickInfo->inputPort = nullptr;
	nodeClickInfo->outputPort = nullptr;
}
bool Node::link( OutputPort *signal_port, InputPort *target_prot ) {
	emit create_link_signal( signal_port, target_prot );
	return true;
}
bool Node::unlink( OutputPort *signal_port, InputPort *target_prot ) {
	emit release_link_signal( signal_port, target_prot );
	return true;
}
InputPort * Node::getInputPort( const QString &port_name ) const {
	size_t count = inputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto inputPortArrayPtr = inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( inputPortArrayPtr[ index ]->name == port_name )
			return inputPortArrayPtr[ index ];
	return nullptr;
}
OutputPort * Node::getOutputPort( const QString &port_name ) const {
	size_t count = outputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ]->name == port_name )
			return outputPortArrayPtr[ index ];
	return nullptr;
}

void Node::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
