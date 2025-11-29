#include "node.h"
#include <QPainter>

#include <app/application.h>

#include <director/varDirector.h>

#include <node/port/inputPort/inputPort.h>
#include <node/port/outputPort/outputPort.h>

#include "../../director/nodeDirector.h"
#include "../../director/printerDirector.h"

#include "../nodeInfo/nodeClickInfo.h"

#include "../nodeType/nodeRunFunctionTypeInfo.h"
Node::~Node( ) {
	emit release_node_signal( this );
	size_t count, index;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		inputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete inputPortArrayPtr[ index ];
	}
	count = outputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete outputPortArrayPtr[ index ];
	}

}
Node::Node( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) { }
bool Node::appendInputPort( InputPort *input_port ) {
	
	return true;
}
bool Node::appendOutputPort( OutputPort *output_port ) {
	size_t count, index;
	OutputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			if( outputPortArrayPtr[ index ] == output_port )
				return true;
	}
	output_port->setParent( this );
	outputPortVector.emplace_back( output_port );
	return true;
}

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
bool Node::init( QWidget *parent, NodeRefLinkInfo *node_ref_link_info, NodeClickInfo *node_click_info ) {
	nodeRefLinkInfoPtr = node_ref_link_info;
	nodeClickInfo = node_click_info;
	instancePtr = Application::getInstancePtr( );
	varDirector = instancePtr->getVarDirector( );
	size_t count, index;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		inputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete inputPortArrayPtr[ index ];
		inputPortVector.clear( );
	}
	count = outputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete outputPortArrayPtr[ index ];
		outputPortVector.clear( );
	}
	nodeFunction = [] ( VarDirector *var_director ) { };
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
