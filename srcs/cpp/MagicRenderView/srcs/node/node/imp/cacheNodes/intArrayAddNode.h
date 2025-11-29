#ifndef INTARRAYADDNODE_H_H_HEAD__FILE__
#define INTARRAYADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../cacheNode.h"

class IntArrayAddNode : public CacheNode {
	Q_OBJECT;
public:
	IntArrayAddNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: CacheNode( parent, f ) { }
	bool updateLayout( ) override {
		return true;
	}
public:
	Def_Satatic_NodeTypeName( Node::tr( "数组/整数缓存序列" ) );
};

#endif // INTARRAYADDNODE_H_H_HEAD__FILE__
