#ifndef BEGINNODE_H_H_HEAD__FILE__
#define BEGINNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class BeginNode : public Node {
	Q_OBJECT;
public:
	BeginNode( QWidget *const parent, const Qt::WindowFlags &f )
		: Node( parent, f ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Begin;
	}
};

#endif // BEGINNODE_H_H_HEAD__FILE__
