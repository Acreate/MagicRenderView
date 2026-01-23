#ifndef PROCESSNODE_H_H_HEAD__FILE__
#define PROCESSNODE_H_H_HEAD__FILE__

#include "node.h"

class ProcessNode : public Node {
	Q_OBJECT;
public:
	ProcessNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};

#endif // PROCESSNODE_H_H_HEAD__FILE__
