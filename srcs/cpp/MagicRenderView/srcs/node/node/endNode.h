#ifndef ENDNODE_H_H_HEAD__FILE__
#define ENDNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class EndNode : public Node {
	Q_OBJECT;
public:
	EndNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::End;
	}
};

#endif // ENDNODE_H_H_HEAD__FILE__
