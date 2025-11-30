#ifndef BEGINNODE_H_H_HEAD__FILE__
#define BEGINNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class BeginNode : public Node {
	Q_OBJECT;
public:
	BeginNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Begin;
	}
};

#endif // BEGINNODE_H_H_HEAD__FILE__
