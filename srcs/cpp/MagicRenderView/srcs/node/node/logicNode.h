#ifndef LOGICNODE_H_H_HEAD__FILE__
#define LOGICNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class LogicNode : public Node {
	Q_OBJECT;
public:
	LogicNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Logic;
	}
};

#endif // LOGICNODE_H_H_HEAD__FILE__
