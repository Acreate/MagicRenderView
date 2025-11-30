#ifndef JUMPNODE_H_H_HEAD__FILE__
#define JUMPNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class JumpNode : public Node {
	Q_OBJECT;
public:
	JumpNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Jump;
	}
};

#endif // JUMPNODE_H_H_HEAD__FILE__
