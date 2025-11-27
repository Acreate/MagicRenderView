#include "node.h"
#include <QPainter>

#include <app/application.h>

#include <director/varDirector.h>

#include <node/nodeEventInfo/nodeClickInfo.h>
#include <node/nodeEventInfo/nodePortLinkInfo.h>

#include <node/port/inputPort/inputPort.h>
#include <node/port/outputPort/outputPort.h>
void Node::releaseLink( InputPort *signal_port, OutputPort *target_prot ) {
	size_t count;
	size_t index;
	OutputPort **outputPortArrayPtr;
	Node *targetNode;
	Node **outputNodeArrayPtr;
	Node **inputNodeArrayPtr;
	targetNode = target_prot->node;
	outputPortArrayPtr = signal_port->linkThisOutputPortVector.data( );
	count = signal_port->linkThisOutputPortVector.size( );
	for( index = 0; index < count; ++index )
		if( outputPortArrayPtr[ index ]->node == targetNode )
			break; // 还存在目标节点
	if( index == count ) { // 输出依赖不在存有节点，则删除依赖节点
		count = outputNodeVector->size( );
		outputNodeArrayPtr = outputNodeVector->data( );
		for( index = 0; index < count; ++index )
			if( outputNodeArrayPtr[ index ] == targetNode ) {
				// 删除该节点输入依赖
				outputNodeVector->erase( outputNodeVector->begin( ) + index );
				break; // 实现该节点的删除输入依赖节点
			}
	}
	// 删除目标节点输出依赖
	count = targetNode->inputNodeVector->size( );
	inputNodeArrayPtr = targetNode->inputNodeVector->data( );
	for( index = 0; index < count; ++index )
		if( inputNodeArrayPtr[ index ] == this ) {
			targetNode->inputNodeVector->erase( targetNode->inputNodeVector->begin( ) + index );
			break; // 实现目标节点的删除输入依赖节点
		}
}
void Node::createLink( InputPort *signal_port, OutputPort *target_prot ) {

}
Node::~Node( ) {
	emit release_node_signal( this );
	size_t count, index;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;
	NodePortLinkInfo **nodePortLinkInfo;
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
bool Node::removeRefInputPortNode( Node *remove_target_ref_node ) {
	size_t outputPortVectorCount = remove_target_ref_node->outputPortVector.size( ),
			foreachIndex = 0;
	if( outputPortVectorCount == foreachIndex )
		return foreachIndex;
	auto outputPortVectorArray = remove_target_ref_node->outputPortVector.data( );
	for( ; foreachIndex < outputPortVectorCount; ++foreachIndex ) {
		if( outputPortVectorArray[ foreachIndex ]. == remove_target_ref_node ) {
			inputNodeVector->erase( inputNodeVector->begin( ) + foreachIndex );
			return false;
		}
	}

	outputPortVectorCount = inputNodeVector->size( );
	auto inputNodeArrayPtr = inputNodeVector->data( );
	foreachIndex = 0;
	for( ; foreachIndex < outputPortVectorCount; ++foreachIndex )
		if( inputNodeArrayPtr[ foreachIndex ] == remove_target_ref_node ) {
			inputNodeVector->erase( inputNodeVector->begin( ) + foreachIndex );
			return true;
		}
	return true;
}
bool Node::removeRefOutputPortNode( Node *remove_target_ref_node ) {
}
bool Node::inputPortHasRefNode( Node *output_port_ref_node ) {
	size_t count = inputPortVector.size( );

	auto inputPortArrayPtr = inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( inputPortArrayPtr[ index ]->refOutputPortHasNode( output_port_ref_node ) )
			return true;
	return false;
}
bool Node::outputPortHasRefNode( Node *input_port_ref_node ) {
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
bool Node::init( QWidget *parent ) {
	instancePtr = Application::getInstancePtr( );
	varDirector = instancePtr->getVarDirector( );
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
