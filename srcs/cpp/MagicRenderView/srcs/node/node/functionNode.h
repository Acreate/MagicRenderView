#ifndef FUNCTIONNODE_H_H_HEAD__FILE__
#define FUNCTIONNODE_H_H_HEAD__FILE__


#include "node.h"

class FunctionNode : public Node {
	Q_OBJECT;
public:
	FunctionNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override;
};
#endif // FUNCTIONNODE_H_H_HEAD__FILE__
