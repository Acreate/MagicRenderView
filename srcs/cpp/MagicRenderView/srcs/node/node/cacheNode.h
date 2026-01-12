#ifndef CACHENODE_H_H_HEAD__FILE__
#define CACHENODE_H_H_HEAD__FILE__

#include "node.h"

class CacheNode : public Node {
	Q_OBJECT;
public:
	CacheNode( const QString &node_name )
		: Node( node_name ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Cache;
	}
};

#endif // CACHENODE_H_H_HEAD__FILE__
