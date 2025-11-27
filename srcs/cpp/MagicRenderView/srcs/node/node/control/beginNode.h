#ifndef BEGINNODE_H_H_HEAD__FILE__
#define BEGINNODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class BeginNode : public Node {
	Q_OBJECT;
public:
	BeginNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	bool updateLayout( ) override;
	Def_Satatic_NodeTypeName( Node::tr( "控制/开始" ) );
};

#endif // BEGINNODE_H_H_HEAD__FILE__
