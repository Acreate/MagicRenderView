#ifndef UNITYNODE_H_H_HEAD__FILE__
#define UNITYNODE_H_H_HEAD__FILE__
#pragma once


#include "node.h"

class UnityNode : public Node {
	Q_OBJECT;
public:
	UnityNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Unity;
	}
};
#endif // UNITYNODE_H_H_HEAD__FILE__
