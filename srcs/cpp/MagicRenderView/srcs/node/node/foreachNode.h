#ifndef FOREACHNODE_H_H_HEAD__FILE__
#define FOREACHNODE_H_H_HEAD__FILE__
#include "node.h"

class ForeachNode : public Node {
	Q_OBJECT;
public:
	ForeachNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};

#endif // FOREACHNODE_H_H_HEAD__FILE__
