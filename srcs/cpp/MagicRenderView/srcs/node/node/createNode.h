#ifndef CREATENODE_H_H_HEAD__FILE__
#define CREATENODE_H_H_HEAD__FILE__


#include "node.h"

class CreateNode : public Node {
	Q_OBJECT;
public:
	CreateNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};

#endif // CREATENODE_H_H_HEAD__FILE__
