#include "node.h"
#include <QPainter>

#include <app/application.h>

#include <director/varDirector.h>

#include <node/nodeEventInfo/nodeClickInfo.h>
#include <node/nodeEventInfo/nodePortLinkInfo.h>

#include <node/port/inputPort/inputPort.h>
#include <node/port/outputPort/outputPort.h>

#include "../../director/printerDirector.h"

#include "../nodeType/nodeRunFunctionTypeInfo.h"
void Node::releaseLink( InputPort *signal_port, OutputPort *target_prot ) {
	emit this->release_link_signal( signal_port, target_prot );
	Node *targetNode = target_prot->node;
	size_t count = inputPortVector.size( );
	auto inputPortArrayPtr = inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( inputPortArrayPtr[ index ]->refOutputPortHasNode( targetNode ) )
			return;
	count = inputNodeVector.size( );
	auto refNodeArrayPtr = inputNodeVector.data( );
	index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == targetNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( refNodeArrayPtr[ index ] == nullptr )
		return;
	count -= 1;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == nullptr )
			break;
		else
			refNodeArrayPtr[ index ] = refNodeArrayPtr[ index + 1 ];
	emit this->release_ref_node_signal( this, targetNode );
}
void Node::createLink( InputPort *signal_port, OutputPort *target_prot ) {
	emit this->create_link_signal( signal_port, target_prot );
	Node *targetNode = target_prot->node;

	size_t count = inputNodeVector.size( );
	auto refNodeArrayPtr = inputNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == targetNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( index == count )
		inputNodeVector.emplace_back( targetNode );
	else if( refNodeArrayPtr[ index ] == nullptr )
		refNodeArrayPtr[ index ] = targetNode;
	connect( targetNode, &Node::release_node_signal, this, &Node::removeInputNode );
	emit this->create_ref_node_signal( this, targetNode );
}
void Node::removeInputNode( Node *remove_target ) {
	size_t count = inputNodeVector.size( );
	auto refNodeArrayPtr = inputNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == remove_target ) {
			count -= 1;
			for( ; index < count; ++index )
				if( refNodeArrayPtr[ index ] == nullptr )
					break;
				else
					refNodeArrayPtr[ index ] = refNodeArrayPtr[ index + 1 ];
			refNodeArrayPtr[ index ] = nullptr;
			return;
		}
	return;
}
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
Node::Node( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), nodeFunctionVarDirector( nullptr ) { }
bool Node::appendInputPort( InputPort *input_port ) {
	size_t count, index;
	InputPort **inputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		inputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			if( inputPortArrayPtr[ index ] == input_port )
				return true;
	}
	input_port->setParent( this );
	inputPortVector.emplace_back( input_port );
	connect( input_port, &InputPort::release_link_signal, this, &Node::releaseLink );
	connect( input_port, &InputPort::create_link_signal, this, &Node::createLink );
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
void * Node::createVar( const QString &type_name ) {
	void *resultPtr;
	if( nodeVarDirector->create( type_name, resultPtr ) == false )
		return nullptr;
	return resultPtr;
}
void * Node::createVar( const std::type_info &std_type_info ) {
	return createVar( std_type_info.name( ) );
}

bool Node::init( QWidget *parent ) {
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
	if( nodeFunctionVarDirector )
		delete nodeFunctionVarDirector;
	nodeFunctionVarDirector = new VarDirector;
	nodeFunction = [] { return nullptr; };
	return true;
}
bool Node::runFunction( NodeFunctionResultType &result_var_ptr ) const {
	if( nodeFunction == nullptr )
		return false;
	result_var_ptr = nodeFunction( );
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
