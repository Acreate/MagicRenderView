#ifndef JUMPNODE_H_H_HEAD__FILE__
#define JUMPNODE_H_H_HEAD__FILE__

#include "node.h"

class JumpNode : public Node {
	Q_OBJECT;
public:
	JumpNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};

#endif // JUMPNODE_H_H_HEAD__FILE__
