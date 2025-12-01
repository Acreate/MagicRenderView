#ifndef NODECLICKINFO_H_H_HEAD__FILE__
#define NODECLICKINFO_H_H_HEAD__FILE__
#pragma once
#include "../../enums/nodeEnum.h"

class OutputPort;
class InputPort;
class Node;
class NodeClickInfo {
	friend class Node;
private:
	NodeEnum::NodeClickType clickType;
	Node *clickNode;
	InputPort *inputPort;
	OutputPort *outputPort;
public:
	virtual ~NodeClickInfo( ) = default;
	NodeClickInfo( const NodeEnum::NodeClickType click_type, Node *const click_node, InputPort *const input_port, OutputPort *const output_port )
		: clickType( click_type ),
		clickNode( click_node ),
		inputPort( input_port ),
		outputPort( output_port ) { }
	virtual NodeEnum::NodeClickType getClickType( ) const { return clickType; }
	virtual Node * getClickNode( ) const { return clickNode; }
	virtual InputPort * getInputPort( ) const { return inputPort; }
	virtual OutputPort * getOutputPort( ) const { return outputPort; }
	virtual void clear( ) {
		clickType = NodeEnum::NodeClickType::None;
		clickNode = nullptr;
		inputPort = nullptr;
		outputPort = nullptr;
	}
};

#endif // NODECLICKINFO_H_H_HEAD__FILE__
