#ifndef POINTNODE_H_H_HEAD__FILE__
#define POINTNODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class PointNode : public Node {
	Q_OBJECT;
public:
	PointNode( QWidget *parent, const Qt::WindowFlags &f )
		: Node( parent, f ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Point;
	}
};

#endif // POINTNODE_H_H_HEAD__FILE__
