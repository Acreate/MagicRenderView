#ifndef ARRAYNODE_H_H_HEAD__FILE__
#define ARRAYNODE_H_H_HEAD__FILE__
#pragma once


#include "node.h"

class ArrayNode : public Node {
	Q_OBJECT;
public:
	ArrayNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Array;
	}
};

#endif // ARRAYNODE_H_H_HEAD__FILE__
