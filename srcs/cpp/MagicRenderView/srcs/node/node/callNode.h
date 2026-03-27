#ifndef CALLNODE_H_H_HEAD__FILE__
#define CALLNODE_H_H_HEAD__FILE__


#include "node.h"

class CallNode : public Node {
	Q_OBJECT;
public:
	CallNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};
#endif // CALLNODE_H_H_HEAD__FILE__
