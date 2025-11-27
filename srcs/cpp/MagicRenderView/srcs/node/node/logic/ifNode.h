#ifndef IFNODE_H_H_HEAD__FILE__
#define IFNODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class IfNode : public Node {
	Q_OBJECT;
public:
	IfNode(  QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	bool updateLayout( ) override;
	Def_Satatic_NodeTypeName( Node::tr( "逻辑/分支" ) );
};

#endif // IFNODE_H_H_HEAD__FILE__
