#ifndef GENERATENODE_H_H_HEAD__FILE__
#define GENERATENODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class GenerateNode : public Node {
	Q_OBJECT;
public:
	GenerateNode( QWidget *const parent, const Qt::WindowFlags &f )
		: Node( parent, f ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Generate;
	}
};

#endif // GENERATENODE_H_H_HEAD__FILE__
