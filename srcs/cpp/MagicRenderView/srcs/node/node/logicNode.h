#ifndef LOGICNODE_H_H_HEAD__FILE__
#define LOGICNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class LogicNode : public Node {
	Q_OBJECT;
public:
	LogicNode( QWidget *parent, const Qt::WindowFlags &f )
		: Node( parent, f ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Logic;
	}
};

#endif // LOGICNODE_H_H_HEAD__FILE__
