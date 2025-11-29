#ifndef CACHENODE_H_H_HEAD__FILE__
#define CACHENODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class CacheNode : public Node {
	Q_OBJECT;
public:
	CacheNode( QWidget *const parent, const Qt::WindowFlags &f )
		: Node( parent, f ) { }
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Cache;
	}
};

#endif // CACHENODE_H_H_HEAD__FILE__
