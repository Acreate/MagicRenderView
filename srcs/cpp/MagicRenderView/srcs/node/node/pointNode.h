#ifndef POINTNODE_H_H_HEAD__FILE__
#define POINTNODE_H_H_HEAD__FILE__

#include "node.h"

class PointNode : public Node {
	Q_OBJECT;
public:
	PointNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Point;
	}
};

#endif // POINTNODE_H_H_HEAD__FILE__
