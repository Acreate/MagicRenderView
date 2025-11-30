#ifndef GENERATENODE_H_H_HEAD__FILE__
#define GENERATENODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class GenerateNode : public Node {
	Q_OBJECT;
public:
	GenerateNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Generate;
	}
};

#endif // GENERATENODE_H_H_HEAD__FILE__
