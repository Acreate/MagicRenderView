#ifndef JUMPNODE_H_H_HEAD__FILE__
#define JUMPNODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class JumpNode : public Node {
	Q_OBJECT;
public:
	JumpNode(  QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	Def_Satatic_NodeTypeName( Node::tr( "控制/跳转" ) );
};

#endif // JUMPNODE_H_H_HEAD__FILE__
